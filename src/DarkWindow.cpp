#include "DarkWindow.h"

#include <QApplication>
#include <QCloseEvent>

#ifdef Q_OS_WIN
#include <QtWin>
#include <dwmapi.h>
#pragma comment (lib,"Dwmapi.lib")
#pragma comment (lib,"user32.lib")

#endif

class DarkWidgetPrivate {
public:
	QList< QWidget*> hitTitleWidget;
	//QEventLoop* eventLoop;
	//int result;
	//void finalize( int resultCode, int dialogCode ) {
	//	//Q_Q( QDialog );

	//	if( dialogCode == QDialog::Accepted )
	//		emit q->accepted();
	//	else if( dialogCode == QDialog::Rejected )
	//		emit q->rejected();

	//	emit q->finished( resultCode );
	//}
};


/////////////////////////////////////////
//DarkWindow::DarkWindow( QWidget* parent )
//	: QMainWindow( parent )
//	, impl( new DarkWidgetPrivate() ) {
//
//#ifdef Q_OS_WIN
//	//static bool once = false;
//	//if( once )return;
//	const MARGINS shadow = { 1, 1, 1, 1 };
//	DwmExtendFrameIntoClientArea( HWND( winId() ), &shadow );
//	//once = true;
//#endif
//	//connect( this, &QMainWindow::close, [&]() {
//	//	
//	//} );
//}

//
///////////////////////////////////////////
//DarkWindow::~DarkWindow() {}
//
//
///////////////////////////////////////////
//void DarkWindow::addCaptionWidget( QWidget* widget ) {
//	impl->hitTitleWidget << widget;
//}
//
//
//
//#ifdef Q_OS_WIN
///////////////////////////////////////////
//bool DarkWindow::nativeEvent( const QByteArray& eventType, void* message, long* result ) {
//	MSG* msg = static_cast<MSG*>( message );
//
//	////マウスポインタがクライアント領域内にあるか
//	//if( ( msg->message == WM_NCHITTEST ) &&
//	//	( *result == HTCLIENT ) ) {
//	//	//マウスがタイトルバーにあるふりをする
//	//	*result =  HTCAPTION;
//	//}
//	if( msg->message == WM_NCCALCSIZE ) {
//		NCCALCSIZE_PARAMS& params = *reinterpret_cast<NCCALCSIZE_PARAMS*>( msg->lParam );
//		if( params.rgrc[ 0 ].top != 0 )
//			params.rgrc[ 0 ].top -= 1;
//
//		//this kills the window frame and title bar we added with WS_THICKFRAME and WS_CAPTION
//		*result = WVR_REDRAW;
//		return true;
//	}
//
//	if( msg->message == WM_NCHITTEST ) {
//		if( isMaximized() ) {
//			return false;
//		}
//
//		*result = 0;
//		const LONG borderWidth = 4;
//		RECT winrect;
//		GetWindowRect( reinterpret_cast<HWND>( winId() ), &winrect );
//
//		// must be short to correctly work with multiple monitors (negative coordinates)
//		short x = msg->lParam & 0x0000FFFF;
//		short y = ( msg->lParam & 0xFFFF0000 ) >> 16;
//
//		bool resizeWidth = minimumWidth() != maximumWidth();
//		bool resizeHeight = minimumHeight() != maximumHeight();
//		if( resizeWidth ) {
//			//left border
//			if( x >= winrect.left && x < winrect.left + borderWidth ) {
//				*result = HTLEFT;
//			}
//			//right border
//			if( x < winrect.right && x >= winrect.right - borderWidth ) {
//				*result = HTRIGHT;
//			}
//		}
//		if( resizeHeight ) {
//			//bottom border
//			if( y < winrect.bottom && y >= winrect.bottom - borderWidth ) {
//				*result = HTBOTTOM;
//			}
//			//top border
//			if( y >= winrect.top && y < winrect.top + borderWidth ) {
//				*result = HTTOP;
//			}
//		}
//		if( resizeWidth && resizeHeight ) {
//			//bottom left corner
//			if( x >= winrect.left && x < winrect.left + borderWidth &&
//				y < winrect.bottom && y >= winrect.bottom - borderWidth ) {
//				*result = HTBOTTOMLEFT;
//			}
//			//bottom right corner
//			if( x < winrect.right && x >= winrect.right - borderWidth &&
//				y < winrect.bottom && y >= winrect.bottom - borderWidth ) {
//				*result = HTBOTTOMRIGHT;
//			}
//			//top left corner
//			if( x >= winrect.left && x < winrect.left + borderWidth &&
//				y >= winrect.top && y < winrect.top + borderWidth ) {
//				*result = HTTOPLEFT;
//			}
//			//top right corner
//			if( x < winrect.right && x >= winrect.right - borderWidth &&
//				y >= winrect.top && y < winrect.top + borderWidth ) {
//				*result = HTTOPRIGHT;
//			}
//		}
//
//		if( *result != 0 )
//			return true;
//
//		QWidget* action = QApplication::widgetAt( QCursor::pos() );
//		if( 0 <= impl->hitTitleWidget.indexOf( action ) ) {
//			*result = HTCAPTION;
//			return true;
//		}
//		if( action == this ) {
//			*result = HTCAPTION;
//			return true;
//		}
//
//		return false;
//	}
//	return QMainWindow::nativeEvent( eventType, message, result );
//	//return false;
//}
//#endif


/////////////////////////////////////////
DarkDialog::DarkDialog( QWidget* parent )
	: QDialog( parent )
	, impl( new DarkWidgetPrivate() ) {
}
/////////////////////////////////////////
DarkDialog::~DarkDialog() {}
/////////////////////////////////////////
void DarkDialog::addCaptionWidget( QWidget* widget ) {
	impl->hitTitleWidget << widget;
}
QList< QWidget*>& DarkDialog::captionWidget() {
	return impl->hitTitleWidget;
}

#ifdef Q_OS_WIN
/////////////////////////////////////////
bool DarkDialog::nativeEvent( const QByteArray& eventType, void* message, long* result ) {
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
		if( 0 <= impl->hitTitleWidget.indexOf( action ) ) {
			*result = HTCAPTION;
			return true;
		}
		if( action == this ) {
			*result = HTCAPTION;
			return true;
		}

		return false;
	}
	return QDialog::nativeEvent( eventType, message, result );
	//return false;
}
#endif
