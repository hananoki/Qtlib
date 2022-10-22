#include "HFramelessWindow.h"

#include <QApplication>
#include <QCloseEvent>

#ifdef Q_OS_WIN
#include <QtWin>
#include <dwmapi.h>
#pragma comment (lib,"Dwmapi.lib")
#pragma comment (lib,"user32.lib")

#endif


class HFramelessWindowPrivate {
public:
	QList< QWidget*> hitCaptionWidget;
};


/////////////////////////////////////////
HFramelessWindow::HFramelessWindow( QWidget* parent )
	: QMainWindow( parent )
	, impl( new HFramelessWindowPrivate() ) {

#ifdef Q_OS_WIN
	const MARGINS shadow = { 1, 1, 1, 1 };
	DwmExtendFrameIntoClientArea( HWND( winId() ), &shadow );
#endif
}


/////////////////////////////////////////
HFramelessWindow::~HFramelessWindow() {}


/////////////////////////////////////////
void HFramelessWindow::addCaptionWidget( QWidget* widget ) {
	impl->hitCaptionWidget << widget;
}



#ifdef Q_OS_WIN
/////////////////////////////////////////
bool HFramelessWindow::nativeEvent( const QByteArray& eventType, void* message, long* result ) {
	MSG* msg = static_cast<MSG*>( message );

	////マウスポインタがクライアント領域内にあるか
	//if( ( msg->message == WM_NCHITTEST ) &&
	//	( *result == HTCLIENT ) ) {
	//	//マウスがタイトルバーにあるふりをする
	//	*result =  HTCAPTION;
	//}
	if( msg->message == WM_NCCALCSIZE ) {
		NCCALCSIZE_PARAMS& params = *reinterpret_cast<NCCALCSIZE_PARAMS*>( msg->lParam );
		if( params.rgrc[ 0 ].top != 0 )
			params.rgrc[ 0 ].top -= 1;

		//this kills the window frame and title bar we added with WS_THICKFRAME and WS_CAPTION
		*result = WVR_REDRAW;
		return true;
	}

	if( msg->message == WM_NCHITTEST ) {
		if( isMaximized() ) {
			return false;
		}

		*result = 0;
		const LONG borderWidth = 4;
		RECT winrect;
		GetWindowRect( reinterpret_cast<HWND>( winId() ), &winrect );

		// must be short to correctly work with multiple monitors (negative coordinates)
		short x = msg->lParam & 0x0000FFFF;
		short y = ( msg->lParam & 0xFFFF0000 ) >> 16;

		bool resizeWidth = minimumWidth() != maximumWidth();
		bool resizeHeight = minimumHeight() != maximumHeight();
		if( resizeWidth ) {
			//left border
			if( x >= winrect.left && x < winrect.left + borderWidth ) {
				*result = HTLEFT;
			}
			//right border
			if( x < winrect.right && x >= winrect.right - borderWidth ) {
				*result = HTRIGHT;
			}
		}
		if( resizeHeight ) {
			//bottom border
			if( y < winrect.bottom && y >= winrect.bottom - borderWidth ) {
				*result = HTBOTTOM;
			}
			//top border
			if( y >= winrect.top && y < winrect.top + borderWidth ) {
				*result = HTTOP;
			}
		}
		if( resizeWidth && resizeHeight ) {
			//bottom left corner
			if( x >= winrect.left && x < winrect.left + borderWidth &&
				y < winrect.bottom && y >= winrect.bottom - borderWidth ) {
				*result = HTBOTTOMLEFT;
			}
			//bottom right corner
			if( x < winrect.right && x >= winrect.right - borderWidth &&
				y < winrect.bottom && y >= winrect.bottom - borderWidth ) {
				*result = HTBOTTOMRIGHT;
			}
			//top left corner
			if( x >= winrect.left && x < winrect.left + borderWidth &&
				y >= winrect.top && y < winrect.top + borderWidth ) {
				*result = HTTOPLEFT;
			}
			//top right corner
			if( x < winrect.right && x >= winrect.right - borderWidth &&
				y >= winrect.top && y < winrect.top + borderWidth ) {
				*result = HTTOPRIGHT;
			}
		}

		if( *result != 0 )
			return true;

		QWidget* action = QApplication::widgetAt( QCursor::pos() );
		if( 0 <= impl->hitCaptionWidget.indexOf( action ) ) {
			*result = HTCAPTION;
			return true;
		}
		if( action == this ) {
			*result = HTCAPTION;
			return true;
		}

		return false;
	}
	return QMainWindow::nativeEvent( eventType, message, result );
	//return false;
}
#endif
