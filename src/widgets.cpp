#include "widgets.h"

#include <QList>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>
#include <QTreeWidget>
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QToolButton>
#include <QSlider>
#include <QListWidget>

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
	void click( QPushButton* w, std::function<void()> func ) {
		QObject::connect( w, &QPushButton::clicked, [=]( bool b ) {
			if( !b ) {
				func();
			}
		} );
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
	void stateChanged( QCheckBox* w, std::function<void( int state )> func ) {
		QObject::connect( w, &QCheckBox::stateChanged, func );
	}
}

namespace $ComboBox {
	void currentIndexChanged( QComboBox* w, std::function<void( int )> func ) {
		QObject::connect( w, qOverload<int>( &QComboBox::currentIndexChanged ), func );
	}
	void currentTextChanged( QComboBox* w, std::function<void( const QString& )> func ) {
		QObject::connect( w, &QComboBox::currentTextChanged, func );
	}
}

namespace $RadioButton {
	void toggled( QRadioButton* w, std::function<void( bool checked )> func ) {
		QObject::connect( w, &QRadioButton::toggled, func );
	}
}

namespace $LineEdit {
	void textEdited( QLineEdit* w, std::function<void( const QString& text )> func ) {
		QObject::connect( w, &QLineEdit::textEdited, func );
	}
	void textChanged( QLineEdit* w, std::function<void( const QString& text )> func ) {
		QObject::connect( w, &QLineEdit::textChanged, func );
	}
}

namespace $Slider {
	void valueChanged( QSlider* w, std::function<void( int value )> func ) {
		QObject::connect( w, &QSlider::valueChanged, func );
	}
}

namespace $TreeWidget {
	void itemClicked( QTreeWidget* w, std::function<void( QTreeWidgetItem* item, int column )> func ) {
		QObject::connect( w, &QTreeWidget::itemClicked, func );
	}
	void itemChanged( QTreeWidget* w, std::function<void( QTreeWidgetItem* item, int column )> func ) {
		QObject::connect( w, &QTreeWidget::itemChanged, func );
	}
	void itemSelectionChanged( QTreeWidget* w, std::function<void( void )> func ) {
		QObject::connect( w, &QTreeWidget::itemSelectionChanged, func );
	}
	void itemDoubleClicked( QTreeWidget* w, std::function<void( QTreeWidgetItem* item, int column )> func ) {
		QObject::connect( w, &QTreeWidget::itemDoubleClicked, func );
	}
	void customContextMenuRequested( QTreeWidget* w, std::function<void( const QPoint& pos )> func ) {
		QObject::connect( w, &QTreeWidget::customContextMenuRequested, func );
	}
}

namespace $ListWidget {
	void itemSelectionChanged( QListWidget* w, std::function<void( void )> func ) {
		QObject::connect( w, &QListWidget::itemSelectionChanged, func );
	}
}

namespace $Action {
	void triggered( QAction* w, std::function<void( void )> func ) {
		QObject::connect( w, &QAction::triggered, func );
	}
	QAction* create( const QString& text, std::function<void( void )> func, QObject* parent /*= nullptr*/ ) {
		return $Action::create( text, QIcon(), func, parent );
	}
	QAction* create( const QIcon& icon, std::function<void( void )> func, QObject* parent /*= nullptr*/ ) {
		return $Action::create( "", icon, func, parent );
	}
	QAction* create( const QString& text, const QIcon& icon, std::function<void( void )> func, QObject* parent /*= nullptr*/ ) {
		QAction* a = new QAction( icon, text, parent );
		QObject::connect( a, &QAction::triggered, func );
		return a;
	}
	QAction* setShortcut( QWidget* w, QKeySequence::StandardKey key, std::function<void( void )> func ) {
		QAction* shortcut = new QAction( w );
		shortcut->setShortcut( QKeySequence( key ) );
		w->addAction( shortcut );
		QObject::connect( shortcut, &QAction::triggered, func );
		return shortcut;
	}
}


namespace $FutureWatcher {
	void progressTextChanged( QFutureWatcher<void>* w, QObject* context, std::function<void( const QString& progressText )> func ) {
		QObject::connect( w,&QFutureWatcher<void>::progressTextChanged, context, func );
	}
}

