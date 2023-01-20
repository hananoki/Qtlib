#include "icon.h"
#include "helper.h"
#include "path.h"

#ifdef Q_OS_WIN
#include <QtWin>
#include <shlwapi.h>
#endif

#include <QMap>
#include <QIcon>
#include <QFileInfo>
#include <QApplication>
#include <QDir>
#include <QMutex>

//#include "QtAwesome/QtAwesome.h"

namespace icon {
	QMap<QString, QIcon> iconCache;
	QtAwesome* awesome;
	QVariantMap variantMap;

#ifdef Q_OS_WIN
	QMutex mutex;
	QIcon get( const QString& filePath ) {
		QMutexLocker _( &mutex );
		QString ss = path::separatorToOS( filePath );
		QFileInfo fileInfo( filePath  );
		const wchar_t* filePathW = $::toWCharPtr( ss );
		unsigned int flags = SHGFI_ICON | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES;

		bool nonCache = false;
		auto suffix = fileInfo.suffix();
		if( suffix == "exe" || suffix == "ico" ) {
			nonCache = true;
		}
		else if( fileInfo.isRoot() ) {
			if( iconCache.contains( filePath ) ) {
				return iconCache[ filePath ];
			}
		}
		else if( fileInfo.isDir() ) {
			// フォルダは * で通常使用できない名前で登録してある
			if( iconCache.contains( "*" ) ) {
				return iconCache[ "*" ];
			}
			ss = path::separatorToOS( QDir::currentPath() );
			filePathW = $::toWCharPtr( ss );
		}
		else {
			if( iconCache.contains( fileInfo.suffix() ) ) {
				return iconCache[ fileInfo.suffix() ];
			}
		}
		SHFILEINFO info;
		ZeroMemory( &info, sizeof( SHFILEINFO ) );
		
		const HRESULT hr = SHGetFileInfo(
			filePathW,
			fileInfo.isDir() ? FILE_ATTRIBUTE_DIRECTORY : 0,
			&info, sizeof( SHFILEINFO ), flags );

		if( info.hIcon ) {//
			auto pixmap = QtWin::fromHICON( info.hIcon );
			auto icon = QIcon( pixmap );
			if( !nonCache ) {
				if( fileInfo.isRoot() ) {
					iconCache.insert( filePath, icon );
				}
				else if( fileInfo.isDir() ) {
					iconCache.insert( "*", icon );
				}
				else {
					iconCache.insert( fileInfo.suffix(), icon );
				}
			}
			return icon;
		}
		return QIcon();
	}
#else
	QIcon get( const QString& filePath ) {
		return get( QStyle::SP_MessageBoxInformation );
	}
#endif

	//void initQtAwesome( float scaleFactor /*= 1.0f*/, QColor color /*= "#FFF"*/ ) {
	//	awesome = new QtAwesome( qApp );
	//	awesome->initFontAwesome();
	//	awesome->setDefaultOption( "scale-factor", scaleFactor );
	//	variantMap.insert( "color", color );
	//	variantMap.insert( "color-selected", color );
	//	variantMap.insert( "color-active", color );
	//	//variantMap.insert( "scale-factor", 0.5 );
	//	/*
	//	    setDefaultOption( "color", QColor(50,50,50) );
 //   setDefaultOption( "color-disabled", QColor(70,70,70,60));
 //   setDefaultOption( "color-active", QColor(10,10,10));
 //   setDefaultOption( "color-selected", QColor(10,10,10));
	//	*/
	//}

	QIcon get( QStyle::StandardPixmap id ) {
		return qApp->style()->standardIcon( id );
	}


//#undef FA_TAG
//#define FA_TAG(aa,en) \
//	QIcon aa () { \
//		return awesome->icon( en,variantMap ); \
//	}
//	namespace FA {
//		FAA_LIST
//	}
}


