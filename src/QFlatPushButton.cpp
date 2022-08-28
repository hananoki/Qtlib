#include "QFlatPushButton.h"
#include <QEvent>

QFlatPushButton::QFlatPushButton( QWidget* parent ) :
	QPushButton( parent )
{
	setFlat( true );
}

void QFlatPushButton::hoverLeave(){
	setFlat( true );
}

bool QFlatPushButton::event( QEvent* event ) {
	if( event->type() == QEvent::HoverEnter ) {
		setFlat( false );
	}

	if( event->type() == QEvent::HoverLeave ) {
		setFlat( true );
	}

	return QPushButton::event( event );
}
