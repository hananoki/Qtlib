#include "QtFusionStyle.h"

#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include <QStyleFactory>

QtFusionStyle::QtFusionStyle() {
}


void QtFusionStyle::set(){
	qApp->setStyle( QStyleFactory::create( "Fusion" ) );
	QPalette darkPalette;

	QColor darkColor = "#222222";// QColor( 45, 45, 45 );
	QColor darkColor2 = "#666";// QColor( 45, 45, 45 );

	QColor disabledColor = QColor( 127, 127, 255 );
	darkPalette.setColor( QPalette::Window, darkColor );
	darkPalette.setColor( QPalette::WindowText, Qt::white );
	darkPalette.setColor( QPalette::Base, "#3E3E3E" /*QColor( 18, 18, 18 )*/ );
	darkPalette.setColor( QPalette::AlternateBase, darkColor );
	darkPalette.setColor( QPalette::ToolTipBase, Qt::white );
	darkPalette.setColor( QPalette::ToolTipText, Qt::white );
	darkPalette.setColor( QPalette::Text, Qt::white );
	darkPalette.setColor( QPalette::Disabled, QPalette::Text, disabledColor );

	darkPalette.setColor( QPalette::Button, darkColor2 );
	darkPalette.setColor( QPalette::ButtonText, Qt::white );
	darkPalette.setColor( QPalette::Disabled, QPalette::ButtonText, disabledColor );

	darkPalette.setColor( QPalette::BrightText, Qt::red );
	darkPalette.setColor( QPalette::Link, QColor( 42, 130, 218 ) );

	darkPalette.setColor( QPalette::Highlight, QColor( 42, 130, 218 ) );
	darkPalette.setColor( QPalette::HighlightedText, Qt::black );
	darkPalette.setColor( QPalette::Disabled, QPalette::HighlightedText, disabledColor );

	qApp->setPalette( darkPalette );

	//qApp->setStyleSheet( "QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }" );
}
