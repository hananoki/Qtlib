#include "path.h"

#include <QFileInfo>
#include <QDir>

namespace path {
	/////////////////////////////////////////
	QString getBaseName( const QString& filePath ) {
		auto finfo = QFileInfo( filePath );
		if( finfo.exists() ) {
			return QFileInfo( filePath ).baseName();
		}
		auto fname = filePath;
		if( filePath.contains( "/" ) ) {
			fname = getFileName( filePath );
		}
		auto lst = filePath.split( "." );
		lst.takeLast();
		return lst.join( "." );
	}

	/////////////////////////////////////////
	QString getFileName( const QString& filePath ) {
		auto finfo = QFileInfo( filePath );
		if( finfo.exists() ) {
			return QFileInfo( filePath ).fileName();
		}
		if( filePath.contains( "/" ) ) {
			auto lst = filePath.split( "/" );
			return lst.last();
		}
		return filePath;
	}


	/////////////////////////////////////////
	QString getDirectoryName( const QString& filePath ) {
		auto finfo = QFileInfo( filePath );
		if( finfo.exists() ) {
			return QFileInfo( filePath ).absoluteDir().path();
		}
		if( filePath.contains( "/" ) ) {
			auto lst = filePath.split( "/" );
			lst.removeLast();
			return lst.join( "/" );
		}
		return "";
	}

	/////////////////////////////////////////
	QString getSuffix( const QString& filePath ) {
		return QFileInfo( filePath ).completeSuffix();
	}

	/////////////////////////////////////////
	bool hasSuffix( const QString& filePath, const QString& suffix ) {
		return getSuffix( filePath ).toLower() == suffix.toLower();
	}

	/////////////////////////////////////////
	//QString getExtension( const QString& filePath ) {
	//	auto ext = QFileInfo( filePath ).completeSuffix();
	//	if( ext.isEmpty() )return "";
	//	return "." + ext;
	//}


	/////////////////////////////////////////
	QString changeSuffix( const QString& filepath, const QString& suffix ) {
		QFileInfo fileInfo( filepath );
		QString dst;
		if( fileInfo.isAbsolute() ) {
			dst = QString( "%1/%2.%3" )
				.arg( fileInfo.absolutePath() )
				.arg( fileInfo.baseName() )
				.arg( suffix );
		}
		else {
			dst = QString( "%1.%2" )
				.arg( fileInfo.baseName() )
				.arg( suffix );
		}
		return dst;
	}


	/////////////////////////////////////////
	QString quote( const QString& s ) {
		if( s.isNull() )return "";
		return '"' + s + '"';
	}


	/////////////////////////////////////////
	QString separatorToOS( QString s ) {
		if( s.isNull() )return "";
		if( s.isEmpty() ) return "";
		return s.replace( '/', QDir::separator() );
	}


	/////////////////////////////////////////
	QString separatorToSlash( QString s ) {
		if( s.isNull() )return "";
		if( s.isEmpty() ) return "";
		return s.replace( '\\', "/" );
	}
}

namespace environment {
	QString currentDirectory() {
		return  QDir::current().canonicalPath();
	}
}
