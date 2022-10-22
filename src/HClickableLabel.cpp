#include "HClickableLabel.h"

HClickableLabel::HClickableLabel( QWidget* parent, const QString& text )
	: QLabel( text, parent ) {

	QFont f = font();
	f.setUnderline(true);
	setFont(f);

	setCursor( Qt::PointingHandCursor );
}

void HClickableLabel::mousePressEvent( QMouseEvent*  ) {
	emit clicked();
}

HClickableLabel::~HClickableLabel() {
}
