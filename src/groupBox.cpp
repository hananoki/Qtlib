#include "groupBox.h"

#include <QList>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>
#include <QTreeWidget>
#include <QAction>
#include <QCheckBox>
#include <QToolButton>

namespace $GroupBox {
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

namespace $PushButton {
	void clicked( QPushButton* w, std::function<void( bool )> func ) {
		QObject::connect( w, &QPushButton::clicked, func );
	}
	void pressed( QPushButton* w, std::function<void()> func ) {
		QObject::connect( w, &QPushButton::pressed, func );
	}
}

namespace $ToolButton {
	void clicked( QToolButton* w, std::function<void( bool )> func ) {
		QObject::connect( w, &QToolButton::clicked, func );
	}
}

namespace $CheckBox {
	void stateChanged( QCheckBox* w, std::function<void( int )> func ) {
		QObject::connect( w, &QCheckBox::stateChanged, func );
	}
}

namespace $LineEdit {
	void textEdited( QLineEdit* w, std::function<void( const QString& )> func ) {
		QObject::connect( w, &QLineEdit::textEdited, func );
	}
	void textChanged( QLineEdit* w, std::function<void( const QString& )> func ) {
		QObject::connect( w, &QLineEdit::textChanged, func );
	}
}

namespace $TreeWidget {
	void itemClicked( QTreeWidget* w, std::function<void( QTreeWidgetItem*, int )> func ) {
		QObject::connect( w, &QTreeWidget::itemClicked, func );
	}
	void itemChanged( QTreeWidget* w, std::function<void( QTreeWidgetItem*, int )> func ) {
		QObject::connect( w, &QTreeWidget::itemChanged, func );
	}
	void itemSelectionChanged( QTreeWidget* w, std::function<void( void )> func ) {
		QObject::connect( w, &QTreeWidget::itemSelectionChanged, func );
	}
}

namespace $Action {
	void triggered( QAction* w, std::function<void( void )> func ) {
		QObject::connect( w, &QAction::triggered, func );
	}
	QAction* create( const QString& text, std::function<void( void )> func ) {
		return $Action::create( QIcon(), text, func );
	}
	QAction* create( const QIcon& icon, const QString& text, std::function<void( void )> func ) {
		QAction* a = new QAction( icon, text );
		QObject::connect( a, &QAction::triggered, func );
		return a;
	}
}
