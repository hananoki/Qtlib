#pragma once

#include <QDialog>
#include <memory>

class DarkWidgetPrivate;

//class DarkWindow : public QMainWindow {
//	Q_OBJECT
//public:
//	DarkWindow( QWidget* parent = nullptr );
//	virtual ~DarkWindow();
//
//	void addCaptionWidget( QWidget* widget );
//
//private:
//	std::unique_ptr<DarkWidgetPrivate> impl;
//
//
//#ifdef Q_OS_WIN
//	bool nativeEvent( const QByteArray& eventType, void* message, long* result ) override;
//#endif
//};


class DarkDialog : public QDialog {
	Q_OBJECT
public:
	DarkDialog( QWidget* parent = nullptr );
	virtual ~DarkDialog();

	void addCaptionWidget( QWidget* widget );
	QList< QWidget*>& captionWidget();

private:
	std::unique_ptr<DarkWidgetPrivate> impl;
#ifdef Q_OS_WIN
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	bool nativeEvent( const QByteArray& eventType, void* message, long* result ) override;
#else
	virtual bool nativeEvent( const QByteArray& eventType, void* message, qintptr* result ) override;
#endif
#endif
};

