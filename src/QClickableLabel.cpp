#include "QClickableLabel.h"

QClickableLabel::QClickableLabel( QWidget* parent, const QString& text )
	: QLabel( text, parent ) {
}

void QClickableLabel::mousePressEvent( QMouseEvent*  ) {
	emit clicked();
}

QClickableLabel::~QClickableLabel() {
}
