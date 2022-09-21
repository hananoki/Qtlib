#include "comboBox.h"

#include <QComboBox>


namespace $ComboBox {
	void currentIndexChanged( QComboBox* w, std::function<void( int )> func ) {
		QObject::connect( w, qOverload<int>( &QComboBox::currentIndexChanged ), func );
	}

	void currentIndexChanged( QComboBox* w, std::function<void( const QString& )> func ) {
		QObject::connect( w, qOverload<const QString&>( &QComboBox::currentIndexChanged ), func );
	}
}
