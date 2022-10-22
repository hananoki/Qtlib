#include "HFlatPushButton.h"
#include <QEvent>

HFlatPushButton::HFlatPushButton( QWidget* parent ) :
	QPushButton( parent )
{
	setFlat( true );
}

void HFlatPushButton::hoverLeave(){
	setFlat( true );
}

bool HFlatPushButton::event( QEvent* event ) {
	if( event->type() == QEvent::HoverEnter ) {
		setFlat( false );
	}

	if( event->type() == QEvent::HoverLeave ) {
		setFlat( true );
	}

	return QPushButton::event( event );
}
