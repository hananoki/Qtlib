#pragma once

#include <QWidget>

class UIFilePathBox : public QWidget {
	Q_OBJECT

public:
	explicit UIFilePathBox( QWidget* parent = nullptr );
	~UIFilePathBox();

	void setText( const QString& text );

	QString text();

	void bind( QString* t, const QStringList& _fileter = {} );

signals:
	void textChanged( const QString& text, bool exist );

private:
	class Impl;
	std::unique_ptr<Impl> impl;

	bool eventFilter( QObject* obj, QEvent* event );
};

namespace $UIFilePathBox {
	void textChanged( UIFilePathBox* w, std::function<void( const QString& text, bool exist )> func );
}
