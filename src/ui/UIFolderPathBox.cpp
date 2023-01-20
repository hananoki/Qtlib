#include "UIFolderPathBox.h"
#include "ui_UIFolderPathBox.h"

#include "icon.h"
#include "widgets.h"
#include "fs.h"
#include "path.h"

#include <QFileDialog>
#include <QDropEvent>
#include <QMimeData>

//////////////////////////////////////////////////////////////////////////////////
class UIFolderPathBox::Impl : public Ui_UIFolderPathBox {
public:
	UIFolderPathBox* self;

	QString folderPath;
	QString* bindText = nullptr;

	/////////////////////////////////////////
	Impl( UIFolderPathBox* _self ) :
		self( _self ) {

		setupUi( self );

		QAction* myAction = lineEdit->addAction( icon::SP_DirOpenIcon(), QLineEdit::TrailingPosition );

		$Action::triggered( myAction, [&]() {
			QFileDialog::Options options =
				QFileDialog::ShowDirsOnly | QFileDialog::HideNameFilterDetails |
				QFileDialog::DontUseCustomDirectoryIcons;

			QString s = QFileDialog::getExistingDirectory(
				self,
				tr( u8"フォルダーの選択" ),
				folderPath,
				options
			);
			if( s.isEmpty() ) {
				return;
			}
			folderPath = s;
			lineEdit->setText( folderPath );
		} );

		$LineEdit::textChanged( lineEdit, [&]( const QString& text ) {
			bool exist = false;

			if( text.isEmpty() || fs::isExistDirectory( text ) ) {
				lineEdit->setStyleSheet( "" );
				exist = true;
			}
			else {
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
	void bind( QString* t ) {
		lineEdit->setText( *t );
		bindText = t;
	}
};


//////////////////////////////////////////////////////////////////////////////////
UIFolderPathBox::UIFolderPathBox( QWidget* parent ) :
	QWidget( parent ),
	impl( new Impl( this ) ) {
}

/////////////////////////////////////////
UIFolderPathBox::~UIFolderPathBox() {
}

/////////////////////////////////////////
void UIFolderPathBox::setText( const QString& text ) {
	impl->lineEdit->setText( text );
}

/////////////////////////////////////////
bool UIFolderPathBox::eventFilter( QObject* obj, QEvent* event ) {
	if( obj != impl->lineEdit ) return false;

	if( event->type() == QEvent::Drop ) {
		QDropEvent* ee = (QDropEvent*) event;
		if( !ee->mimeData()->hasUrls() ) return false;

		auto lst = ee->mimeData()->urls();

		auto path = QUrl( lst[ 0 ] ).toLocalFile();

		if( fs::isExistFile( path ) ) {
			path = path::getDirectoryName( path );
		}

		setText( path );

		return true;
	}
	if( event->type() == QEvent::DragEnter ) {
		QDragEnterEvent* ee = (QDragEnterEvent*) event;
		ee->acceptProposedAction();
		return true;
	}
	if( event->type() == QEvent::DragMove ) {
		QDragMoveEvent* ee = (QDragMoveEvent*) event;
		ee->acceptProposedAction();
		return true;
	}
	return false;
}

void UIFolderPathBox::bind( QString* t ) {
	impl->bind( t );
}

namespace $UIFolderPathBox {
	void textChanged( UIFolderPathBox* w, std::function<void( const QString& text, bool exist )> func ) {
		QObject::connect( w, &UIFolderPathBox::textChanged, func );
	}
}
