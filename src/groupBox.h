#pragma once

#include <functional>

class QRadioButton;
class QGroupBox;
class QPushButton;
class QLineEdit;
class QString;
class QTreeWidget;
class QTreeWidgetItem;
class QAction;
class QCheckBox;
class QIcon;
class QToolButton;

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

namespace $LineEdit {
	void textEdited( QLineEdit* w, std::function<void( const QString& )> func );
	void textChanged( QLineEdit* w, std::function<void( const QString& )> func );
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
}

namespace $Action {
	void triggered( QAction* w, std::function<void( void )> func );

	QAction* create( const QString& text, std::function<void( void )> func );
	QAction* create( const QIcon& icon, const QString& text, std::function<void( void )> func );
}
