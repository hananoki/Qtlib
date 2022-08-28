#pragma once

#include <QStringList>

namespace comboBox {
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
