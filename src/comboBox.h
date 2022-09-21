#pragma once

#include <functional>
#include <QStringList>

class QComboBox;

namespace $ComboBox {
	void currentIndexChanged( QComboBox* w, std::function<void( int )> func );
	void currentIndexChanged( QComboBox* w, std::function<void( const QString& )> func );

	template<typename T>
	void addItems( T& ui, QStringList ss ) {
		for( auto& s : ss ) {
			ui.addItem( s );
		}
	}

	template<typename T>
	void addItems( T* ui, QStringList ss ) {
		addItems<T>( *ui, ss );
	}
}
