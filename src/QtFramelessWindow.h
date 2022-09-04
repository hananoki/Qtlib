#pragma once

#include <QMainWindow>
#include <memory>

class QtFramelessWindowPrivate;

class QtFramelessWindow : public QMainWindow {
	Q_OBJECT
public:
	QtFramelessWindow( QWidget* parent = nullptr );
	virtual ~QtFramelessWindow();

	void addCaptionWidget( QWidget* widget );

private:
	std::unique_ptr<QtFramelessWindowPrivate> impl;


#ifdef Q_OS_WIN
	bool nativeEvent( const QByteArray& eventType, void* message, long* result ) override;
#endif
};
