#include "helper.h"
#include "fs.h"
#include "path.h"

#include <QString>
#include <QStringList>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#ifdef Q_OS_WIN
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#include <QtWin>
#endif
#include <shlwapi.h>
#endif
#include <QDebug>
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#include <QTextCodec>
#endif

void binarySerializer::write( const QString& filepath, std::function<void( QDataStream& )> cb ) {
	fs::mkdir( path::getDirectoryName( filepath ) );
	QFile file( filepath );
	file.open( QFile::WriteOnly );
	QDataStream dataStream( &file );
	cb( dataStream );
}
void binarySerializer::read( const QString& filepath, std::function<void( QDataStream& )> cb ) {
	QFile file( filepath );
	file.open( QFile::ReadOnly );
	QDataStream dataStream( &file );
	//QVariant variant;
	cb( dataStream );
	//serializable.fromVariant( variant );
}


void tsv::parser( const QString& filepath, std::function<void( const QStringList& )> cb ) {
	QFile file( filepath );
	if( !file.open( QIODevice::ReadOnly ) ) {
		QString errStr = $F( "error: %s", file.errorString() );
		qDebug() << errStr;
		return;
	}
	QTextStream in( &file );
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	in.setCodec( "UTF-8" );
#else
	in.setEncoding( QStringConverter::Utf8 );
	//ts.setEncoding( bUtf8 ? QStringConverter::Utf8 : QStringConverter::Latin1 );
#endif
	if( in.atEnd() )return;

	auto s = in.readLine();// 一行目はヘッダ扱いとして無視する
	//auto s2 = in.readLine();// 一行目はヘッダ扱いとして無視する
	//auto s4 = in.readLine();// 一行目はヘッダ扱いとして無視する

	while( !in.atEnd() ) {
		auto ss = in.readLine().split( "\t" );
		cb( ss );
	}
}

namespace fs {
	inline void internalDirIterator( QString path, QString searchPattern, QDir::Filters filters, SearchOption searchOption, std::function<bool( QString )> cb ) {

		QStringList nameFilters = searchPattern.toLower().split( ";" );

		QDirIterator::IteratorFlags iteratorFlags = QDirIterator::IteratorFlag::NoIteratorFlags;
		if( searchOption == SearchOption::AllDirectories ) {
			iteratorFlags = QDirIterator::IteratorFlag::Subdirectories;
		}
		iteratorFlags |= QDirIterator::IteratorFlag::FollowSymlinks;

		QDirIterator it( path, nameFilters, filters, iteratorFlags );
		while( it.hasNext() ) {
			if( !cb( it.next() ) )break;
		}
	}

	void enumerateFiles( QString path, QString searchPattern, SearchOption searchOption, std::function<bool( const QString& )> cb ) {
		enumerateFiles( path, searchPattern, searchOption, (QDir::Filters) 0, cb );
	}

	void enumerateFiles( QString path, QString searchPattern, SearchOption searchOption, QDir::Filters filterFlags, std::function<bool( const QString& )> cb ) {
		internalDirIterator(
			path,
			searchPattern,
			QDir::Files | filterFlags,
			searchOption,
			cb
		);
	}

	void enumerateDirectories( QString path, QString searchPattern, SearchOption searchOption, std::function<bool( const QString& )> cb ) {
		enumerateDirectories( path, searchPattern, searchOption, (QDir::Filters) 0, cb );
	}

	void enumerateDirectories( QString path, QString searchPattern, SearchOption searchOption, QDir::Filters filterFlags, std::function<bool( const QString& )> cb ) {
		internalDirIterator(
			path,
			searchPattern,
			QDir::Dirs | QDir::NoDot | QDir::NoDotDot | filterFlags,
			searchOption,
			cb
		);
	}


	/////////////////////////////////////////
	QStringList getFiles( QString path, QString searchPattern, SearchOption searchOption ) {
		return getFiles( path, searchPattern, searchOption, (QDir::Filters) 0 );
	}


