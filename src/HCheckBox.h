#pragma once

#include <QCheckBox>

class HCheckBox : public QCheckBox {
	Q_OBJECT
public:
	explicit HCheckBox( QWidget* parent = 0 ) :QCheckBox( parent ) {}

	void bind( bool* t, QObject* config = nullptr );
signals:
	void stateChanged(  );

protected:
	//void mousePressEvent( QMouseEvent* event );
};
