#include "path.h"

#include <QFileInfo>
#include <QDir>

namespace path {
	/////////////////////////////////////////
	QString getBaseName( const QString& filePath ) {
		return QFileInfo( filePath ).baseName();
	}

	/////////////////////////////////////////
	QString getFileName( const QString& filePath ) {
		return QFileInfo( filePath ).fileName();
	}


	/////////////////////////////////////////
	QString getDirectoryName( const QString& filePath ) {
		return QFileInfo( filePath ).absoluteDir().path();
	}

	/////////////////////////////////////////
	QString getSuffix( const QString& filePath ) {
		return QFileInfo( filePath ).completeSuffix();
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
		QString dst = QString( "%1/%2.%3" )
			.arg( fileInfo.absolutePath() )
			.arg( fileInfo.baseName() )
			.arg( suffix );
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
