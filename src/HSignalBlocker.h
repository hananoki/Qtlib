#pragma once

#include <QWidget>

class HSignalBlocker {
	QWidget* self;
public:
	HSignalBlocker( QWidget* p ) :self( p ) {
		for( auto& w : p->findChildren<QWidget*>() ) {
			w->blockSignals( true );
		}
		p->blockSignals( true );
	}

	~HSignalBlocker() {
		for( auto& w : self->findChildren<QWidget*>() ) {
			w->blockSignals( false );
		}
		self->blockSignals( false );
	}
};