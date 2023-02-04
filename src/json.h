#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QMap>
#include <QSize>
#include <QPoint>
#include <QStringList>

#include <functional>

#define DECLARE_ENUM(type) \
namespace json { \
	template<> \
	inline type GetValue<type>( const QJsonValue& value ) { \
		return (type) value.toInt(); \
	} \
	template<> \
	inline void SetValue<type>( QJsonObject& jsonObj, const QString& name, const type& value ) { \
		jsonObj[ name ] = (int) value; \
	} \
}

using StringKeyValue = QMap<QString, QString>;

namespace json {

	bool read( const QString& filePath, std::function<void( const QJsonObject& )> cb );
	void write( const QString& filePath, std::function<void( QJsonObject& )> cb );

	QStringList toStringList( const QJsonValue& s );
	QSize toSize( const QJsonValue& s );
	QPoint toPoint( const QJsonValue& s );

	inline QString toString( const QPoint& q ) {
		return QString( "%1 %2" ).arg( q.x() ).arg( q.y() );
	}
	inline QString toString( const QSize& q ) {
		return QString( "%1 %2" ).arg( q.width() ).arg( q.height() );
	}

	template<typename  T>
	inline void SetValue( QJsonObject& jsonObj, const QString& name, const T& value ) {
		jsonObj[ name ] = value;
	}


	template<>
	inline void SetValue<QChar>( QJsonObject& jsonObj, const QString& name, const QChar& value ) {
		jsonObj[ name ] = value.unicode();
	}

	template<>
	inline void SetValue<QPoint>( QJsonObject& jsonObj, const QString& name, const QPoint& value ) {
		jsonObj[ name ] = json::toString( value );
	}

	template<>
	inline void SetValue<QSize>( QJsonObject& jsonObj, const QString& name, const QSize& value ) {
		jsonObj[ name ] = json::toString( value );
	}

	template<>
	inline void SetValue<QStringList>( QJsonObject& jsonObj, const QString& name, const QStringList& value ) {
		jsonObj[ name ] = QJsonArray::fromStringList( value );
	}


	template<typename  T>
	inline T GetValue( const QJsonValue& value ) {
		static_assert( 0, "Unimplemented type selected" );
	}

	template<>
	inline int GetValue<int>( const QJsonValue& value ) {
		return 	value.toInt();
	}

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	template<>
	inline QChar GetValue<QChar>( const QJsonValue& value ) {
		return value.toInt();
	}
#endif

	template<>
	inline bool GetValue<bool>( const QJsonValue& value ) {
		return 	value.toBool();
	}
	template<>
	inline QString GetValue<QString>( const QJsonValue& value ) {
		return 	value.toString();
	}
	template<>
	inline QStringList GetValue<QStringList>( const QJsonValue& value ) {
		return 	toStringList( value );
	}
	template<>
	inline QSize GetValue<QSize>( const QJsonValue& value ) {
		return toSize( value );
	}
	template<>
	inline QPoint GetValue<QPoint>( const QJsonValue& value ) {
		return toPoint( value );
	}
}


namespace json {
	template<>
	inline StringKeyValue GetValue<StringKeyValue>( const QJsonValue& value ) {
		StringKeyValue lst;
		for( QJsonValue s : value.toArray() ) {
			lst.insert( s[ "key" ].toString(), s[ "value" ].toString() );
		}
		return 	lst;
	}

	template<>
	inline void SetValue<StringKeyValue>( QJsonObject& jsonObj, const QString& name, const StringKeyValue& value ) {
		QJsonArray jsonArr;
		for( auto& k : value.keys() ) {
			QJsonObject jsObj;
			jsObj[ "key" ] = k;
			jsObj[ "value" ] = value[ k ];
			jsonArr.append( jsObj );
		}
		jsonObj[ name ] = jsonArr;
	}
}

