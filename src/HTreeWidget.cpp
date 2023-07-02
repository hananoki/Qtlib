#include "HTreeWidget.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QFileInfo>
#include <QDateTime>

//////////////////////////////////////////////////////////////////////////////////
//HTreeWidgetItem::HTreeWidgetItem( QTreeWidget* view ) : treeWidget( view )
//{}
 QTreeWidget* HTreeWidgetItem::treeWidget() const {
	 Q_ASSERT( 0/*, "Do not use."*/ );
	return nullptr;
}

/////////////////////////////////////////
QString HTreeWidgetItem::fullPath() {
	QString result = text( 0 );

	QTreeWidgetItem* item = this;

	while( item->parent() != NULL ) {
		result = item->parent()->text( 0 ) + "##" + result;
		item = item->parent();
	}
	return result;
}

/////////////////////////////////////////
bool HTreeWidgetItem::checkState( int column ) {
	return 0 < QTreeWidgetItem::checkState( column ) ? true : false;
}


/////////////////////////////////////////
void HTreeWidgetItem::setLastModified( int column, const QFileInfo& finfo ) {
	setText( column, finfo.lastModified().toString( "yyyy/MM/dd hh:mm" ) );
}


//////////////////////////////////////////////////////////////////////////////////
HTreeWidget::HTreeWidget( QWidget* parent ) : QTreeWidget( parent ) {

}

/////////////////////////////////////////
void HTreeWidget::keyPressEvent( QKeyEvent* event ) {
	QTreeWidget::keyPressEvent( event );
	if( ( event->key() == Qt::Key_Up ) || ( event->key() == Qt::Key_Down ) ) {
		//static_cast<ItemBase*>( currentItem() )->itemClicked();
		emit itemClicked( QTreeWidget::currentItem(), 0);
	}

}
/////////////////////////////////////////
void HTreeWidget::mousePressEvent( QMouseEvent* e ) {

	if( onMousePressEvent ) {
		if( onMousePressEvent( e ) )return;
	}
	QTreeWidget::mousePressEvent(e);
}

/////////////////////////////////////////
QStringList HTreeWidget::getExpandItemPaths() {
	QStringList result;

	for( int i = 0; i < topLevelItemCount(); i++ ) {
		QTreeWidgetItem* p = topLevelItem( i );
		internalGetExpandNodeString( p, result );
	}

	return result;
}


/////////////////////////////////////////
void HTreeWidget::internalGetExpandNodeString( QTreeWidgetItem* node, QStringList& result ) {
	for( int i = 0; i < node->childCount(); i++ ) {
		QTreeWidgetItem* p = node->child( i );
		internalGetExpandNodeString( p, result );
	}

	if( !node->isExpanded() ) return;

	QString path = ( (HTreeWidgetItem*) node )->fullPath();
	if( 0 <= result.indexOf( path ) )return;
	result << path;
}



/////////////////////////////////////////
void HTreeWidget::setExpandItemPaths( const QStringList& expandList ) {
	//var nodes = treeView.Nodes.OfType<TreeNode>().ToList();

	auto getNodes = [&]() {
		QList< QTreeWidgetItem*> lst;
		for( int i = 0; i < topLevelItemCount(); i++ ) {
			lst << topLevelItem( i );
		}
		return lst;
	};
	auto getNodes2 = [&]( QTreeWidgetItem* item ) {
		QList< QTreeWidgetItem*> lst;
		for( int i = 0; i < item->childCount(); i++ ) {
			lst << item->child( i );
			//qDebug() << i << " " << item->child( i )->text( 0 );
		}
		return lst;
	};
	auto findList = []( QList< QTreeWidgetItem*> lst, QString text )-> QTreeWidgetItem* {
		for( auto* p : lst ) {
			if( p->text( 0 ) == text )return p;
		}
		return nullptr;
	};

	QList< QTreeWidgetItem*> nodes = getNodes();
	bool find = false;
	QTreeWidgetItem* findNode;
	for( auto& s : expandList ) {
		auto n = nodes;
		find = true;
		findNode = nullptr;
		for( auto nname : s.split( "##" ) ) {
			auto* node = findList( n, nname );
			if( node == nullptr ) {
				find = false;
				break;
			}
			findNode = node;
			n = getNodes2( node );// node.Nodes.OfType<TreeNode>().ToList();
		}
		if( !find ) continue;
		//Debug.Log( findNode.Text );
		findNode->setExpanded( true );
	}
}



