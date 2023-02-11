#include "helper.h"
#include "fs.h"
#include "path.h"

#include <cmath>

#include <QDir>


#include <QMap>
#include <QApplication>

#include <QTreeWidgetItem>
#include <QGroupBox>
#include <QRadioButton>
#include <QSettings>
#include <QDesktopServices>
#include <QUrl>
#include <QUrl>
#include <QDebug>


//#define ENABLE_SOUND
#ifdef ENABLE_SOUND
#include <QSoundEffect>
#endif

#ifdef Q_OS_WIN
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#include <QtWin>
#endif
#include <shlwapi.h>
#include <memory.h>
#pragma comment (lib,"Shlwapi.lib")
#endif

typedef struct _REPARSE_DATA_BUFFER {
	ULONG  ReparseTag;
	USHORT ReparseDataLength;
	USHORT Reserved;
	union {
		struct {
			USHORT SubstituteNameOffset;
			USHORT SubstituteNameLength;
			USHORT PrintNameOffset;
			USHORT PrintNameLength;
			ULONG  Flags;
			WCHAR  PathBuffer[ 1 ];
		} SymbolicLinkReparseBuffer;
		struct {
			USHORT SubstituteNameOffset;
			USHORT SubstituteNameLength;
			USHORT PrintNameOffset;
			USHORT PrintNameLength;
			WCHAR  PathBuffer[ 1 ];
		} MountPointReparseBuffer;
		struct {
			UCHAR DataBuffer[ 1 ];
		} GenericReparseBuffer;
	} DUMMYUNIONNAME;
} REPARSE_DATA_BUFFER, * PREPARSE_DATA_BUFFER;


QString removeUncOrLongPathPrefix( QString path ) {
	constexpr qsizetype minPrefixSize = 4;
	if( path.size() < minPrefixSize )
		return path;

	auto data = path.data();
	const auto slash = path[ 0 ];
	if( slash != u'\\' && slash != u'/' )
		return path;

	// check for "//?/" or "/??/"
	if( data[ 2 ] == u'?' && data[ 3 ] == slash && ( data[ 1 ] == slash || data[ 1 ] == u'?' ) ) {

		path = path.remove( 0, minPrefixSize );

		// check for a possible "UNC/" prefix left-over
		if( path.size() >= 4 ) {
			data = path.data();
			if( data[ 0 ] == u'U' && data[ 1 ] == u'N' && data[ 2 ] == u'C' && data[ 3 ] == slash ) {
				data[ 2 ] = slash;
				return path.remove( 0, 2 );
			}
		}
	}

	return path;
}


//////////////////////////////////////////////////////////////////////////////////
HFileInfo::HFileInfo( const QString& _fullPath ) :
	QFileInfo( _fullPath ),
	fullpath( _fullPath ) {

}

/////////////////////////////////////////
bool HFileInfo::isLink() {
	return isSymbolicLink() || isJunction();
}

/////////////////////////////////////////
QString HFileInfo::linkTarget() {
	if( isSymbolicLink() ) return symLinkTarget();
	if( isJunction() ) return 	$::junctionTarget( fullpath );
	return "";
}

namespace $ {

	void naturalSort( QStringList& files ) {
#ifdef Q_OS_WIN
		struct {
			bool operator()( const QString& a, const QString& b ) {
				int e = StrCmpLogicalW(
					(LPCWSTR) a.unicode(),
					(LPCWSTR) b.unicode() );
				return e < 0;
			}
		} pred;
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
		qSort( files.begin(), files.end(), pred );
#else
		std::sort( files.begin(), files.end(), pred );
#endif

#else
		files.sort();
#endif
	}


	bool match( const QString& s1, const QString& s2, std::function<void( QRegularExpressionMatch& )> func, QRegularExpression::MatchType matchType ) {
		if( s1.isEmpty() ) return false;

		QRegularExpression r( s2 );

		//r.setMinimal( true );
		QRegularExpressionMatch m = r.match( s1, matchType );

		if( m.hasMatch() ) {
			//	//R.@_ = mm[ 0 ].Groups;
				//func ? .Invoke( mm[ 0 ].Groups );
			if( func ) func( m );
			return true;
		}
		return false;
	}


