#pragma once

#include <QStyle>

class QIcon;
class QString;
class QtAwesome;

namespace icon {
	QIcon get( const QString& filePath );
	QIcon get( QStyle::StandardPixmap id );

	void initQtAwesome( float scaleFactor = 1.0f, QColor color = "#FFF" );


#define QT_ICON(xxx,yyy) inline QIcon xxx (){ return  icon::get( yyy ); }
#define QT_ICON_LIST \
		QT_ICON( SP_TitleBarMinButton, QStyle::SP_TitleBarMinButton) \
		QT_ICON( SP_TitleBarMaxButton, QStyle::SP_TitleBarMaxButton) \
		QT_ICON( SP_DirOpenIcon, QStyle::SP_DirOpenIcon) \
		QT_ICON( SP_DialogCloseButton, QStyle::SP_DialogCloseButton) \
		QT_ICON( SP_DialogSaveButton, QStyle::SP_DialogSaveButton) \
		QT_ICON( SP_TitleBarCloseButton, QStyle::SP_TitleBarCloseButton) \
		QT_ICON( SP_ArrowUp, QStyle::SP_ArrowUp) \
		QT_ICON( SP_MediaPlay, QStyle::SP_MediaPlay) \
		QT_ICON( SP_MediaPause, QStyle::SP_MediaPause) \
		QT_ICON( SP_MediaSeekForward, QStyle::SP_MediaSeekForward) \
		QT_ICON( SP_MediaSeekBackward, QStyle::SP_MediaSeekBackward) \
		QT_ICON( SP_MediaVolume, QStyle::SP_MediaVolume) \
		QT_ICON( SP_MessageBoxInformation, QStyle::SP_MessageBoxInformation) \
		QT_ICON( SP_MessageBoxWarning, QStyle::SP_MessageBoxWarning) \
		QT_ICON( SP_MessageBoxCritical, QStyle::SP_MessageBoxCritical)

