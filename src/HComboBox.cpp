#include "HComboBox.h"
#include "widgets.h"
#include "IConfigChanged.h"

void HComboBox::bind( int* t, QObject* config /*= nullptr*/ ) {
	setCurrentIndex( *t );
	$ComboBox::currentIndexChanged( this, [this, t, config]( int index ) {
		//config.setIgnoreFlag( state );
		*t = index;
		auto* c = dynamic_cast<IConfigChanged*>( config );
		if( c ) {
			c->changedValue();
		}
		emit currentTextChanged();
	} );
}

void HComboBox::bind( QString* t, QObject* config /*= nullptr*/ ) {
	setCurrentText( *t );
	$ComboBox::currentTextChanged( this, [this, t, config]( const QString& text ) {
		//config.setIgnoreFlag( state );
		*t = text;
		auto* c = dynamic_cast<IConfigChanged*>( config );
		if( c ) {
			c->changedValue();
		}
		emit currentTextChanged();
	} );
}