	//QString trimStart( const QString& s, QString trim ) {
	//	QString ss = s;
	//	if( ss.endsWith( trim ) ) {
	//		ss.chop( 1 );
	//	}
	//	return ss;
	//}
	QString trimEnd( const QString& s, QString trim ) {
		QString ss = s;
		if( ss.endsWith( trim ) ) {
			ss.chop( 1 );
		}
		return ss;
	}
	QStringList select( const QStringList& lst, std::function<QString( const QString& )> func ) {
		QStringList result;
		for( auto& s : lst ) {
			result << func( s );
		}
		return result;
	}


	void setBoldFont( QTreeWidgetItem& item ) {
		auto ff = QFont( item.font( 0 ) );
		ff.setBold( true );
		item.setFont( 0, ff );
	}


	QPixmap getStdPixmap( QStyle::StandardPixmap id ) {
		return qApp->style()->standardPixmap( id );
	}

	// エクスプローラで見えるサイズ
	// 
	QString toStringFileSize( qint64 fsize ) {
		double num = fsize;

		if( num >= 1024 ) {
			num /= 1024.0;
		}
		else if( 0 < num ) {
			num = 1;
		}
		return QLocale( QLocale::English ).toString( (ulong) std::ceil( num ) ) + " KB";
	}


	/// @brief  日付チェック
	/// @param  inFile
	/// @param  outFile
	/// @return outFileよりinFileが新しい時はtrue
	bool isLastModified( const QString& inFile, const QString& outFile ) {
		//if( config.bDateCheck == Qt::CheckState::Checked ) return true;

		bool enable = false;
		if( fs::isExistFile( outFile ) ) {
			if( QFileInfo( outFile ).lastModified() < QFileInfo( inFile ).lastModified() ) {
				enable = true;
			}
		}
		else {
			enable = true;
		}
		return enable;
	}

	QString makeUniqueDirectoryPath( QString fpath ) {
		if( !fs::isExistDirectory( fpath ) )return fpath;

		QFileInfo finfo( fpath );

		if( finfo.isAbsolute() ) {
			auto dir = path::getDirectoryName( fpath );
			auto base = path::getFileName( fpath );

			for( int i = 2;; i++ ) {
				fpath = $$( "%1/%2 (%3)" ).arg( dir ).arg( base ).arg( i );
				if( !fs::isExistDirectory( fpath ) )break;
			}
		}
		else {
			/* たぶんコレでいいと思うけど試していない
			auto base = fpath ;

			for( int i = 2;; i++ ) {
				fpath = $$( "%1 (%2)" ).arg( base ).arg( i );
				if( !fs::isExistDirectory( fpath ) )break;
			}
			*/
		}
		return fpath;
	}

	/////////////////////////////////////////
	QString makeUniqueFilePath( QString fpath ) {
		if( !fs::isExistFile( fpath ) )return fpath;

		QFileInfo finfo( fpath );

		if( finfo.isAbsolute() ) {
			auto dir = path::getDirectoryName( fpath );
			auto base = path::getBaseName( fpath );
			auto suffix = path::getSuffix( fpath );

			for( int i = 0;; i++ ) {
				fpath = $$( "%1/%2_%3.%4" ).arg( dir ).arg( base ).arg( i ).arg( suffix );
				if( !fs::isExistFile( fpath ) )break;
			}
		}
		else {
			/* たぶんコレでいいと思うけど試していない
			auto base = path::getBaseName( fpath );
			auto suffix = path::getSuffix( fpath );

			for( int i = 0;; i++ ) {
				fpath = $$( "%1_%2.%3" ).arg( base ).arg( i ).arg( suffix );
				if( !fs::isExistFile( fpath ) )break;
			}
			*/
		}
		return fpath;
	}


#ifdef Q_OS_WIN
	bool isDrakMode() {
		QSettings settings( "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", QSettings::NativeFormat );
		return settings.value( "AppsUseLightTheme" ) == 0;
	}
#endif

	/////////////////////////////////////////
	void showInExplorer( const QString& path ) {
		QDesktopServices::openUrl( QUrl::fromLocalFile( path ) );
	}


