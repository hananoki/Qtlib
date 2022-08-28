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
		FA_TAG( FA_ARROWUP, fa::arrowup ) \
		FA_TAG( FA_BOOKMARK, fa::bookmark ) \
		FA_TAG( FA_BOOKMARKO, fa::bookmarko ) \
		FA_TAG( FA_BRIEFCASE, fa::briefcase ) \
		FA_TAG( FA_COG, fa::cog ) \
		FA_TAG( FA_CODEPEN, fa::codepen ) \
		FA_TAG( FA_CODE, fa::code ) \
		FA_TAG( FA_GROUP, fa::group ) \
\
		FA_TAG( FA_FILESO, fa::fileso ) \
		FA_TAG( FA_FOLDER, fa::folder ) \
		FA_TAG( FA_FOLDERO, fa::foldero ) \
		FA_TAG( FA_FOLDEROPEN, fa::folderopen ) \
		FA_TAG( FA_FOLDEROPENO, fa::folderopeno ) \
\
		FA_TAG( FA_HDDO, fa::hddo ) \
		FA_TAG( FA_LIST, fa::list ) \
		FA_TAG( FA_LISTALT, fa::listalt ) \
		FA_TAG( FA_LISTOL, fa::listol ) \
		FA_TAG( FA_LISTUL, fa::listul ) \
		FA_TAG( FA_PAPERCLIP, fa::paperclip ) \
		FA_TAG( FA_STICKYNOTE, fa::stickynote ) \
\
		FA_TAG( FA_HISTORY, fa::history )\
		FA_TAG( FA_HOME, fa::home )\
		FA_TAG( FA_DOWNLOAD, fa::download ) \
		FA_TAG( FA_MUSIC, fa::music ) \
		FA_TAG( FA_VIDEOCAMERA, fa::videocamera ) \
		FA_TAG( FA_TRASHO, fa::trasho ) \
		FA_TAG( FA_REFRESH, fa::refresh )\
		FA_TAG( FA_REPEAT, fa::repeat )\
		FA_TAG( FA_RANDOM, fa::random )\
\
		FA_TAG( FA_WINDOWMAXIMIZE, fa::windowmaximize ) \
		FA_TAG( FA_WINDOWMINIMIZE, fa::windowminimize ) \
		FA_TAG( FA_WINDOWCLOSE, fa::windowclose ) \
		FA_TAG( FA_WINDOWCLOSEO, fa::windowcloseo )\
		FA_TAG( FA_CLOSE, fa::close ) \
\
		FA_TAG( FA_PLUS, fa::plus ) \
		FA_TAG( FA_MINUS, fa::minus ) \
		FA_TAG( FA_CHECK, fa::check ) \
		FA_TAG( FA_EDIT, fa::edit ) \
		FA_TAG( FA_STICKYNOTEO, fa::stickynoteo ) \
		FA_TAG( FA_PAINTBRUSH, fa::paintbrush ) \
\
		FA_TAG( FA_SEARCH, fa::search )\
		FA_TAG( FA_SEARCHMINUS, fa::searchminus )\
		FA_TAG( FA_SEARCHPLUS, fa::searchplus )\
\
		FA_TAG( FA_REGISTERED, fa::registered )\
		FA_TAG( FA_ARCHIVE, fa::archive )\
		FA_TAG( FA_WRENCH,fa::wrench) \
		FA_TAG( FA_TASKS, fa::tasks ) \
		FA_TAG( FA_GAMEPAD, fa::gamepad ) \
		FA_TAG( FA_PRODUCTHUNT, fa::producthunt ) \
		FA_TAG( FA_WPEXPLORER, fa::wpexplorer ) \
		FA_TAG( FA_WPFORMS, fa::wpforms )

		FAA_LIST

		extern QtAwesome* awesome;
}


