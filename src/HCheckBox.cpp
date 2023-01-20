#include "HCheckBox.h"
#include "widgets.h"
#include "IConfigChanged.h"

void HCheckBox::bind( bool* t, QObject* config /*= nullptr*/ ) {
	setChecked( *t );
	$CheckBox::stateChanged( this, [this, t, config]( int state ) {
		//config.setIgnoreFlag( state );
		*t = state;
		auto* c = dynamic_cast<IConfigChanged*>( config );
		if( c ) {
			c->changedValue();
		}
		emit stateChanged();
	} );
}
