#include "groupBox.h"

#include <QList>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>

namespace groupBox {
	/////////////////////////////////////////
	QRadioButton* findSelectedRadioButton( QGroupBox* group ) {
		QList<QRadioButton*>list = group->findChildren<QRadioButton*>();

		for( int i = 0; i < list.size(); i++ ) {
			if( list.at( i )->isChecked() ) {
				return list.at( i );
			}
		}
		return static_cast<QRadioButton*>( 0 );
	}
}

namespace pushbutton {
	void clicked( QPushButton* w, std::function<void( bool )> func ) {
		QObject::connect( w, &QPushButton::clicked, func );
	}
	void pressed( QPushButton* w, std::function<void()> func ) {
		QObject::connect( w, &QPushButton::pressed, func );
	}
}

namespace lineedit {
	void textEdited( QLineEdit* w, std::function<void( const QString& )> func ) {
		QObject::connect( w, &QLineEdit::textEdited, func );
	}
	void textChanged( QLineEdit* w, std::function<void( const QString& )> func ) {
		QObject::connect( w, &QLineEdit::textChanged, func );
	}
}