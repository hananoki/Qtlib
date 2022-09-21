#pragma once

#include <QPushButton>

class QtFlatPushButton : public QPushButton {
	Q_OBJECT
public:
	QtFlatPushButton( QWidget* parent = nullptr );

	void hoverLeave();

protected:
	bool event( QEvent* event );
};

