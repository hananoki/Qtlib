#pragma once

#include <functional>

class QAction;
class QCheckBox;
class QGroupBox;
class QIcon;
class QLineEdit;
class QListWidget;
class QRadioButton;
class QPoint;
class QPushButton;
class QSlider;
class QString;
class QToolButton;
class QTreeWidget;
class QTreeWidgetItem;

namespace $GroupBox {
	QRadioButton* findSelectedRadioButton( QGroupBox* group );
}

namespace $PushButton {
	void clicked( QPushButton* w, std::function<void( bool )> func );
	void pressed( QPushButton* w, std::function<void()> func );
}

namespace $ToolButton {
	void clicked( QToolButton* w, std::function<void( bool )> func );
}

namespace $CheckBox {
	void stateChanged( QCheckBox* w, std::function<void( int )> func );
}

namespace $RadioButton {
	void toggled( QRadioButton* w, std::function<void( bool  )> func );
}

namespace $LineEdit {
	void textEdited( QLineEdit* w, std::function<void( const QString& )> func );
	void textChanged( QLineEdit* w, std::function<void( const QString& )> func );
}

namespace $Slider {
	void valueChanged( QSlider* w, std::function<void( int value )> func );
}

namespace $TreeWidget {
	template<typename T>
	void forTopLevelItems( QTreeWidget* w, std::function<void( T* )> func ) {
		for( int i = 0; i < w->topLevelItemCount(); i++ ) {
			func( (T*) w->topLevelItem( i ) );
		}
	}
	void itemClicked( QTreeWidget* w, std::function<void( QTreeWidgetItem*, int )> func );
	void itemChanged( QTreeWidget* w, std::function<void( QTreeWidgetItem*, int )> func );
	void itemSelectionChanged( QTreeWidget* w, std::function<void( void )> func );
	void itemDoubleClicked( QTreeWidget* w, std::function<void( QTreeWidgetItem* item, int column )> func );
	void customContextMenuRequested( QTreeWidget* w, std::function<void( const QPoint& pos )> func );
}

namespace $ListWidget {
	void itemSelectionChanged( QListWidget* w, std::function<void( void )> func );
}

namespace $Action {
	void triggered( QAction* w, std::function<void( void )> func );

	QAction* create( const QString& text, std::function<void( void )> func );
	QAction* create( const QIcon& icon, std::function<void( void )> func );
	QAction* create( const QString& text, const QIcon& icon, std::function<void( void )> func );
}
