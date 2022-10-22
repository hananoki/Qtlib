#include "json.h"

#include "fs.h"
#include <QFile>
#include <QTextStream>

namespace json {

	QSize toSize( const QJsonValue& s ) {
		if( s.isNull() )return QSize( 100, 100 );
		auto ss = s.toString().split( " " );

		if( ss.length() != 2 )return QSize( 100, 100 );
		return QSize( ss[ 0 ].toInt(), ss[ 1 ].toInt() );
	}

	QPoint toPoint( const QJsonValue& s ) {
		if( s.isNull() )return QPoint();
		auto ss = s.toString().split( " " );

		if( ss.length() != 2 )return QPoint();
		return QPoint( ss[ 0 ].toInt(), ss[ 1 ].toInt() );
	}

	QStringList toStringList( const QJsonValue& jsObj ) {
		QStringList result;
		for( QJsonValue s : jsObj.toArray() ) {
			result << s.toString();
		}
		return result;
	}

	bool read( const QString& filePath, std::function<void( const QJsonObject& )> cb ) {
		if( !fs::isExistFile( filePath ) )return false;

		auto txt = fs::readAll( filePath );

		if( txt.isEmpty() )return false;

		QJsonDocument jsonDoc = QJsonDocument::fromJson( txt );

		cb( jsonDoc.object() );

		return true;
	}


	void write( const QString& filePath, std::function<void( QJsonObject& )> cb ) {
		QFile saveFile( filePath );

		// save.jsonを開くことができなければ警告を出す
		if( !saveFile.open( QIODevice::WriteOnly ) ) {
			qWarning( "Couldn't open save.json" );
			return;
		}

		// QtでJsonを扱うためのオブジェクトを作製し、キーとそれに対応する値を保存する
		QJsonObject saveObject;
		cb( saveObject );

		saveFile.write( QJsonDocument( saveObject ).toJson() );
	}
}