	/////////////////////////////////////////
	QStringList getFiles( QString path, QString searchPattern, SearchOption searchOption, QDir::Filters filterFlags ) {
		QDir::Filters filters = QDir::Files;
		filters |= filterFlags;

		QStringList nameFilters = searchPattern.split( ";" );
		QStringList result;

		QDirIterator::IteratorFlags iteratorFlags = QDirIterator::IteratorFlag::NoIteratorFlags;
		if( searchOption == SearchOption::AllDirectories ) {
			iteratorFlags = QDirIterator::IteratorFlag::Subdirectories;
		}
		iteratorFlags |= QDirIterator::IteratorFlag::FollowSymlinks;

		QDirIterator it( path, nameFilters, filters, iteratorFlags );
		while( it.hasNext() ) result << it.next();
		return result;
	}


	/////////////////////////////////////////
	QStringList getDirectories( QString path, QString searchPattern, SearchOption searchOption ) {
		return getDirectories( path, searchPattern, searchOption, QDir::NoDotAndDotDot );
	}


	/////////////////////////////////////////
	QStringList getDirectories( QString path, QString searchPattern, SearchOption searchOption, QDir::Filters filterFlags ) {
		QDir::Filters filters = QDir::Dirs | QDir::NoDotAndDotDot;
		filters |= filterFlags;

		QStringList nameFilters = searchPattern.split( ";" );

		// 対象フラグ  
		//QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags;
		//flags = QDirIterator::Subdirectories;

		QDirIterator::IteratorFlags iteratorFlags = QDirIterator::IteratorFlag::NoIteratorFlags;
		if( searchOption == SearchOption::AllDirectories ) {
			iteratorFlags = QDirIterator::IteratorFlag::Subdirectories;
		}
		iteratorFlags |= QDirIterator::IteratorFlag::FollowSymlinks;

		QStringList result;

		QDirIterator it( path, nameFilters, filters, iteratorFlags );
		while( it.hasNext() ) {
			auto path = it.next();
			//if( path[ path.size() - 1 ] == "." )continue;
			//auto fileinfo = QFileInfo(  );
				//addMyItem( fileinfo );
			result << path;
		}
		return result;
	}


	void mkdir( const QString& path ) {
		if( fs::isExistDirectory( path ) )return;

		QDir dir;

		auto finfo = QFileInfo( path );
		if( finfo.isAbsolute() ) {
			QString p;
			for( auto& s : path.split( "/" ) ) {
				p += p.isEmpty() ? s : "/" + s;
				if( fs::isExistDirectory( p ) )continue;
				dir.mkdir( p );
			}
		}

		if( !dir.mkdir( path ) ) {
			// エラーの場合の処理
		}
	}

	void cp( const QString& src, const QString& dst ) {
		if( isExistFile( src ) ) {
			fs::mkdir( path::getDirectoryName( dst ) );
			// タイムスタンプ更新が腐ってるので消してコピーし直す
			if( isExistFile( dst ) ) {
				QFile::remove( dst );
			}
			QFile::copy( src, dst );
			// ファイルの更新時間が変更されない
			//auto finfo = QFileInfo( src );
			//QFile( dst ).setFileTime( finfo.lastModified(), QFile::FileTime::FileModificationTime );
		}
	}

	void mv( const QString& src, const QString& dst ) {
		if( isExistDirectory( src ) ) {
			QDir dir( path::getDirectoryName( src ) );
			dir.rename( path::getFileName( src ), path::getFileName( dst ) );
		}
		if( isExistFile( src ) ) {
			QFile f( src );
			f.rename( dst );
		}
	}


	void rmDir( const QString& path ) {
		//if( isExistFile( src ) ) {
		//	QFile f( src );
		//	f.rename( dst );
		//}
		auto ff = QFileInfo( path );
		auto abso = ff.absolutePath();
		QDir( path::getDirectoryName( ff.absolutePath() ) ).rmdir( path::getFileName( path ) );
	}

	QByteArray readAll( const QString& fileName ) {
		QFile file( fileName );
		if( !file.open( QIODevice::ReadOnly ) ) {
			return nullptr;
		}

		return file.readAll();
	}

	bool writeByteArray( const QString& fileName, const QByteArray& data ) {
		QFile file( fileName );
		if( !file.open( QIODevice::WriteOnly ) ) {
			//errStr = "ファイル(" + fileInfo.suffix() + ")オープンエラー:" + file.errorString();
			qDebug() << "file.open error: " << fileName;
			return false;
		}
		file.write( data );
		return true;
	}


