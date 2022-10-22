#pragma once

#include <QString>

namespace path {
	QString getBaseName( const QString& filePath );
	QString getFileName( const QString& filePath );
	QString getDirectoryName( const QString& filePath );
	//QString getExtension( const QString& filePath );
	QString getSuffix( const QString& filePath );

	QString changeSuffix( const QString& filepath, const QString& ext );
	QString quote( const QString& filePath );
	QString separatorToOS( QString s );
	QString separatorToSlash( QString s );
}

namespace environment {
	QString currentDirectory(  );
};
