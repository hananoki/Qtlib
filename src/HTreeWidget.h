#pragma once

#include <QTreeWidget>

//////////////////////////////////////////////////////////////////////////////////
class HTreeWidgetItem : public QTreeWidgetItem {
public:
	HTreeWidgetItem() : QTreeWidgetItem() {}
	HTreeWidgetItem( QTreeWidget* _treeWidget ) : treeWidget( _treeWidget ) {}

	// @brief  /(スラッシュ)を区切りとしてノードの繋がりを文字列で返す
	QString fullPath();
	QTreeWidget* treeWidget;

	template<class T>
	QList<T*> childItems() {
		QList<T*> lst;
		for( int i = 0; i < childCount(); i++ ) {
			auto* p = dynamic_cast<T*>( child( i ) );
			if( !p )continue;
			lst << p;
		}
		return lst;
	}

	template<class T>
	T* find( QString text ) {
		for( auto& p : childItems<T>() ) {
			if( p->text( 0 ) == text )return p;
		}
		return nullptr;
	}
};


//////////////////////////////////////////////////////////////////////////////////
class HTreeWidget : public QTreeWidget {
public:
	HTreeWidget( QWidget* parent = nullptr );

	template <class T>
	T* currentItem();

	template <class T>
	QList<T*> currentItems();

	QStringList getExpandItemPaths();

	void setExpandItemPaths( const QStringList& expandList );

	template <class T>
	T* removeTopLevelItem( T* item ) {
		int index = indexOfTopLevelItem( item );
		if( 0 <= index ) {
			return (T*) takeTopLevelItem( index );
		}
		return nullptr;
	}

	template <class T>
	QList<T*> topLevelItems() {
		QList<T*> lst;
		for( int i = 0; i < topLevelItemCount(); i++ ) {
			auto* p = dynamic_cast<T*>( topLevelItem( i ) );
			if( !p )continue;
			lst << p;
		}
		return lst;
	}
	template <>
	QList<QTreeWidgetItem*> topLevelItems() {
		QList<QTreeWidgetItem*> lst;
		for( int i = 0; i < topLevelItemCount(); i++ ) {
			lst << topLevelItem( i );
		}
		return lst;
	}

	template <class T>
	T* itemFromIndex( const QModelIndex& index ) const;

	void dragEnterEvent( QDragEnterEvent* e ) { if( onDragEnterEvent ) onDragEnterEvent( e ); }
	void dragMoveEvent( QDragMoveEvent* e ) { if( odDagMoveEvent )odDagMoveEvent( e ); }
	void dropEvent( QDropEvent* e ) { if( odDagMoveEvent )onDropEvent( e ); }

	std::function<void( QDragEnterEvent* ) > onDragEnterEvent;
	std::function<void( QDragMoveEvent* ) > odDagMoveEvent;
	std::function<void( QDropEvent* ) > onDropEvent;

private:
	void internalGetExpandNodeString( QTreeWidgetItem* node, QStringList& result );

	void keyPressEvent( QKeyEvent* event );
};



/////////////////////////////////////////
template <class T>
T* HTreeWidget::currentItem() {
	auto items = selectedItems();
	if( items.length() == 0 )return nullptr;
	return dynamic_cast<T*>( items[ 0 ] );
}

template <class T>
QList<T*> HTreeWidget::currentItems() {
	QList<T*> l;
	for( auto* p : selectedItems() ) {
		l << dynamic_cast<T*>( p );
	}
	return l;
}

template <class T>
T* HTreeWidget::itemFromIndex( const QModelIndex& index ) const {
	return dynamic_cast<T*>( QTreeWidget::itemFromIndex( index ) );
}
