#include "sound.h"
#include <QSoundEffect>
#include <QMap>
#include "path.h"


QMap<QString, QSoundEffect*> soundCache;

void $sound::play( const QString& filepath ) {
	if( soundCache.contains( filepath ) ) {
		soundCache[ filepath ]->play();
		return;
	}
	QSoundEffect* effect = new QSoundEffect();
	auto ur = QUrl::fromLocalFile( path::separatorToOS( filepath ) );
	effect->setSource( ur );
	effect->setVolume( 50 );
	effect->play();

	soundCache.insert( filepath, effect );
}
