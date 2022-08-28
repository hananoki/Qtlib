#pragma once

#include <QLabel>

class QClickableLabel : public QLabel {
	Q_OBJECT
public:
	explicit QClickableLabel( QWidget* parent = 0, const QString& text = "" );
	~QClickableLabel();

signals:
	void clicked();

protected:
	void mousePressEvent( QMouseEvent* event );
};

