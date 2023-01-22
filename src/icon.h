#pragma once

#include <QStyle>

class QIcon;
class QString;
class QtAwesome;

namespace icon {
	QIcon get( const QString& filePath );
	QIcon get( QStyle::StandardPixmap id );

	//void initQtAwesome( float scaleFactor = 1.0f, QColor color = "#FFF" );


#define QT_ICON(xxx,yyy) inline QIcon xxx (){ return  icon::get( yyy ); }
#define QT_ICON_LIST \
		QT_ICON( SP_TitleBarMenuButton, QStyle::SP_TitleBarMenuButton) \
		QT_ICON( SP_TitleBarMinButton, QStyle::SP_TitleBarMinButton) \
		QT_ICON( SP_TitleBarMaxButton, QStyle::SP_TitleBarMaxButton) \
		QT_ICON( SP_TitleBarCloseButton, QStyle::SP_TitleBarCloseButton) \
\
		QT_ICON( SP_TitleBarNormalButton, QStyle::SP_TitleBarNormalButton ) \
		QT_ICON( SP_TitleBarShadeButton, QStyle::SP_TitleBarShadeButton ) \
		QT_ICON( SP_TitleBarUnshadeButton, QStyle::SP_TitleBarUnshadeButton ) \
		QT_ICON( SP_TitleBarContextHelpButton, QStyle::SP_TitleBarContextHelpButton ) \
\
		QT_ICON( SP_DockWidgetCloseButton, QStyle::SP_DockWidgetCloseButton ) \
		QT_ICON( SP_MessageBoxInformation, QStyle::SP_MessageBoxInformation ) \
		QT_ICON( SP_MessageBoxWarning, QStyle::SP_MessageBoxWarning ) \
		QT_ICON( SP_MessageBoxCritical, QStyle::SP_MessageBoxCritical ) \
\
		QT_ICON( SP_MessageBoxQuestion, QStyle::SP_MessageBoxQuestion ) \
		QT_ICON( SP_DesktopIcon, QStyle::SP_DesktopIcon ) \
		QT_ICON( SP_TrashIcon, QStyle::SP_TrashIcon ) \
		QT_ICON( SP_ComputerIcon, QStyle::SP_ComputerIcon ) \
\
		QT_ICON( SP_DriveFDIcon, QStyle::SP_DriveFDIcon) \
		QT_ICON( SP_DriveHDIcon, QStyle::SP_DriveHDIcon) \
		QT_ICON( SP_DriveCDIcon, QStyle::SP_DriveCDIcon) \
		QT_ICON( SP_DriveDVDIcon, QStyle::SP_DriveDVDIcon) \
\
		QT_ICON( SP_DriveNetIcon, QStyle::SP_DriveNetIcon) \
		QT_ICON( SP_DirOpenIcon, QStyle::SP_DirOpenIcon) \
		QT_ICON( SP_DirClosedIcon, QStyle::SP_DirClosedIcon) \
		QT_ICON( SP_DirLinkIcon, QStyle::SP_DirLinkIcon) \
\
		QT_ICON( SP_DirLinkOpenIcon, QStyle::SP_DirLinkOpenIcon) \
		QT_ICON( SP_FileIcon, QStyle::SP_FileIcon) \
		QT_ICON( SP_FileLinkIcon, QStyle::SP_FileLinkIcon) \
		QT_ICON( SP_ToolBarHorizontalExtensionButton, QStyle::SP_ToolBarHorizontalExtensionButton) \
\
		QT_ICON( SP_ToolBarVerticalExtensionButton, QStyle::SP_ToolBarVerticalExtensionButton) \
		QT_ICON( SP_FileDialogStart, QStyle::SP_FileDialogStart) \
		QT_ICON( SP_FileDialogEnd, QStyle::SP_FileDialogEnd) \
		QT_ICON( SP_FileDialogToParent, QStyle::SP_FileDialogToParent) \
\
		QT_ICON( SP_FileDialogNewFolder, QStyle::SP_FileDialogNewFolder) \
		QT_ICON( SP_FileDialogDetailedView, QStyle::SP_FileDialogDetailedView) \
		QT_ICON( SP_FileDialogInfoView, QStyle::SP_FileDialogInfoView) \
		QT_ICON( SP_FileDialogContentsView, QStyle::SP_FileDialogContentsView) \
\
		QT_ICON( SP_FileDialogListView, QStyle::SP_FileDialogListView) \
		QT_ICON( SP_FileDialogBack, QStyle::SP_FileDialogBack) \
		QT_ICON( SP_DirIcon, QStyle::SP_DirIcon) \
		QT_ICON( SP_DialogOkButton, QStyle::SP_DialogOkButton) \
\
		QT_ICON( SP_DialogCancelButton, QStyle::SP_DialogCancelButton) \
		QT_ICON( SP_DialogHelpButton, QStyle::SP_DialogHelpButton) \
		QT_ICON( SP_DialogOpenButton, QStyle::SP_DialogOpenButton) \
		QT_ICON( SP_DialogSaveButton, QStyle::SP_DialogSaveButton) \
\
		QT_ICON( SP_DialogCloseButton, QStyle::SP_DialogCloseButton) \
		QT_ICON( SP_DialogApplyButton, QStyle::SP_DialogApplyButton) \
		QT_ICON( SP_DialogResetButton, QStyle::SP_DialogResetButton) \
		QT_ICON( SP_DialogDiscardButton, QStyle::SP_DialogDiscardButton) \
\
		QT_ICON( SP_DialogYesButton, QStyle::SP_DialogYesButton) \
		QT_ICON( SP_DialogNoButton, QStyle::SP_DialogNoButton) \
		QT_ICON( SP_ArrowUp, QStyle::SP_ArrowUp) \
		QT_ICON( SP_ArrowDown, QStyle::SP_ArrowDown) \
\
		QT_ICON( SP_ArrowLeft, QStyle::SP_ArrowLeft) \
		QT_ICON( SP_ArrowRight, QStyle::SP_ArrowRight) \
		QT_ICON( SP_ArrowBack, QStyle::SP_ArrowBack) \
		QT_ICON( SP_ArrowForward, QStyle::SP_ArrowForward) \
\
		QT_ICON( SP_DirHomeIcon, QStyle::SP_DirHomeIcon) \
		QT_ICON( SP_CommandLink, QStyle::SP_CommandLink) \
		QT_ICON( SP_VistaShield, QStyle::SP_VistaShield) \
		QT_ICON( SP_BrowserReload, QStyle::SP_BrowserReload) \
\
		QT_ICON( SP_BrowserStop, QStyle::SP_BrowserStop) \
		QT_ICON( SP_MediaPlay, QStyle::SP_MediaPlay) \
		QT_ICON( SP_MediaStop, QStyle::SP_MediaStop) \
		QT_ICON( SP_MediaPause, QStyle::SP_MediaPause) \
\
		QT_ICON( SP_MediaSkipForward, QStyle::SP_MediaSkipForward) \
		QT_ICON( SP_MediaSkipBackward, QStyle::SP_MediaSkipBackward) \
		QT_ICON( SP_MediaSeekForward, QStyle::SP_MediaSeekForward) \
		QT_ICON( SP_MediaSeekBackward, QStyle::SP_MediaSeekBackward) \
\
		QT_ICON( SP_MediaVolume, QStyle::SP_MediaVolume) \
		QT_ICON( SP_MediaVolumeMuted, QStyle::SP_MediaVolumeMuted) \
		QT_ICON( SP_LineEditClearButton, QStyle::SP_LineEditClearButton) \
		QT_ICON( SP_DialogYesToAllButton, QStyle::SP_DialogYesToAllButton) \
\
		QT_ICON( SP_DialogNoToAllButton, QStyle::SP_DialogNoToAllButton) \
		QT_ICON( SP_DialogSaveAllButton, QStyle::SP_DialogSaveAllButton) \
		QT_ICON( SP_DialogAbortButton, QStyle::SP_DialogAbortButton) \
		QT_ICON( SP_DialogRetryButton, QStyle::SP_DialogRetryButton) \
\
		QT_ICON( SP_DialogIgnoreButton, QStyle::SP_DialogIgnoreButton) \
		QT_ICON( SP_RestoreDefaultsButton, QStyle::SP_RestoreDefaultsButton)

	QT_ICON_LIST

#undef QT_ICON
#undef QT_ICON_LIST

}


