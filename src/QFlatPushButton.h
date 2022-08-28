#pragma once

#include <QPushButton>

class QFlatPushButton : public QPushButton {
	Q_OBJECT

public:
	QFlatPushButton( QWidget* parent = nullptr );

	void hoverLeave();

protected:
	bool event( QEvent* event );
};

