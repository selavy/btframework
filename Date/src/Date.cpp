#include "Date.hpp"
#include <ctime>

/* Constructors */

Date::Date()
{
  time_t rawtime;

  time( &rawtime );
  Time = *gmtime( &rawtime );

} /* end Date::Date() */

Date::Date(
	   int aDay,
	   int aMonth,
	   int aYear,
	   int aSeconds
	   )
{
  settm( aDay, aMonth, aYear, aSeconds );
} /* end Date::Date() */

Date::Date(
	   const Date& aDate
	   )
{
  settm( aDate.getDay(), aDate.getMonth(), aDate.getYear(), aDate.getSecond() );
} /* end Date::Date() */

Date::Date(
	   const struct tm& aDate
	   )
{
  Time = aDate;
} /* end Date::Date() */

Date::Date(
	   const time_t& aDate
	   )
{
  Time = toTmStruct( aDate );
} /* end Date::Date() */

/* Class method */
int Date::secondsToDays(
			double seconds
			)
{
  return static_cast<int>( seconds / 86400 );
}

/* Accessors */

time_t Date::unixTmstmp() const throw( DateException )
{
  return toUnixTimeStamp( Time );
} /* end Date::unixTmstmp() */

int Date::getSecond() const throw()
{
  return Time.tm_sec;
} /* end Date::getSecond() */

int Date::getDay() const throw()
{
  return Time.tm_mday;
} /* end Date::getDay() */

/**
 * getMonth()
 *
 * Returns the number of the month,
 * January being 0 to December at 11
 */
int Date::getMonth() const throw()
{
  return Time.tm_mon;
} /* end Date::getMonth() */

/**
 * getYear()
 *
 * Returns the number of years since 1900
 */
int Date::getYear() const throw()
{
  return Time.tm_year;
} /* end Date::getYear() */

/* Modifiers */

void Date::setSeconds(
		      int aSeconds
		      )
  throw ( DateException )
{
  settm( getDay(), getMonth(), getYear(), aSeconds );
} /* end Date::setSeconds() */

void Date::setDay(
		  int aDay
		  )
  throw( DateException )
{
  settm( aDay, getMonth(), getYear(), getSecond() );
} /* end Date::setDay() */

void Date::setMonth(
		    int aMonth
		    )
  throw( DateException )
{
  settm( getDay(), aMonth, getYear(), getSecond() );
} /* end Date::setMonth() */

void Date::setYear(
		   int aYear
		   )
  throw( DateException )
{
  settm( getDay(), getMonth(), aYear, getSecond() );
} /* end Date::setYear() */

/* Methods */

double Date::diffDate(
		   const Date& aDate
		   )
const
{
  time_t aTime = aDate.unixTmstmp();
  time_t myTime = toUnixTimeStamp( Time );

  return difftime( myTime, aTime );
} /* end Date::addDate() */

bool Date::isLessThan(
		      const Date& aDate
		      )
const
{
  if( aDate.getYear() > getYear() )
    return true;
  else if( aDate.getMonth() > getMonth() )
    return true;
  else if( aDate.getDay() > getDay() )
    return true;
  else if( aDate.getSecond() > getSecond() )
    return true;
  else
    return false;
} /* end Date::isLessThan() */

bool Date::isEqualTo(
	       const Date& aDate
		     )
const
{
  return ( aDate.getYear() == getYear() && aDate.getMonth() == getMonth() && aDate.getDay() == getDay() && aDate.getSecond() == getSecond() );
} /* end Date::isEqualTo() */

/**
 * toString()
 *
 * Returns a string representation of the date.
 * Format: YYYY-MM-DD
 */
std::string Date::toString( bool showTime ) const
{
  char buffer[80];
  std::string format("%F");

  if( showTime )
    format += " %R";

  strftime( buffer, 80, format.c_str(), &Time );

  return std::string( buffer );
} /* end Date::toString() */

void Date::adjust(
		  int aAmount,
		  Date::GRANULARITY granularity
		  )
  throw( DateException )
{
  if( granularity == SECOND )
    {
      adjustSeconds( aAmount );
    }
  else if( granularity == MIN )
    {
      adjustMinutes( aAmount );
    }
  else if( granularity == DAY )
    {
      adjustDay( aAmount );
    }
  else if( granularity == WEEK )
    {
      adjustDay( aAmount * 7 );
    }
  else if( granularity == MONTH )
    {
      adjustMonth( aAmount );
    }
  else if( granularity == YEAR )
    {
      adjustYear( aAmount );
    }
  else
    {
      throw( DateException( "Incorrect granularity!" ) );
    } 
} /* end Date::adjust() */

/* Operator Overloads */
bool Date::operator<(
	       const Date& other
		     )
const
{
  return( isLessThan( other ) );
} /* end Date::operator<() */

bool Date::operator>(
		     const Date& other
		     )
const
{
  return( !isLessThan( other ) && !isEqualTo( other ) );
} /* end Date::operator>() */

bool Date::operator<=(
		      const Date& other
		      )
const
{
  return( isLessThan( other ) || isEqualTo( other ) );
} /* end Date::operator<=() */

bool Date::operator>=(
		      const Date& other
		      )
const
{
  return( !isLessThan( other ) );
} /* end Date::operator>=() */

bool Date::operator==(
		      const Date& other
		      )