	QT_ICON_LIST

#undef QT_ICON
#undef QT_ICON_LIST

#define FA_TAG(xxx,yyy) QIcon xxx ();
#define FAA_LIST \
		FA_TAG( arrowcircledown, fa::arrowcircledown ) \
		FA_TAG( arrowcircleleft, fa::arrowcircleleft ) \
		FA_TAG( arrowcircleodown, fa::arrowcircleodown ) \
		FA_TAG( arrowcircleoleft, fa::arrowcircleoleft ) \
\
		FA_TAG( arrowcircleoright, fa::arrowcircleoright ) \
		FA_TAG( arrowcircleoup, fa::arrowcircleoup ) \
		FA_TAG( arrowcircleright, fa::arrowcircleright ) \
		FA_TAG( arrowcircleup, fa::arrowcircleup ) \
\
		FA_TAG( arrowdown, fa::arrowdown ) \
		FA_TAG( arrowleft, fa::arrowleft ) \
		FA_TAG( arrowright, fa::arrowright ) \
		FA_TAG( arrowup, fa::arrowup ) \
\
		FA_TAG( arrows, fa::arrows ) \
		FA_TAG( arrowsalt, fa::arrowsalt ) \
		FA_TAG( arrowsh, fa::arrowsh ) \
		FA_TAG( arrowsv, fa::arrowsv ) \
\
		FA_TAG( bookmark, fa::bookmark ) \
		FA_TAG( bookmarko, fa::bookmarko ) \
		FA_TAG( briefcase, fa::briefcase ) \
		FA_TAG( cog, fa::cog ) \
		FA_TAG( cogs, fa::cogs ) \
		FA_TAG( gear, fa::gear ) \
		FA_TAG( gears, fa::gears ) \
		FA_TAG( columns, fa::columns ) \
		FA_TAG( codepen, fa::codepen ) \
		FA_TAG( code, fa::code ) \
		FA_TAG( dashboard, fa::dashboard ) \
		FA_TAG( group, fa::group ) \
		FA_TAG( feed, fa::feed ) \
		FA_TAG( ellipsisv, fa::ellipsisv ) \
\
		FA_TAG( star, fa::star ) \
		FA_TAG( starhalf, fa::starhalf ) \
		FA_TAG( starhalfempty, fa::starhalfempty ) \
		FA_TAG( starhalffull, fa::starhalffull ) \
		FA_TAG( starhalfo, fa::starhalfo ) \
		FA_TAG( staro, fa::staro ) \
\
		FA_TAG( file, fa::file ) \
		FA_TAG( filearchiveo, fa::filearchiveo ) \
		FA_TAG( fileaudioo, fa::fileaudioo ) \
		FA_TAG( filecodeo, fa::filecodeo ) \
		FA_TAG( fileexcelo, fa::fileexcelo ) \
		FA_TAG( fileimageo, fa::fileimageo ) \
		FA_TAG( filemovieo, fa::filemovieo ) \
		FA_TAG( fileo, fa::fileo ) \
		FA_TAG( filepdfo, fa::filepdfo ) \
		FA_TAG( filephotoo, fa::filephotoo ) \
		FA_TAG( filepictureo, fa::filepictureo ) \
		FA_TAG( filepowerpointo, fa::filepowerpointo ) \
		FA_TAG( filesoundo, fa::filesoundo ) \
		FA_TAG( filetext, fa::filetext ) \
		FA_TAG( filetexto, fa::filetexto ) \
		FA_TAG( filevideoo, fa::filevideoo ) \
		FA_TAG( filewordo, fa::filewordo ) \
		FA_TAG( filezipo, fa::filezipo ) \
		FA_TAG( fileso, fa::fileso ) \
\
		FA_TAG( folder, fa::folder ) \
		FA_TAG( foldero, fa::foldero ) \
		FA_TAG( folderopen, fa::folderopen ) \
		FA_TAG( folderopeno, fa::folderopeno ) \
\
		FA_TAG( square, fa::square ) \
		FA_TAG( squareo, fa::squareo ) \
		FA_TAG( hsquare, fa::hsquare ) \
		FA_TAG( foursquare, fa::foursquare ) \
		FA_TAG( checkcircle, fa::checkcircle ) \
		FA_TAG( checkcircleo, fa::checkcircleo ) \
		FA_TAG( checksquare, fa::checksquare ) \
		FA_TAG( checksquareo, fa::checksquareo ) \
\
		FA_TAG( toggledown, fa::toggledown ) \
		FA_TAG( toggleleft, fa::toggleleft ) \
		FA_TAG( toggleoff, fa::toggleoff ) \
		FA_TAG( toggleon, fa::toggleon ) \
		FA_TAG( toggleright, fa::toggleright ) \
		FA_TAG( toggleup, fa::toggleup ) \
\
		FA_TAG( hddo, fa::hddo ) \
		FA_TAG( list, fa::list ) \
		FA_TAG( listalt, fa::listalt ) \
		FA_TAG( listol, fa::listol ) \
		FA_TAG( listul, fa::listul ) \
		FA_TAG( paperclip, fa::paperclip ) \
		FA_TAG( stickynote, fa::stickynote ) \
\
		FA_TAG( history, fa::history )\
		FA_TAG( home, fa::home )\
		FA_TAG( download, fa::download ) \
		FA_TAG( music, fa::music ) \
		FA_TAG( videocamera, fa::videocamera ) \
		FA_TAG( trash, fa::trash ) \
		FA_TAG( trasho, fa::trasho ) \
		FA_TAG( refresh, fa::refresh )\
		FA_TAG( repeat, fa::repeat )\
		FA_TAG( random, fa::random )\
\
		FA_TAG( windowmaximize, fa::windowmaximize ) \
		FA_TAG( windowminimize, fa::windowminimize ) \
		FA_TAG( windowclose, fa::windowclose ) \
		FA_TAG( windowcloseo, fa::windowcloseo )\
		FA_TAG( close, fa::close ) \
\
		FA_TAG( plus, fa::plus ) \
		FA_TAG( minus, fa::minus ) \
		FA_TAG( check, fa::check ) \
		FA_TAG( edit, fa::edit ) \
		FA_TAG( stickynoteo, fa::stickynoteo ) \
		FA_TAG( paintbrush, fa::paintbrush ) \
\
		FA_TAG( building, fa::building )\
		FA_TAG( buildingo, fa::buildingo )\
		FA_TAG( wrench,fa::wrench) \
\
		FA_TAG( search, fa::search )\
		FA_TAG( searchminus, fa::searchminus )\
		FA_TAG( searchplus, fa::searchplus )\
\
		FA_TAG( registered, fa::registered )\
		FA_TAG( archive, fa::archive )\
		FA_TAG( tasks, fa::tasks ) \
		FA_TAG( gamepad, fa::gamepad ) \
		FA_TAG( producthunt, fa::producthunt ) \
		FA_TAG( windows, fa::windows ) \
		FA_TAG( wpexplorer, fa::wpexplorer ) \
		FA_TAG( wpforms, fa::wpforms ) \
		FA_TAG( terminal, fa::terminal ) \
\
		FA_TAG( question, fa::question ) \
		FA_TAG( questioncircle, fa::questioncircle ) \
		FA_TAG( questioncircleo, fa::questioncircleo ) \
\
		FA_TAG( info, fa::info ) \
		FA_TAG( infocircle, fa::infocircle )

		namespace FA {
		FAA_LIST
	}
		extern QtAwesome* awesome;
}


