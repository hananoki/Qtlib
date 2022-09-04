#include "groupBox.h"

#include <QList>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>
#include <QTreeWidget>

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

namespace $PushButton {
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

namespace $TreeWidget {
	void itemClicked( QTreeWidget* w, std::function<void( QTreeWidgetItem* , int )> func ) {
		QObject::connect( w, &QTreeWidget::itemClicked, func );
	}
}

//	connect( treeWidget, &QTreeWidget::itemClicked, [&]( QTreeWidgetItem* item, int column ) {
//	static_cast<ItemBase*>( item )->itemClicked();
//	auto* folder = dynamic_cast<ItemFolder*>( item );
//	if( !folder )return;
//	make2( folder );
//	AppHelper::setSelectFolderPath( folder->path );
//} );
