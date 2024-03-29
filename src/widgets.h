﻿#pragma once

#include <QKeySequence>
#include <functional>
#include <QFutureWatcher>
#include <QTreeWidget>

class QAction;
class QCheckBox;
class QComboBox;
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
//class QTreeWidget;
class QTreeWidgetItem;
class QObject;
class QWidget;

namespace $GroupBox {
	QRadioButton* findSelectedRadioButton( QGroupBox* group );
}

namespace $PushButton {
	void clicked( QPushButton* w, std::function<void( bool )> func );
	void click( QPushButton* w, std::function<void()> func );
	void pressed( QPushButton* w, std::function<void()> func );
}

namespace $ToolButton {
	void clicked( QToolButton* w, std::function<void( bool )> func );
}

namespace $CheckBox {
	void stateChanged( QCheckBox* w, std::function<void( int )> func );
}

namespace $ComboBox {
	void currentIndexChanged( QComboBox* w, std::function<void( int )> func );
	void currentTextChanged( QComboBox* w, std::function<void( const QString& )> func );
}

namespace $RadioButton {
	void toggled( QRadioButton* w, std::function<void( bool )> func );
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
	template <class T>
	T* findItem( QList<QTreeWidgetItem*> itemList, const QString& text ) {
		for( auto& item :itemList ) {
			auto* p = dynamic_cast<T*>( item );
			if( !p )continue;
			if( p->text( 0 ) == text )return (T*) p;
		}
		return nullptr;
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

	QAction* create( const QString& text, std::function<void( void )> func, QObject* parent = nullptr );
	QAction* create( const QIcon& icon, std::function<void( void )> func, QObject* parent = nullptr );
	QAction* create( const QString& text, const QIcon& icon, std::function<void( void )> func, QObject* parent = nullptr );

	QAction* setShortcut( QWidget* w, QKeySequence::StandardKey key, std::function<void( void )> func );
}

namespace $FutureWatcher {
	void progressTextChanged( QFutureWatcher<void>* w, QObject* context, std::function<void( const QString& progressText )> func );
}
