#pragma once

#include <functional>

class QRadioButton;
class QGroupBox;
class QPushButton;

namespace groupBox {
	QRadioButton* findSelectedRadioButton( QGroupBox* group );
}

namespace pushbutton {
	void clicked( QPushButton* w, std::function<void( bool )> func );
	void pressed( QPushButton* w, std::function<void()> func );
}

