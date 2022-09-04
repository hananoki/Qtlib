#pragma once

#include <functional>

class QRadioButton;
class QGroupBox;
class QPushButton;
class QLineEdit;
class QString;
class QTreeWidget;
class QTreeWidgetItem;

namespace groupBox {
	QRadioButton* findSelectedRadioButton( QGroupBox* group );
}

namespace $PushButton {
	void clicked( QPushButton* w, std::function<void( bool )> func );
	void pressed( QPushButton* w, std::function<void()> func );
}


namespace lineedit {
	void textEdited( QLineEdit* w, std::function<void( const QString& )> func );
	void textChanged( QLineEdit* w, std::function<void( const QString& )> func );
}

namespace $TreeWidget {
	void itemClicked( QTreeWidget* w, std::function<void( QTreeWidgetItem*, int )> func );
}
