#include "Database.hpp"

Database * Database::instance = NULL;
std::mutex Database::mtx;

Database::Database( std::string aDatabase, unsigned int aMaxNumberOfRequests )
  :
  MaxNumberOfRequests( aMaxNumberOfRequests )
{
} /* end Database::Database() */

Database * Database::getInstance()
{
  if( instance == NULL )
    {
      instance = new Database( "PLACEHOLDER" );
    }

  return instance;
}

double Database::getLatestPrice( std::string aCompanySymbol )
{
  Database::lockMutex();

  double mean;
  double variance;

  std::unordered_map<std::string, double>::const_iterator got = Mean.find( aCompanySymbol );

  if( got == Mean.end() )
    {
      mean = ( rand() % 50 + 15 ) / 100.0;
      variance = ( rand() % 25 + 5 ) / 100.0;
      Mean.insert( std::make_pair( aCompanySymbol, mean ) );
      Variance.insert( std::make_pair( aCompanySymbol, variance ) );
    }
  else
    {
      mean = got->second;

      got = Variance.find( aCompanySymbol );
      variance = got->second;
    }

  mean *= ( rand() % 50 );
  variance *= ( rand() % 25 );

  Database::unlockMutex();
  return mean + variance;
} /* end Database::getLatesetPrice() */

double Database::getDaysLow( std::string aCompanySymbol, Date aDate )
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return 0.0;
} /* end Database::getDaysLow() */

double Database::getDaysHigh( std::string aCompanySymbol, Date aDate )
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return 0.0;
} /* end Database::getDaysHigh() */

double Database::get52WeekLow( std::string aCompanySymbol, Date aDate )
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return 0.0;
} /* end Database::get52WeekLow() */

double Database::get52WeekHigh( std::string aCompanySymbol, Date aDate )
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();  
  return 0.0;
} /* end Database::get52WeekHigh() */

double Database::get50DayMovingAverage( std::string aCompanySymbol, Date aDate )
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return 0.0;
} /* end Database::get50DayMovingAverage() */

double Database::get200DayMovingAverage( std::string aCompanySymbol, Date aDate )
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return 0.0;
} /* end Database::get200DayMovingAverage() */

double Database::getChange50DayMovingAverage( std::string aCompanySymbol, Date aDate )
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return 0.0;
} /* end Database::getChange50DayMovingAverage() */

double Database::getChange200DayMovingAverage( std::string aCompanySymbol, Date aDate )
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return 0.0;
} /* end Database::getChange200DayMovingAverage() */

std::string Database::getString( std::string aCompanySymbol)
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return "";
} /* end Database::getString() */

std::string Database::getSymbol( std::string aCompanyName )
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return "";
} /* end Database::getSymbol() */

long int Database::getVolume( std::string aCompanySymbol, Date aDate )
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return 0;
} /* end Database::getVolume() */

std::string Database::getStockExchange( std::string aCompanySymbol )
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return "";
} /* end Database::getStockExchange() */

long int Database::getUptime()
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return 0;
} /* end Database::getUptime() */

Database::STATUS Database::getStatus()
{
  Database::lockMutex();
  // TODO
  Database::unlockMutex();
  return Database::ALIVE;
} /* end Database::getStatus */

/**
 * Class Method
 */
void Database::lockMutex()
{
  mtx.lock();
} /* end Database::lockMutex() */

/**
 * Class Method
 */
void Database::unlockMutex()
{
  mtx.unlock();
} /* end Database::unlockMutex() */

/**************************************************************************************************/
/* DatabaseException class                                                                        */
/**************************************************************************************************/

Database::DatabaseException::DatabaseException()
  :
  Message(""),
  ErrorCode(-1)
{
} /* end Database::DatabaseException::DatabaseException() */

Database::DatabaseException::DatabaseException(
			    std::string aMessage,
			    int aErrorCode
			    )
  :
  Message( aMessage ),
  ErrorCode( aErrorCode )
{
} /* end Database::DatabaseException::DatabaseException() */

const char * Database::DatabaseException::what() const throw()
{
  std::string retMessage = "DatabaseException";
  retMessage += std::string("(") + std::to_string( ErrorCode ) + std::string(")");
  retMessage += std::string(": ") + Message;

  return retMessage.c_str();
} /* end Database::DatabaseException::what() */