	QString readAllText( const QString& filePath, Encoding encoding ) {
		if( !fs::isExistFile( filePath ) )return "";
		QFile f( filePath );
		f.open( QFile::ReadOnly | QFile::Text );
		QTextStream in( &f );

		if( encoding == Encoding::UTF8 || encoding == Encoding::UTF8N ) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			in.setCodec( "UTF-8" );
#else
			in.setEncoding( QStringConverter::Utf8 );
#endif
		}
		if( encoding == Encoding::Shift_JIS ) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			in.setCodec( "Shift-JIS" );
#else
			//in.setEncoding( QStringConverter::Utf8 );
#endif
		}

		return in.readAll();
	}

	/////////////////////////////////////////
	QStringList readAllLines( const QString& filePath, Encoding encoding ) {
		QFile file( filePath );
		QStringList result;

		if( !file.open( QIODevice::ReadOnly | QFile::Text ) ) {
			//QString errStr = "ファイル(" + fileInfo.suffix() + ")オープンエラー:" + file.errorString();
			qDebug() << "error readAllLines";
			return result;
		}
		QTextStream in( &file );

		if( encoding == Encoding::UTF8 || encoding == Encoding::UTF8N ) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			in.setCodec( "UTF-8" );
#else
			in.setEncoding( QStringConverter::Utf8 );
#endif
		}
		if( encoding == Encoding::Shift_JIS ) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			in.setCodec( "Shift-JIS" );
#else
			//in.setEncoding( QStringConverter::Utf8 );
#endif
		}

		while( !in.atEnd() ) result << in.readLine();

		return result;
	}


	/**
	 * @brief  指定したファイルから一行毎に読み取り、指定コールバックに渡して呼び出します
	 * @param  filePath: ファイルパス
	 * @param  encoding: テキストエンコーディング
	 * @param  cb:       コールバック
	 */
	bool readAllLines( const QString& filePath, Encoding encoding, std::function<void( const QString& )> cb ) {
		QFile file( filePath );
		QStringList result;

		if( !file.open( QIODevice::ReadOnly | QFile::Text ) ) {
			//QString errStr = "ファイル(" + fileInfo.suffix() + ")オープンエラー:" + file.errorString();
			qDebug() << "error readAllLines: " << filePath;
			return false;
		}
		QTextStream in( &file );

		if( encoding == Encoding::UTF8 || encoding == Encoding::UTF8N ) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			in.setCodec( "UTF-8" );
#else
			in.setEncoding( QStringConverter::Utf8 );
#endif
		}
		if( encoding == Encoding::Shift_JIS ) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			in.setCodec( "Shift-JIS" );
#else
			//in.setEncoding( QStringConverter::Utf8 );
#endif
		}

		while( !in.atEnd() ) cb( in.readLine() );

		return true;
	}

	/**
	 * @brief  指定したファイルから一行毎に読み取り、指定コールバックに渡して呼び出します
	 *         テキストエンコーディングはEncoding::UTF8が指定されます
	 * @param  filePath: ファイルパス
	 * @param  cb:       コールバック
	 */
	bool readAllLines( const QString& filePath, std::function<void( const QString& )> cb ) {
		return readAllLines( filePath, Encoding::UTF8, cb );
	}

	/////////////////////////////////////////
	void writeAllLines( const QString& filePath, const QStringList& lines, Encoding encoding ) {
		fs::mkdir( path::getDirectoryName( filePath ) );
		QString errStr;
		QFileInfo fileInfo( filePath );
		//if( fileInfo.exists() ) {
		//	/*errStr = "既存ファイル(" + fileInfo.suffix() + ")には出力できません"
		//		QMessageBox::information( this, tr( "ファイル出力エラー" ), errStr );*/
		//	return;
		//}
		QFile file( filePath );
		if( !file.open( QIODevice::WriteOnly ) ) {
			//errStr = "ファイル(" + fileInfo.suffix() + ")オープンエラー:" + file.errorString();
			qDebug() << "file.open error: " << filePath;
			return;
		}
		QTextStream out( &file );

		if( encoding == Encoding::UTF8 || encoding == Encoding::UTF8N ) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			out.setCodec( "UTF-8" );
#else
			out.setEncoding( QStringConverter::Utf8 );
#endif
		}
		if( encoding == Encoding::UTF8 ) {
			out.setGenerateByteOrderMark( true );
		}
		if( encoding == Encoding::Shift_JIS ) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			out.setCodec( "Shift-JIS" );
