#include "Database.hpp"

Database * Database::instance = NULL;
std::mutex Database::mtx;

Database::Database( std::string aDatabase )
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

double Database::getLatestPrice( std::string aCompanyName )
{
  Database::lockMutex();

  double mean;
  double variance;

  std::unordered_map<std::string, double>::const_iterator got = Mean.find( aCompanyName );

  if( got == Mean.end() )
    {
      mean = ( rand() % 50 + 15 ) / 100.0;
      variance = ( rand() % 25 + 5 ) / 100.0;
      Mean.insert( std::make_pair( aCompanyName, mean ) );
      Variance.insert( std::make_pair( aCompanyName, variance ) );
    }
  else
    {
      mean = got->second;

      got = Variance.find( aCompanyName );
      variance = got->second;
    }

  mean *= ( rand() % 50 );
  variance *= ( rand() % 25 );

  Database::unlockMutex();
  return mean + variance;
} /* end Database::getLatesetPrice() */

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
