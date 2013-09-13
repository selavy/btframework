#include "Portfolio.hpp"
#include "../../Database/src/Database.hpp"

Portfolio::Portfolio() :
  Name(""),
  InitialCapital( 0.0 ),
  CurrentCapital( 0.0 ),
  NetWorth( 0.0 )
{
} /* end Portfolio::Portfolio() */

Portfolio::Portfolio(
		     std::string aName,
		     double aInitialValue
		     )
  :
  Name( aName ),
  InitialCapital( aInitialValue ),
  CurrentCapital( aInitialValue ),
  NetWorth( aInitialValue )
{
} /* end Portfolio::Portfolio() */

Portfolio::Portfolio(
		     std::string aName,
		     double aInitialValue,
		     std::unordered_map<std::string, int> aHoldings
		     )
  :
  Name( aName ),
  Holdings( aHoldings ),
  InitialHoldings( aHoldings ),
  InitialCapital( aInitialValue ),
  CurrentCapital( aInitialValue )
{
  NetWorth = aInitialValue;

  for( auto it = std::begin( Holdings ); it != std::end( Holdings ); ++it )
    {
      NetWorth += Database::getInstance()->getLatestPrice( it->first ) * it->second;
    }
} /* end Portfolio::Portfolio() */

/* Copy Constructor */
Portfolio::Portfolio(
		     const Portfolio& aPortfolio
		     )
{
  Name = aPortfolio.getName();
  Holdings = aPortfolio.getHoldings();
  InitialHoldings = aPortfolio.getInitialHoldings();
  InitialCapital = aPortfolio.getInitialCapital();
  CurrentCapital = aPortfolio.getCurrentCapital();
  NetWorth = aPortfolio.getNetWorth();
} /* end Portrolio::Portfolio() */

std::string Portfolio::getName() const throw()
{
  return Name;
} /* end Portfolio::getName() */

int Portfolio::hasHolding(
			  std::string companyName
			  )
  const
{
  std::unordered_map<std::string, int>::const_iterator got = Holdings.find( companyName );

  if( got == Holdings.end() )
    {
      /* Do not have the stock */
      return 0;
    }

  return got->second;
} /* end Portfolio::hasHolding() */

double Portfolio::getInitialCapital() const throw()
{
  return InitialCapital;
} /* end Portfolio::getInitialCapital() */

double Portfolio::getNetWorth() const throw()
{
  return NetWorth;
} /* end Portfolio::getNetWorth() */

double Portfolio::getCurrentCapital() const throw()
{
  return CurrentCapital;
} /* end Portfolio::getCurrentCapital() */

std::unordered_map<std::string, int> Portfolio::getHoldings() const throw()
{
  return Holdings;
} /* end Portfolio::getHoldings() */

std::unordered_map<std::string, int> Portfolio::getInitialHoldings() const throw()
{
  return InitialHoldings;
} /* end Portfolio::getInitalHoldings() */

void Portfolio::print( std::ostream & os )
{
  os << "Portfolio: " << getName() << std::endl;

  if( Holdings.empty() )
    {
      os << "No holdings!" << std::endl;
      return;
    }

  for( auto it = std::begin( Holdings ); it != std::end( Holdings ); ++it )
    {
      os << it->second << " shares of: " << it->first << std::endl;
    }
} /* end Portfolio::print() */

void Portfolio::setName(
			std::string aName
			)
{
  Name = aName;
} /* end Portfolio::setName() */

void Portfolio::setInitialCapital(
				  double aAmount
				  )
{
  InitialCapital = aAmount;
} /* end Portfolio::setInitalCapital() */

void Portfolio::action(
		       std::string aCompanyName,
		       int aAmount,               //<! Positive = buy, Negative = sell
		       int aSharePrice
		       )
{
  if( aAmount == 0 )
    return;

  if( aAmount < 0 )
    sell( aCompanyName, -1 * aAmount, aSharePrice );
  else
    buy( aCompanyName, aAmount, aSharePrice );
} /* end Portfolio::action() */

void Portfolio::sellAllPositions()
{
  for( auto it = std::begin( Holdings ); it != std::end( Holdings ); ++it )
    {
      sell( it->first, it->second, Database::getInstance()->getLatestPrice( it->first ) );
    }
} /* end Portfolio::sellAllPositions() */

void Portfolio::calcNetWorth()
{
  NetWorth = getCurrentCapital();

  for( auto it = std::begin( Holdings ); it != std::end( Holdings ); ++it )
    {
      NetWorth += ( Database::getInstance()->getLatestPrice( it->first ) * it->second );
    }
} /* end Portfolio::calcNetWorth() */

void Portfolio::sell( std::string aCompanyName, int aAmount, int aSharePrice )
{
  std::unordered_map<std::string, int>::const_iterator got = Holdings.find( aCompanyName );

  if( got == Holdings.end() )
    {
      /* Don't own this stock */
      return;
    }

  int amountToSell = ( got->second > aAmount ) ? aAmount : got->second;

  CurrentCapital += ( amountToSell * aSharePrice );

  Holdings.at( aCompanyName ) -= amountToSell;

  if( Holdings.at( aCompanyName ) <= 0 )
    {
      Holdings.erase( aCompanyName );
    }

  /* recalculate networth */
  calcNetWorth();
} /* end Portfolio::sell() */

void Portfolio::buy( std::string aCompanyName, int aAmount, int aSharePrice )
{
  if( ( aAmount * aSharePrice ) > getCurrentCapital() )
    {
      /* don't have enough capital to make this purchase */
      /* maybe in the future we will remove this check   */
      /* if there is some way to get loans/buy on margin */
      return;
    }

  CurrentCapital -= ( aAmount * aSharePrice );

  std::unordered_map<std::string, int>::iterator got = Holdings.find( aCompanyName );

  if( got == Holdings.end() )
    {
      /* don't own this stock already */
      Holdings.insert( std::make_pair(aCompanyName, aAmount ) );
    }
  else
    {
      got->second += aAmount;
    }

  /* recalculate networth */
  calcNetWorth();
} /* end Portfolio::buy() */