const
{
  return( isEqualTo( other ) );
} /* end Date::operator==() */

bool Date::operator!=(
		      const Date& other
		      )
const
{
  return( !isEqualTo( other ) );
} /* end Date::operator!=() */

Date& Date::operator=(
		      const Date& rhs
		      )
{
  /* Have to pass in year + 1900 because settm subtracts 1900 from the year */
  /* and in this case, 1900 has already been subtracted, so we don't want   */
  /* to do it twice */
  if( rhs != *this )
    settm( rhs.getDay(), rhs.getMonth(), rhs.getYear() + 1900, rhs.getSecond() );
  return *this;
} /* end Date::operator=() */

double Date::operator-(
		      const Date& rhs
		      )
{
  return( diffDate( rhs ) );
} /* end Date::operator-() */

/* Private Methods */

void Date::settm(
		int aDay,
		int aMonth,
		int aYear,
		int aSecond
		)
  throw( DateException )
{
  if( aMonth > 11 )
    throw DateException( "Out of range for month" );

  if( aDay > getDaysInMonth( aMonth, aYear ) )
    throw DateException( "Out of range for day" );

  if( aSecond > 86400 )
    throw DateException( "Out of range for seconds" );

  Time.tm_sec = aSecond % 60;
  Time.tm_min = aSecond / 60;
  Time.tm_hour = aSecond / 3600;
  Time.tm_mday = aDay;
  Time.tm_mon = aMonth;
  Time.tm_year = aYear - 1900;

  int centuryNumber;

  /* Formula for calculating the day of the week      */
  /* d + m + y + (last 2 digits of year) / 4 + c      */
  /* d = day, m = month, y = year, c = century number */
  /* the century number is 6 if the two significant   */
  /* digits of the year are divisible by 4, then the  */
  /* subsequent centuries are 4, 2, 0.                */
  /* ( 2000 => 6, 2100 => 4, 2200 => 2, 2300 => 0 )   */
  /* check out wiki: "Determination of the day of the week" */
  centuryNumber = 6 - ( ( aYear / 100 ) % 4 );
  Time.tm_wday = ( aDay + aMonth + aYear + ( ( aYear % 100 ) / 4 ) + centuryNumber ) % 7; 

  /* To get the day in the year, add the number of    */
  /* days in each month before the current month      */
  /* then add the day of the current month to that    */
  /* total.                                           */
  int yday = 0;
  for( int i = 0; i < aMonth; ++i )
    {
      yday += getDaysInMonth( i, getYear() );
    }

  yday += aDay;

  Time.tm_yday = yday;

  /* I don't want to worry about day light savings   */
  Time.tm_isdst = -1;
} /* end Date::init() */

void Date::adjustSeconds(
		   int aAmount
		   )
  throw( DateException )
{
  int addSeconds = getSecond() + aAmount;
  if( addSeconds > 86400 )
    {
      adjustDay( addSeconds / 86400 );
      addSeconds = addSeconds % 86400;
    }
  setSeconds( addSeconds );
} /* end Date::adjustSeconds() */

void Date::adjustMinutes(
			 int aAmount
			 )
  throw( DateException )
{
  adjustSeconds( aAmount * 60 );
} /* end Date::adjustMinutes() */

void Date::adjustDay(
		     int aAmount
		     )
  throw( DateException )
{
  int addDays = aAmount + getDay();
  int daysInMonth = getDaysInMonth( getMonth(), getYear() );

  while( addDays >= daysInMonth )
    {
      adjustMonth( 1 );
      addDays = addDays - daysInMonth;
      /* month should have been moved up 1 */
      daysInMonth = getDaysInMonth( getMonth(), getYear() );
    }

  setDay( addDays );
} /* end Date::adjustDay() */

void Date::adjustMonth(
		       int aAmount
		       )
  throw( DateException )
{
  int addMonth = aAmount + getMonth();

  if( addMonth >= 12 )
    {
      adjustYear( addMonth / 12 );
      addMonth = addMonth % 12;
    }

  setMonth( addMonth );
} /* end Date::adjustMonth() */

void Date::adjustYear(
		      int aAmount
		      )
  throw( DateException )
{
  setYear( getYear() + aAmount );
} /* end Date::adjustYear() */

 int Date::getDaysInMonth(
			 int aMonth,
			 int aYear
			 )
   const
   throw( DateException )
{
  switch( aMonth )
    {
    case 0:
    case 2:
    case 4:
    case 6:
    case 7:
    case 9:
    case 11:
      return 31;
      break;
    case 3:
    case 5:
    case 8:
    case 10:
      return 30;
      break;
    case 1:
      {
	if( aYear % 4 == 0 )
	  {
	    if( aYear % 100 != 0 || aYear % 400 == 0 )
	      return 29;
	    else
	      return 28;
	  } 
	else
	  return 28;
      }
      break;
    default:
      throw( DateException( "Out of range for month" ) );
      break;
    }

} /* end Date::getDayInMonth() */
 
struct tm Date::toTmStruct(
			    time_t aTimeStamp
			    )
  throw()
{
  return *gmtime( &aTimeStamp );
} /* end Date::timestampToStruct() */

time_t Date::toUnixTimeStamp(
		       struct tm aTime
		       )
  const
  throw( DateException )
{
  return mktime( &aTime );
} /* end Date::toUnixTimeStamp() */
