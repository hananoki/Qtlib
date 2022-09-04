#pragma once

#include <QLabel>

class QtClickableLabel : public QLabel {
	Q_OBJECT
public:
	explicit QtClickableLabel( QWidget* parent = 0, const QString& text = "" );
	virtual ~QtClickableLabel();

signals:
	void clicked();

protected:
	void mousePressEvent( QMouseEvent* event );
};

