#pragma once

#include <QLabel>

class HClickableLabel : public QLabel {
	Q_OBJECT
public:
	explicit HClickableLabel( QWidget* parent = 0, const QString& text = "" );
	virtual ~HClickableLabel();

signals:
	void clicked();

protected:
	void mousePressEvent( QMouseEvent* event );
};

