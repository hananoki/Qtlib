#pragma once

#include <QComboBox>

class HComboBox : public QComboBox {
	Q_OBJECT
public:
	explicit HComboBox( QWidget* parent = 0 ) : QComboBox( parent ) {}

	void bind( int* t, QObject* config = nullptr );
	virtual void bind( QString* t, QObject* config = nullptr );
signals:
	void currentTextChanged();

protected:
	//void mousePressEvent( QMouseEvent* event );
};

