#include "UIStatusBar.h"
#include "ui_UIStatusBar.h"
#include "helper.h"

#include <QStyle>
#include <QTimer>

#define PIXMAP_MSG_INFO $::getStdPixmap( QStyle::SP_MessageBoxInformation )
#define PIXMAP_MSG_WARNING $::getStdPixmap( QStyle::SP_MessageBoxWarning )
#define PIXMAP_MSG_ERROR $::getStdPixmap( QStyle::SP_MessageBoxCritical )


//////////////////////////////////////////////////////////////////////////////////
class UIStatusBar::Impl : public Ui_UIStatusBar {
public:
	static UIStatusBar* instance;
	UIStatusBar* self;

	QTimer* timer;

	int mode = 0;
	int step = 0;;
	QString commandMessage;

	/////////////////////////////////////////
	Impl( UIStatusBar* _self ) :
		self( _self ) {

		instance = self;
		setupUi( self );

		timer = new QTimer( self );
		timer->stop();

		label->hide();
		label_status->hide();

		connect( timer, &QTimer::timeout, [&]() {_timeout(); } );
	}


	/////////////////////////////////////////
	void _timeout() {
		QStringList a( { "|", "/" , "-", "\\" } );
		if( mode ) {
			label_status->setText( commandMessage + a[ step ] );
			step++;
			if( a.length() <= step ) step = 0;
		}
		else {
			timer->stop();
			label->hide();
			label_status->hide();
		}
	}


	/////////////////////////////////////////
	void show( const QString& message, int type, int msec ) {
		label->show();
		label_status->show();
		mode = 0;

		QPixmap px;
		switch( type ) {
			case 0:
				px = PIXMAP_MSG_INFO;
				break;
			case 1:
				px = PIXMAP_MSG_WARNING;
				break;
			case 2:
				px = PIXMAP_MSG_ERROR;
				break;
		}
		px = px.scaled( 16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation );

		label->setPixmap( px );

		label_status->setText( message );

		timer->setInterval( msec );

		timer->start();
	}


	/////////////////////////////////////////
	void progressStart( const QString& message ) {
		commandMessage = message;
		label_status->setText( message );
		label_status->show();
		timer->setInterval( 200 );
		mode = 1;
		step = 0;
		timer->start();
	}


	/////////////////////////////////////////
	void progressStop() {
		mode = 0;
	}

};

UIStatusBar* UIStatusBar::Impl::instance;


//////////////////////////////////////////////////////////////////////////////////
UIStatusBar::UIStatusBar( QWidget* parent ) :
	QFrame( parent ),
	impl( new Impl( this ) ) {

}


/////////////////////////////////////////
UIStatusBar::~UIStatusBar() {

}


/////////////////////////////////////////
void UIStatusBar::info( QString message, int msec ) {
	UIStatusBar::Impl::instance->impl->show( message, 0, msec );
}

/////////////////////////////////////////
void UIStatusBar::warning( const QString& message, int msec ) {
	UIStatusBar::Impl::instance->impl->show( message, 1, msec );
}

/////////////////////////////////////////
void UIStatusBar::error( const QString& message, int msec ) {
	UIStatusBar::Impl::instance->impl->show( message, 2, msec );
}

void UIStatusBar::progressStart( const QString& message ) {
	UIStatusBar::Impl::instance->impl->progressStart( message );
}

void UIStatusBar::progressStop() {
	UIStatusBar::Impl::instance->impl->progressStop();
}
