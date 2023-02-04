#pragma once

#include <QMainWindow>
#include <memory>

class HFramelessWindowPrivate;

class HFramelessWindow : public QMainWindow {
	Q_OBJECT
public:
	HFramelessWindow( QWidget* parent = nullptr );
	virtual ~HFramelessWindow();

	void addCaptionWidget( QWidget* widget );

private:
	std::unique_ptr<HFramelessWindowPrivate> impl;


#ifdef Q_OS_WIN
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	bool nativeEvent( const QByteArray& eventType, void* message, long* result ) override;
#else
	virtual bool nativeEvent( const QByteArray& eventType, void* message, qintptr* result ) override;
#endif
#endif
};
