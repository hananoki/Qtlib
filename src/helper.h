#pragma once

//#include <QWidget>
#include <QStyle>
#include <QRegularExpression>
#include <QDateTime>
#include <QFileInfo>
#include <QString>
#include <QStringList>

//class QString;
//class QStringList;
class QTreeWidgetItem;
//class QRegularExpressionMatch;


#define $$(x) QString(x)
#define $F(fmt, ...) QString::asprintf(fmt, __VA_ARGS__)

class HFileInfo : public QFileInfo {
public:
	HFileInfo( const QString& _fullPath );
	bool isLink();
	QString linkTarget();
	QString fullpath;
};


namespace $ {
	//public:
	void naturalSort( QStringList& files );

	inline int toInt( const QString& s );
	inline bool toBool( const QString& s );

	QString toString( int i );
	QString toString( bool b );
	QString toString( const QDateTime& dt, bool sec = false );

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

	QString toStringFileSize( qint64 fsize );

	/// @brief  日付チェック
	/// @param  inFile
	/// @param  outFile
	/// @return outFileよりinFileが新しい時はtrue
	bool isLastModified( const QString& inFile, const QString& outFile );

	QString makeUniqueDirectoryPath( QString fpath );
	QString makeUniqueFilePath( QString fpath );

#ifdef Q_OS_WIN
	bool isDrakMode();
#endif

#ifdef ENABLE_SOUND
	void playSound( const QString& filepath );
#endif

	template<class T>
	void showDialog( QWidget* parent ) {
		T dialog( parent );
		dialog.exec();
	}

	template<class T>
	void showDialog( QWidget* parent, std::function<void( T& )> accept ) {
		T dialog( parent );
		int result = dialog.exec();

		if( result != QDialog::Accepted )return;

		accept( dialog );
	}
	template<class T, class U>
	void showDialog( QWidget* parent, U arg, std::function<void( T& )> accept ) {
		T dialog( parent, arg );
		int result = dialog.exec();

		if( result != QDialog::Accepted )return;

		accept( dialog );
	}

	void showInExplorer( const QString& path );

	void showProperty( const QString& path );

	QString fileKind( const QString& path );

	QString junctionTarget( const QString& path );

	void getVolumeInformation( const QString& tdrive );

	int shellExecute( const QString& _filePath, const QString& _parameters );

	std::tuple<quint64, quint64, quint64> getDiskFreeSpace( QChar driveLetter );

	inline int toInt( const QString& s ) {
		return  s.toInt();
	}
	inline bool toBool( const QString& s ) {
		return  QVariant( s ).toBool();
	}

	inline QString toString( int i ) {
		return  QString::number( i );
	}
	inline QString toString( qint64 i ) {
		return  QString::number( i );
	}
	inline QString toStringHex( int i ) {
		return  $$( "%1" ).arg( i, 8, 16, QChar( '0' ) );
	}
	inline QString toString( quint32 i ) {
		return  QString::number( i );
	}
	inline QString toString( float v, char f = 'g', int prec = 6 ) {
		return  QString::number( v, f, prec );
		//QString::number( 0.12345, 'f', 5 )
	}
	inline QString toString( double v, char f = 'g', int prec = 6 ) {
		return  QString::number( v, f, prec );
	}

	inline QString toString( bool b ) {
		return b ? "True" : "False";
	}
	inline QString toString( const QDateTime& dt, bool sec /*= false*/ ) {
		return dt.toString( sec ? "yyyy/MM/dd hh:mm:ss" : "yyyy/MM/dd hh:mm" );
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


#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))

class $enums {
public:
	template<class T>
	static QStringList names() {
		using namespace cpplinq;
		constexpr auto color_names = magic_enum::enum_names<T>();
		return from( color_names )
			>> select( []( const auto& x ) { return QString( x.data() ); } )
			>> to_qlist();
	}

	template<class T>
	static T value( const QString& s ) {
		return magic_enum::enum_cast<EBuildAction>( s.toStdString() ).value();
	}
};

#endif




