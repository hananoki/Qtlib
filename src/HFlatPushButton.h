#pragma once

#include <QPushButton>

class HFlatPushButton : public QPushButton {
	Q_OBJECT
public:
	HFlatPushButton( QWidget* parent = nullptr );

	void hoverLeave();

protected:
	bool event( QEvent* event );
};

