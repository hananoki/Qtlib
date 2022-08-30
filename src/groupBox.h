#pragma once

#include <functional>

class QRadioButton;
class QGroupBox;
class QPushButton;
class QLineEdit;
class QString;

namespace groupBox {
	QRadioButton* findSelectedRadioButton( QGroupBox* group );
}

namespace pushbutton {
	void clicked( QPushButton* w, std::function<void( bool )> func );
	void pressed( QPushButton* w, std::function<void()> func );
}


namespace lineedit {
	void textEdited( QLineEdit* w, std::function<void( const QString& )> func );
	void textChanged( QLineEdit* w, std::function<void( const QString& )> func );
}
