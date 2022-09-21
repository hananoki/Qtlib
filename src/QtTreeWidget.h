#pragma once

#include <QTreeWidget>

//////////////////////////////////////////////////////////////////////////////////
class HTreeWidgetItem : public QTreeWidgetItem {
public:
	HTreeWidgetItem( QTreeWidget* view );
	QString fullPath();
	QTreeWidget* treeWidget;
};


//////////////////////////////////////////////////////////////////////////////////
class QtTreeWidget : public QTreeWidget {
public:
	QtTreeWidget( QWidget* parent = nullptr );

	template <class T>
	T* currentItem();

	QStringList getExpandItemPaths();

	void setExpandItemPaths( const QStringList& expandList );

private:
	void internalGetExpandNodeString( QTreeWidgetItem* node, QStringList& result );

	void keyPressEvent( QKeyEvent* event );
};



/////////////////////////////////////////
template <class T>
T* QtTreeWidget::currentItem() {
	return dynamic_cast<T*>( selectedItems()[ 0 ] );
}
