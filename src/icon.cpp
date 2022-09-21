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

#include "QtAwesome/QtAwesome.h"

namespace icon {
	QMap<QString, QIcon> iconCache;
	QtAwesome* awesome;
	QVariantMap variantMap;

#ifdef Q_OS_WIN
	QIcon get( const QString& filePath ) {
		
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

	void initQtAwesome( float scaleFactor /*= 1.0f*/, QColor color /*= "#FFF"*/ ) {
		awesome = new QtAwesome( qApp );
		awesome->initFontAwesome();
		awesome->setDefaultOption( "scale-factor", scaleFactor );
		variantMap.insert( "color", color );
		variantMap.insert( "color-selected", color );
		variantMap.insert( "color-active", color );
		//variantMap.insert( "scale-factor", 0.5 );
		/*
		    setDefaultOption( "color", QColor(50,50,50) );
    setDefaultOption( "color-disabled", QColor(70,70,70,60));
    setDefaultOption( "color-active", QColor(10,10,10));
    setDefaultOption( "color-selected", QColor(10,10,10));
		*/
	}

	QIcon get( QStyle::StandardPixmap id ) {
		return qApp->style()->standardIcon( id );
	}


#undef FA_TAG
#define FA_TAG(aa,en) \
	QIcon aa () { \
		return awesome->icon( en,variantMap ); \
	}
	namespace FA {
		FAA_LIST
	}
}


//#define ICON_FA_PAPERCLIP awesome->icon( fa::paperclip )
//#define ICON_FA_STICKYNOTE awesome->icon( fa::stickynote )

//#define ICON_FA_BRIEFCASE awesome->icon( fa::briefcase )
#define ICON_FA_BOOK awesome->icon( fa::book )
#define ICON_FA_STICKYNOTEO awesome->icon( fa::stickynoteo )
#define ICON_FA_ARCHIVE awesome->icon( fa::archive )
#define ICON_FA_CODEFORK awesome->icon( fa::codefork )
#define ICON_FA_CODEPEN awesome->icon( fa::codepen )
#define ICON_FA_CODE awesome->icon( fa::code )
#define ICON_FA_GEARS awesome->icon( fa::gears )
#define ICON_FA_COG awesome->icon( fa::cog )
#define ICON_FA_COGS awesome->icon( fa::cogs )
#define ICON_FA_PAINTBRUSH awesome->icon( fa::paintbrush )
//#define ICON_FA_PLUS awesome->icon( fa::plus )
//#define ICON_FA_MINUS awesome->icon( fa::minus )
//#define ICON_FA_CHECK awesome->icon( fa::check )
#define ICON_FA_COMMENT awesome->icon( fa::comment )
//#define ICON_FA_EDIT awesome->icon( fa::edit )
#define ICON_FA_ARROWSALT awesome->icon( fa::arrowsalt )
//#define ICON_FA_TRASH awesome->icon( fa::trasho )

