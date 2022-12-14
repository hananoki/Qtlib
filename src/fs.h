#pragma once

#include <QByteArray>
#include <functional>

class QString;
class QStringList;

enum class Encoding : int {
	None,
	UTF8,
	UTF8N,
};

enum class SearchOption : int {
	TopDirectoryOnly,
	AllDirectories,
};

class binarySerializer {
public:
	static void write( const QString& filepath, std::function<void(  QDataStream& )> cb );
	static void read( const QString& filepath, std::function<void(  QDataStream& )> cb );
};

class tsv {
public:
	static void parser( const QString& filepath, std::function<void( const QStringList& )> cb );
};

namespace fs {
	void mkdir( const QString& path );
	void cp( const QString& src, const QString& dst );
	void mv( const QString& src, const QString& dst );

	void rmDir( const QString& path );

	QByteArray readAll( const QString& fileName );
	bool writeByteArray( const QString& fileName, const QByteArray& data );

	QString readAllText( const QString& filePath, Encoding encoding = Encoding::UTF8 );

	QStringList readAllLines( const QString& filePath, Encoding encoding = Encoding::UTF8 );
	void writeAllLines( const QString& filePath, const QStringList& lines, Encoding encoding = Encoding::UTF8 );

	
	void writeAllText( const QString& path, const QString& contents, Encoding encoding );

	void moveToTrash( const QStringList& fileList );
	int moveToTrash( const QString& fullPath );

	void removeDirectoryRecursively( const QString& fullPath );
	bool isExistFile( const QString& path );
	bool isExistDirectory( const QString& path );
	bool isWritableFile( const QString& path );

	// ラムダ式戻り値bool: true 列挙を継続する false 列挙を中止する
	void enumerateFiles( QString path, QString searchPattern, SearchOption searchOption, std::function<bool( QString )> cb );
	void enumerateDirectories( QString path, QString searchPattern, SearchOption searchOption, std::function<bool( QString )> cb );

	QStringList getFiles( QString path, QString searchPattern, SearchOption searchOption = SearchOption::TopDirectoryOnly );
	QStringList getDirectories( QString path, QString searchPattern, SearchOption searchOption = SearchOption::TopDirectoryOnly );
}
