#ifndef __DATE_HPP__
#define __DATE_HPP__

#include<ctime>
#include<string>
#include "DateException.hpp"

class Date
{
public:
  /* Types */
enum GRANULARITY
  {
    SECOND = 0,
    MIN,
    DAY,
    WEEK,
    MONTH,
    YEAR
  };

public:
  /* Constructors / Destructor */
  Date();
  Date( int aDay, int aMonth, int aYear, int aSeconds = 0 );
  Date( const Date& aDate );
  Date( const struct tm& aDate );
  Date( const time_t& aDate);

  virtual ~Date() {}

  static int secondsToDays( double seconds );

  /* Accessors */
  time_t unixTmstmp() const throw( DateException );
  int    getSecond()  const throw();
  int    getDay()     const throw();
  int    getMonth()   const throw();
  int    getYear()    const throw();

  /* Modifiers */
  void setSeconds( int aSeconds ) throw( DateException );
  void setDay( int aDay )         throw( DateException );
  void setMonth( int aMonth )     throw( DateException );
  void setYear( int aYear )       throw( DateException );

  /* Methods */
  double diffDate( const Date& aDate )   const;
  bool   isLessThan( const Date& aDate ) const;
  bool   isEqualTo( const Date& aDate )  const;

  std::string toString( bool showTime = false ) const;
  void adjust( int aAmount, Date::GRANULARITY granularity ) throw( DateException );

  /* Operator Overloads */
  bool operator< ( const Date& other ) const;
  bool operator> ( const Date& other ) const;
  bool operator<=( const Date& other ) const;
  bool operator>=( const Date& other ) const;
  bool operator==( const Date& other ) const;
  bool operator!=( const Date& other ) const;

  Date& operator= ( const Date& rhs );
  double operator- ( const Date& rhs );

private:
  void settm( int aDay, int aMonth, int aYear, int aSecond = 0 ) throw( DateException );

  void adjustSeconds( int aAmount ) throw( DateException );
  void adjustMinutes( int aAmount ) throw( DateException );
  void adjustDay( int aAmount )     throw( DateException );
  void adjustMonth( int aAmount )   throw( DateException );
  void adjustYear( int aAmount )    throw( DateException );

  int getDaysInMonth( int aMonth, int aYear ) const throw( DateException );

  struct tm toTmStruct( time_t aTimeStamp ) throw();
  time_t toUnixTimeStamp( struct tm aTime ) const throw( DateException );

  struct tm Time;

};

#endif
