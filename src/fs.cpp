#include "helper.h"
#include "fs.h"
#include "path.h"

#include <QString>
#include <QStringList>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#ifdef Q_OS_WIN
#include <QtWin>
#endif
#include <QDebug>

void binarySerializer::write( const QString& filepath, std::function<void( QDataStream& )> cb ) {
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
	in.setCodec( "UTF-8" );
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

	QStringList getFiles( QString path, QString searchPattern, SearchOption searchOption ) {
		QDir::Filters filters = QDir::Files;
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


	QStringList getDirectories( QString path, QString searchPattern, SearchOption searchOption ) {
		QDir::Filters filters = QDir::Dirs | QDir::NoDot | QDir::NoDotDot;
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

		if( !dir.mkdir( path ) ) {
			// エラーの場合の処理
		}
	}


	void mv( const QString& src, const QString& dst ) {
		if( isExistFile( src ) ) {
			QFile f( src );
			f.rename( dst );
		}
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
			in.setCodec( "UTF-8" );
		}
		return in.readAll();
	}


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
			in.setCodec( "UTF-8" );
		}

		while( !in.atEnd() ) result << in.readLine();

		return result;
	}


	void writeAllLines( const QString& filePath, const QStringList& lines, Encoding encoding ) {
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
			out.setCodec( "UTF-8" );
		}
		if( encoding == Encoding::UTF8 ) {
			out.setGenerateByteOrderMark( true );
		}

		for( auto& s : lines ) {
			out << s << endl;
		}
		file.close();
	}


	void moveToTrash( const QStringList& fileList ) {
#ifdef Q_OS_WIN
		for( auto& f : fileList ) {
			moveToTrash( f );
		}
#endif
	}


	int moveToTrash( const QString& inFullPath ) {
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
		sf.fFlags = sf.fFlags | FOF_SILENT; //進捗ダイアログを表示しません。
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
		return QFileInfo( path ).exists();
	}

	bool isExistDirectory( const QString& path ) {
		return QDir( path ).exists();
	}

	bool isWritableFile( const QString& path ) {
		return QFileInfo( path ).isWritable();
	}
}
