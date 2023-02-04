#include "comboBox.h"

#include <QComboBox>


namespace $ComboBox {
	void currentIndexChanged( QComboBox* w, std::function<void( int index )> func ) {
		//QObject::connect( w, &QComboBox::currentIndexChanged, func );
	}

	void currentTextChanged( QComboBox* w, std::function<void( const QString& )> func ) {
		QObject::connect( w, &QComboBox::currentTextChanged, func );
	}
}
