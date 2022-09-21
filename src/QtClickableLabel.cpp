#include "QtClickableLabel.h"

QtClickableLabel::QtClickableLabel( QWidget* parent, const QString& text )
	: QLabel( text, parent ) {

	QFont f = font();
	f.setUnderline(true);
	setFont(f);

	setCursor( Qt::PointingHandCursor );
}

void QtClickableLabel::mousePressEvent( QMouseEvent*  ) {
	emit clicked();
}

QtClickableLabel::~QtClickableLabel() {
}
