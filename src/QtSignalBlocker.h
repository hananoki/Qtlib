#pragma once

#include <QWidget>

class QtSignalBlocker {
	QWidget* self;
public:
	QtSignalBlocker( QWidget* p ) :self( p ) {
		for( auto& w : p->findChildren<QWidget*>() ) {
			w->blockSignals( true );
		}
	}

	~QtSignalBlocker() {
		for( auto& w : self->findChildren<QWidget*>() ) {
			w->blockSignals( false );
		}
	}
};