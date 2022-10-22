#pragma once

#include <QFrame>
#include <memory>

class UIStatusBar : public QFrame {
	Q_OBJECT

public:
	explicit UIStatusBar( QWidget* parent = nullptr );
	~UIStatusBar();

	static void info( QString message, int msec = 5000 );
	static void warning( const QString& message, int msec = 10000 );
	static void error( const QString& message, int msec = 10000 );

	static void progressStart( const QString& message );
	static void progressStop();

private:
	class Impl;
	std::unique_ptr<Impl> impl;


};


