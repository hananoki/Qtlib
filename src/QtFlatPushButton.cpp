#include "QtFlatPushButton.h"
#include <QEvent>

QtFlatPushButton::QtFlatPushButton( QWidget* parent ) :
	QPushButton( parent )
{
	setFlat( true );
}

void QtFlatPushButton::hoverLeave(){
	setFlat( true );
}

bool QtFlatPushButton::event( QEvent* event ) {
	if( event->type() == QEvent::HoverEnter ) {
		setFlat( false );
	}

	if( event->type() == QEvent::HoverLeave ) {
		setFlat( true );
	}

	return QPushButton::event( event );
}
