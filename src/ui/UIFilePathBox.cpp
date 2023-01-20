#include "UIFilePathBox.h"
#include "ui_UIFilePathBox.h"

#include "icon.h"
#include "widgets.h"
#include "fs.h"

#include <QFileDialog>
#include <QDropEvent>
#include <QMimeData>

//////////////////////////////////////////////////////////////////////////////////
class UIFilePathBox::Impl : public Ui_UIFilePathBox {
public:
	UIFilePathBox* self;

	QString folderPath;
	QString* bindText = nullptr;

	QString fileter;

	/////////////////////////////////////////
	Impl( UIFilePathBox* _self ) :
		self( _self ) {

		setupUi( self );

		QAction* myAction = lineEdit->addAction( icon::SP_FileIcon(), QLineEdit::TrailingPosition );

		$Action::triggered( myAction, [&]() {
			QString s = QFileDialog::getOpenFileName(
				self,
				tr( u8"ファイルを選択" ),
				folderPath,
				fileter
			);
			if( s.isEmpty() ) {
				return;
			}
			folderPath = s;
			lineEdit->setText( folderPath );
		} );

		$LineEdit::textChanged( lineEdit, [&]( const QString& text ) {
			bool exist = false;

			if( text.isEmpty() || fs::isExistFile( text ) ) {
				lineEdit->setStyleSheet( "" );
				exist = true;
			}
			else {
				//lineEdit->setStyleSheet( "background: #844" );
				lineEdit->setStyleSheet( "background: #FBB" );
			}
			if( bindText ) {
				*bindText = text;
			}
			emit self->textChanged( text, exist );
		} );

		lineEdit->installEventFilter( self );
	}


	/////////////////////////////////////////
	void bind( QString* t, const QStringList& _fileter ) {
		lineEdit->setText( *t );
		bindText = t;

		QStringList lst = _fileter;
		lst.insert( 0, tr( u8"すべてのファイル (*.*)" ) );

		fileter = lst.join( ";;" );
	}
};


//////////////////////////////////////////////////////////////////////////////////
UIFilePathBox::UIFilePathBox( QWidget* parent ) :
	QWidget( parent ),
	impl( new Impl( this ) ) {
}

/////////////////////////////////////////
UIFilePathBox::~UIFilePathBox() {
}

/////////////////////////////////////////
void UIFilePathBox::setText( const QString& text ) {
	impl->lineEdit->setText( text );
}


/////////////////////////////////////////
QString UIFilePathBox::text() {
	return impl->lineEdit->text();
}


/////////////////////////////////////////
bool UIFilePathBox::eventFilter( QObject* obj, QEvent* event ) {
	if( obj != impl->lineEdit ) return false;

	if( event->type() == QEvent::Drop ) {
		QDropEvent* ee = (QDropEvent*) event;
		if( !ee->mimeData()->hasUrls() ) return false;

		auto lst = ee->mimeData()->urls();

		auto path = QUrl( lst[ 0 ] ).toLocalFile();

		if( !fs::isExistFile( path ) ) {
			return false;
		}

		setText( path );

		return true;
	}
	if( event->type() == QEvent::DragEnter ) {
		QDragEnterEvent* ee = (QDragEnterEvent*) event;

		if( !ee->mimeData()->hasUrls() ) return false;

		auto lst = ee->mimeData()->urls();

		auto path = QUrl( lst[ 0 ] ).toLocalFile();

		if( !fs::isExistFile( path ) ) {
			return false;
		}

		ee->acceptProposedAction();
		return true;
	}
	//if( event->type() == QEvent::DragMove ) {
	//	QDragMoveEvent* ee = (QDragMoveEvent*) event;
	//	if( !ee->mimeData()->hasUrls() ) return false;

	//	auto lst = ee->mimeData()->urls();

	//	auto path = QUrl( lst[ 0 ] ).toLocalFile();

	//	if( !fs::isExistFile( path ) ) {
	//		return false;
	//	}

	//	ee->acceptProposedAction();
	//	return true;
	//}
	return false;
}

void UIFilePathBox::bind( QString* t, const QStringList& fileter ) {
	impl->bind( t, fileter );
}

namespace $UIFilePathBox {
	void textChanged( UIFilePathBox* w, std::function<void( const QString& text, bool exist )> func ) {
		QObject::connect( w, &UIFilePathBox::textChanged, func );
	}
}