	/////////////////////////////////////////
	void showProperty( const QString& path ) {
#ifdef Q_OS_WIN
		SHELLEXECUTEINFO sei;

		ZeroMemory( &sei, sizeof( sei ) );
		sei.cbSize = sizeof( sei );
		sei.lpFile = $::toWCharPtr( path );
		sei.lpVerb = TEXT( "properties" );
		sei.fMask = SEE_MASK_INVOKEIDLIST | SEE_MASK_NOCLOSEPROCESS;
		ShellExecuteEx( &sei );
#endif
	}


	QHash<QString, QString> suffix2kind;

	/////////////////////////////////////////
	QString fileKind( const QString& path ) {
#ifdef Q_OS_WIN
		auto suffix = QFileInfo( path ).suffix();

		auto it = suffix2kind.find( suffix );

		if( it != suffix2kind.constEnd() ) {
			return ( *it );
		}

		auto s = $$( ".%1" ).arg( suffix );
		auto* w = s.utf16();

		DWORD dwSize;
		auto hr = AssocQueryStringW(
			ASSOCF_NOTRUNCATE,
			ASSOCSTR_FRIENDLYDOCNAME,
			(wchar_t*) w,
			nullptr,
			nullptr,
			&dwSize
		);
		wchar_t* buf = new wchar_t[ dwSize ];
		//ZeroMemory( &buf, sizeof( wchar_t ) * dwSize );

		hr = AssocQueryStringW(
			ASSOCF_NOTRUNCATE,
			ASSOCSTR_FRIENDLYDOCNAME,
			(wchar_t*) w,
			nullptr,
			buf,
			&dwSize
		);
		auto result = QString::fromWCharArray( buf );
		suffix2kind.insert( suffix, result );
		delete[] buf;
		return result;
#else
		return "";
#endif
	}


	/////////////////////////////////////////
	QString junctionTarget( const QString& path ) {
		QString result;
#ifdef Q_OS_WIN
		HANDLE handle = CreateFile( (wchar_t*) path.utf16(),
			FILE_READ_EA,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			0,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
			0 );

		if( handle != INVALID_HANDLE_VALUE ) {
			DWORD bufsize = MAXIMUM_REPARSE_DATA_BUFFER_SIZE;
			REPARSE_DATA_BUFFER* rdb = (REPARSE_DATA_BUFFER*) malloc( bufsize );
			Q_CHECK_PTR( rdb );
			DWORD retsize = 0;
			if( ::DeviceIoControl( handle, FSCTL_GET_REPARSE_POINT, 0, 0, rdb, bufsize, &retsize, 0 ) ) {
				if( rdb->ReparseTag == IO_REPARSE_TAG_MOUNT_POINT ) {
					int length = rdb->MountPointReparseBuffer.SubstituteNameLength / sizeof( wchar_t );
					int offset = rdb->MountPointReparseBuffer.SubstituteNameOffset / sizeof( wchar_t );
					const wchar_t* PathBuffer = &rdb->MountPointReparseBuffer.PathBuffer[ offset ];
					result = QString::fromWCharArray( PathBuffer, length );
				}
				else if( rdb->ReparseTag == IO_REPARSE_TAG_SYMLINK ) {
					int length = rdb->SymbolicLinkReparseBuffer.SubstituteNameLength / sizeof( wchar_t );
					int offset = rdb->SymbolicLinkReparseBuffer.SubstituteNameOffset / sizeof( wchar_t );
					const wchar_t* PathBuffer = &rdb->SymbolicLinkReparseBuffer.PathBuffer[ offset ];
					result = QString::fromWCharArray( PathBuffer, length );
				}
				// remove "\\?\", "\??\" or "\\?\UNC\"
				result = removeUncOrLongPathPrefix( result );
			}
			free( rdb );
			CloseHandle( handle );

			//#if QT_CONFIG(fslibs) && QT_CONFIG(regularexpression)
						//initGlobalSid();
			QRegularExpression matchVolumeRe( QLatin1String( "^Volume\\{([a-z]|[0-9]|-)+\\}\\\\" ), QRegularExpression::CaseInsensitiveOption );
			auto matchVolume = matchVolumeRe.match( result );
			if( matchVolume.hasMatch() ) {
				Q_ASSERT( matchVolume.capturedStart() == 0 );
				DWORD len;
				wchar_t buffer[ MAX_PATH ];
				const QString volumeName = QLatin1String( "\\\\?\\" ) + matchVolume.captured();
				if( GetVolumePathNamesForVolumeName( reinterpret_cast<LPCWSTR>( volumeName.utf16() ), buffer, MAX_PATH, &len ) != 0 )
					result.replace( 0, matchVolume.capturedLength(), QString::fromWCharArray( buffer ) );
			}
			//#endif // QT_CONFIG(fslibs)
		}
#endif
		return path::separatorToSlash( result );
	}


