﻿#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QSize>
#include <QPoint>
#include <QStringList>

#include <functional>


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

