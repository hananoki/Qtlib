#pragma once

#include <QWidget>

class UIFolderPathBox : public QWidget {
	Q_OBJECT

public:
	explicit UIFolderPathBox( QWidget* parent = nullptr );
	~UIFolderPathBox();

	void setText( const QString& text );

	void bind( QString* t );

signals:
	void textChanged( const QString& text, bool exist );

private:
	class Impl;
	std::unique_ptr<Impl> impl;

	bool eventFilter( QObject* obj, QEvent* event );
};

namespace $UIFolderPathBox {
	void textChanged( UIFolderPathBox* w, std::function<void( const QString& text, bool exist )> func );
}