	/////////////////////////////////////////
	int shellExecute(const QString& _filePath, const QString& _parameters ) {
		QString filePath = _filePath;
		if(fs::isExistDirectory( filePath ) || fs::isExistFile( filePath ) ) {
			filePath = $$( "\"%1\"" ).arg( path::separatorToOS( filePath ) );
		}

		QString parameters = _parameters;
		if( fs::isExistDirectory( parameters ) || fs::isExistFile( parameters ) ) {
			parameters = $$( "\"%1\"" ).arg( path::separatorToOS( parameters ) );
		}
		//SHELLEXECUTEINFO sei;
		//ZeroMemory( &sei, sizeof( SHELLEXECUTEINFO ) );
		//sei.cbSize=  sizeof( SHELLEXECUTEINFO );
		//sei.lpDirectory = $::toWCharPtr( fol );
		//sei.lpFile = $::toWCharPtr( fil );
		//sei.lpParameters = $::toWCharPtr( param );
		//sei.lpVerb = L"open";
		//sei.nShow = SW_SHOWNORMAL;
		auto hInst = ShellExecute( NULL, L"open", $::toWCharPtr( filePath ), $::toWCharPtr( parameters ), NULL, SW_SHOWNORMAL );
		//ShellExecuteEx( &sei );

		return 0;
	}


	/////////////////////////////////////////
	/*
	 * getDiskFreeSpaceInGB
	 *
	 * Returns the amount of free drive space for the given drive in GB. The
	 * value is rounded to the nearest integer value.
	 */
	std::tuple<quint64, quint64, quint64> getDiskFreeSpace( QChar driveLetter ) {
#ifdef Q_OS_WIN
		quint64 freeBytesAvailableToCaller;
		ULARGE_INTEGER totalNumberOfBytes;
		ULARGE_INTEGER totalNumberOfFreeBytes;
		freeBytesAvailableToCaller = 0L;
		totalNumberOfBytes.QuadPart = 0L;
		totalNumberOfFreeBytes.QuadPart = 0L;
		auto drive = $$( "%1:" ).arg( driveLetter );
		auto* w = $::toWCharPtr( drive );
		if( !GetDiskFreeSpaceEx( w, (PULARGE_INTEGER) &freeBytesAvailableToCaller, &totalNumberOfBytes, &totalNumberOfFreeBytes ) ) {
			qDebug() << "ERROR: Call to GetDiskFreeSpaceEx() failed.";
		}

		//int freeSpace_gb = freeBytesToCaller.QuadPart / B_per_GB;
		//qDebug() << "Free drive space: " << freeSpace_gb << "GB";

		return std::tuple<quint64, quint64, quint64>(
			freeBytesAvailableToCaller,
			totalNumberOfBytes.QuadPart,
			totalNumberOfFreeBytes.QuadPart );
#endif
	}


#ifdef ENABLE_SOUND

	QMap<QString, QSoundEffect*> soundCache;

	void $::playSound( const QString& filepath ) {
		if( soundCache.contains( filepath ) ) {
			soundCache[ filepath ]->play();
			return;
		}
		QSoundEffect* effect = new QSoundEffect();
		auto ur = QUrl::fromLocalFile( separatorToOS( filepath ) );
		effect->setSource( ur );
		effect->setVolume( 50 );
		effect->play();

		soundCache.insert( filepath, effect );
	}
#endif

}