#else
			//out.setEncoding( QStringConverter::Utf8 );
#endif
		}

		for( auto& s : lines ) {
			out << s << Qt::endl;
		}
		file.close();
	}



	/////////////////////////////////////////
	/// @brief  新しいファイルを作成し、指定した文字列をそのファイルに書き込んだ後、ファイルを閉じます。
	///         既存のターゲット ファイルは上書きされます
	/// @param  書き込み先のファイル
	/// @param  ファイルに書き込む文字列
	/// @param  文字列に適用するエンコーディング
	void writeAllText( const QString& path, const QString& contents, Encoding encoding ) {
		fs::mkdir( path::getDirectoryName( path ) );
		QFile file( path );
		if( !file.open( QIODevice::WriteOnly ) ) {
			qWarning() << "fs::writeAllText: file open error. " << path;
			return;
		}
		QTextStream out( &file );

		if( encoding == Encoding::UTF8 || encoding == Encoding::UTF8N ) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			out.setCodec( "UTF-8" );
#else
			out.setEncoding( QStringConverter::Utf8 );
#endif
		}
		if( encoding == Encoding::UTF8 ) {
			out.setGenerateByteOrderMark( true );
		}
		if( encoding == Encoding::Shift_JIS ) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			out.setCodec( "Shift-JIS" );
#else
			//out.setEncoding( QStringConverter::Utf8 );
#endif
		}
		//QTextCodec* codec = QTextCodec::codecForName( "Shift-JIS" );
		out << contents;
	}


	/////////////////////////////////////////
	/// @brief  ファイルをゴミ箱へ移動します
	/// @params ファイルパスのリスト
	void moveToTrash( const QStringList& fileList ) {
#ifdef Q_OS_WIN
		for( auto& f : fileList ) {
			moveToTrash( f );
		}
#else
		qWarning << u8"未実装";
#endif
	}


	/////////////////////////////////////////
	/// @brief  ファイルをゴミ箱へ移動します
	/// @params ファイルパス
	int moveToTrash( const QString& inFullPath, bool silent /*= false*/ ) {
#ifdef Q_OS_WIN
		auto fullPath = path::separatorToOS( inFullPath );
		if( !isExistDirectory( fullPath ) && !isExistFile( fullPath ) ) return -1;

		SHFILEOPSTRUCT sf;

		ZeroMemory( &sf, sizeof( sf ) );
		sf.wFunc = FO_DELETE; // 削除を指示します。
		sf.fFlags = FOF_ALLOWUNDO; //「元に戻す」を有効にします。
		//sf.fFlags = sf.fFlags | FILEOP_FLAGS.FOF_NOERRORUI; //エラー画面を表示しません。
		// 単体ファイルの削除なので複数ファイル削除で使用されると進捗ダイアログがOn/Offが頻発する
		// 結果的にメインウィンドウのフォーカスが入れ食い状態になる
		if( silent ) {
			sf.fFlags = sf.fFlags | FOF_SILENT; //進捗ダイアログを表示しません。
		}
		//sf.fFlags = sf.fFlags | FILEOP_FLAGS.FOF_NOCONFIRMATION; //削除確認ダイアログを表示しません。

		auto* buf = (wchar_t*) malloc( sizeof( wchar_t ) * ( fullPath.size() + 2 ) );
		fullPath.toWCharArray( buf );
		buf[ fullPath.size() ] = 0;
		buf[ fullPath.size() + 1 ] = 0; //<- 終端を示す０がもう一つ要る!!
		sf.pFrom = buf;//
		auto result = SHFileOperation( &sf );
		free( buf );

		//if( result != 0 ) {
		//	// なんらかエラー
		//	return 1;
		//}
		return result;
#else
		return -1;
#endif
	}


	/////////////////////////////////////////
	void removeDirectoryRecursively( const QString& fullPath ) {
		QDir dir( fullPath );
		dir.removeRecursively();
	}

	bool isExistFile( const QString& path ) {
		return QFileInfo( path ).isFile();
	}

	bool isExistDirectory( const QString& path ) {
		return QFileInfo( path ).isDir();
	}

	bool isWritableFile( const QString& path ) {
		return QFileInfo( path ).isWritable();
	}
}
