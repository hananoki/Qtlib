#pragma once

//#include <QWidget>
#include <QStyle>
#include <QRegularExpression>
#include <QDateTime>

class QString;
class QStringList;
class QTreeWidgetItem;
//class QRegularExpressionMatch;


#define $$(x) QString(x)
#define $F(fmt, ...) QString::asprintf(fmt, __VA_ARGS__)


namespace $ {
	//public:
	void naturalSort( QStringList& files );

	inline int toInt( const QString& s ) { return  s.toInt(); }
	inline bool toBool( const QString& s ) { return  QVariant( s ).toBool(); }
	inline QString toString( int i ) { return  QString::number( i ); }
	inline QString toString( const QDateTime& i ) { return   i.toString( "yyyy/MM/dd hh:mm" ); }

	const wchar_t* toWCharPtr( const QString& s );
	bool match( const QString& s1, const QString& s2, std::function<void( QRegularExpressionMatch& )> func = nullptr, QRegularExpression::MatchType matchType = QRegularExpression::NormalMatch );


	QString trimEnd( const QString& s, QString trim );

	template<typename T>
	void restoreState( T* widget, const QString& bintxt ) {
		widget->restoreState( QByteArray::fromHex( QByteArray().append( bintxt ) ) );
	}

	template<typename T>
	void saveState( QString& bintxt, T* widget ) {
		bintxt = QString( widget->saveState().toHex() );
	}

	template<class T>
	static QStringList toStringList( const QList<T>& lst, std::function<QString( const T& )> func ) {
		QStringList result;
		for( auto& s : lst ) {
			result << func( s );
		}
		return result;
	}
	//template<class T>

	bool has( int i, int chk );
	void enable( int& i, int chk );
	void disable( int& i, int chk );
	void toggle( int& i, int flag, bool b );

	void setBoldFont( QTreeWidgetItem& item );

	QPixmap getStdPixmap( QStyle::StandardPixmap id );

#ifdef Q_OS_WIN
	bool isDrakMode();
#endif

	void playSound( const QString& filepath );

	template<class T>
	void showDialog( QWidget* parent, std::function<void( T& )> accept ) {
		T dialog( parent );
		int result = dialog.exec();

		if( result != QDialog::Accepted )return;

		accept( dialog );
	}



	inline
		const wchar_t* toWCharPtr( const QString& s ) {
		return reinterpret_cast<const wchar_t*>( s.utf16() );
	}

	inline
		bool $::has( int i, int chk ) {
		return 0 != ( i & chk ) ? true : false;
	}

	inline
		void $::enable( int& i, int chk ) {
		i |= chk;
	}

	inline
		void $::disable( int& i, int chk ) {
		i &= ~chk;
	}

	inline
		void $::toggle( int& i, int flag, bool b ) {
		if( b ) i |= flag;
		else i &= ~flag;
	}

}







