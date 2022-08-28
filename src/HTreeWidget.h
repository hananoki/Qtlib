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
class HTreeWidget : public QTreeWidget {
public:
	HTreeWidget( QWidget* parent = nullptr );

	template <class T>
	T* currentItem();

	QStringList getExpandItemPaths();

	void setExpandItemPaths( const QStringList& expandList );

private:
	void internalGetExpandNodeString( QTreeWidgetItem* node, QStringList& result );
};



/////////////////////////////////////////
template <class T>
T* HTreeWidget::currentItem() {
	return (T*) ( selectedItems()[ 0 ] );
}
