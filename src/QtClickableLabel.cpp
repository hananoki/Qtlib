#include "QtClickableLabel.h"

QtClickableLabel::QtClickableLabel( QWidget* parent, const QString& text )
	: QLabel( text, parent ) {
}

void QtClickableLabel::mousePressEvent( QMouseEvent*  ) {
	emit clicked();
}

QtClickableLabel::~QtClickableLabel() {
}
