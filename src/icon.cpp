#include "icon.h"
#include "helper.h"
#include "path.h"
#include "fs.h"

#ifdef Q_OS_WIN
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#include <QtWin>
#endif
#include <shlwapi.h>
#endif

#include <QMap>
#include <QIcon>
#include <QFileInfo>
#include <QApplication>
#include <QDir>
#include <QMutex>


namespace icon {
	QMap<QString, QIcon> iconCache;
	QtAwesome* awesome;
	QVariantMap variantMap;

#ifdef Q_OS_WIN
	QMutex mutex;
	QIcon get( const QString& filePath ) {
		QMutexLocker _( &mutex );
		QString ss = path::separatorToOS( filePath );
		QFileInfo fileInfo( filePath );
		const wchar_t* filePathW = $::toWCharPtr( ss );
		unsigned int flags = SHGFI_ICON | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES;

		bool nonCache = false;
		auto suffix = fileInfo.suffix();
		if( suffix == "exe" || suffix == "ico" || suffix == "lnk" ) {
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
		else if( fileInfo.isFile() ) {
			if( iconCache.contains( fileInfo.suffix() ) ) {
				return iconCache[ fileInfo.suffix() ];
			}
		}
		else {
			return QIcon();
		}

		SHFILEINFO info;
		ZeroMemory( &info, sizeof( SHFILEINFO ) );

		const HRESULT hr = SHGetFileInfo(
			filePathW,
			fileInfo.isDir() ? FILE_ATTRIBUTE_DIRECTORY : 0,
			&info, sizeof( SHFILEINFO ), flags );

		if( info.hIcon ) {//
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			auto pixmap = QtWin::fromHICON( info.hIcon );
#else
			auto pixmap = QPixmap::fromImage( QImage::fromHICON( info.hIcon ) );
#endif
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

	QIcon get( QStyle::StandardPixmap id ) {
		return qApp->style()->standardIcon( id );
	}

}


