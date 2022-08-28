#include "helper.h"

#include <QDir>


#include <QMap>
#include <QApplication>

#include <QTreeWidgetItem>
#include <QGroupBox>
#include <QRadioButton>
#include <QSettings>

//#define ENABLE_SOUND
#ifdef ENABLE_SOUND
#include <QSoundEffect>
#endif

#ifdef Q_OS_WIN
#include <QtWin>
#include <shlwapi.h>
#endif


namespace $ {

	void naturalSort( QStringList& files ) {
#ifdef Q_OS_WIN
		struct {
			bool operator()( const QString& a, const QString& b ) {
				int e = StrCmpLogicalW(
					(LPCWSTR) a.unicode(),
					(LPCWSTR) b.unicode() );
				return e < 0;
			}
		} pred;

		qSort( files.begin(), files.end(), pred );
#else
		files.sort();
#endif
	}


	bool match( const QString& s1, const QString& s2, std::function<void( QRegularExpressionMatch& )> func, QRegularExpression::MatchType matchType ) {
		if( s1.isEmpty() ) return false;

		QRegularExpression r( s2 );

		//r.setMinimal( true );
		QRegularExpressionMatch m = r.match( s1, matchType );

		if( m.hasMatch() ) {
			//	//R.@_ = mm[ 0 ].Groups;
				//func ? .Invoke( mm[ 0 ].Groups );
			if( func ) func( m );
			return true;
		}
		return false;
	}



	QString trimEnd( const QString& s, QString trim ) {
		QString ss = s;
		if( ss.endsWith( trim ) ) {
			ss.chop( 1 );
		}
		return ss;
	}
	QStringList select( const QStringList& lst, std::function<QString( const QString& )> func ) {
		QStringList result;
		for( auto& s : lst ) {
			result << func( s );
		}
		return result;
	}


	void setBoldFont( QTreeWidgetItem& item ) {
		auto ff = QFont( item.font( 0 ) );
		ff.setBold( true );
		item.setFont( 0, ff );
	}


	QPixmap getStdPixmap( QStyle::StandardPixmap id ) {
		return qApp->style()->standardPixmap( id );
	}



#ifdef Q_OS_WIN
	bool isDrakMode() {
		QSettings settings( "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", QSettings::NativeFormat );
		return settings.value( "AppsUseLightTheme" ) == 0;
	}
#endif

#ifdef ENABLE_SOUND

	QMap<QString, QSoundEffect*> soundCache;

	void $::playSound( const QString& filepath ) {
		if( soundCache.contains( filepath ) ) {
			soundCache[ filepath ]->play();
			return;
		}
		QSoundEffect* effect = new QSoundEffect();
		auto ur = QUrl::fromLocalFile( separatorToOS( filepath ) );
		effect->setSource( ur );
		effect->setVolume( 50 );
		effect->play();

		soundCache.insert( filepath, effect );
	}
#endif

}
