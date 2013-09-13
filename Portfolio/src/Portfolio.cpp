#include "Portfolio.hpp"
#include "../../Database/src/Database.hpp"

Portfolio::Portfolio() :
  Name("")
{
  setInitialCapital( 0.0 );
  setCurrentCapital( 0.0 );
  calcNetWorth();
} /* end Portfolio::Portfolio() */

Portfolio::Portfolio(
		     std::string aName,
		     double aInitialValue
		     )
  :
  Name( aName )
{
  setInitialCapital( aInitialValue );
  setCurrentCapital( aInitialValue );
  calcNetWorth();
} /* end Portfolio::Portfolio() */

Portfolio::Portfolio(
		     std::string aName,
		     double aInitialValue,
		     std::unordered_map<std::string, int> aHoldings
		     )
  :
  Name( aName ),
  Holdings( aHoldings ),
  InitialHoldings( aHoldings )
{
  setInitialCapital( aInitialValue );
  setCurrentCapital( aInitialValue );
  calcNetWorth();
} /* end Portfolio::Portfolio() */

Portfolio::Portfolio(
		     std::string aName,
		     mpf_class aInitialValue
		     )
  :
  Name( aName ),
  InitialCapital( aInitialValue ),
  CurrentCapital( aInitialValue ),
  NetWorth( aInitialValue)
{
} /* end Portfolio::Portfolio() */

Portfolio::Portfolio(
		     std::string aName,
		     mpf_class aInitialValue,
		     std::unordered_map<std::string, int> aHoldings
		     )
  :
  Name( aName ),
  Holdings( aHoldings ),
  InitialHoldings( aHoldings ),
  InitialCapital( aInitialValue ),
  CurrentCapital( aInitialValue )
{
  calcNetWorth();
} /* end Portfoliio::Portfolio() */

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

mpf_class Portfolio::getInitialCapital() const throw()
{
  return InitialCapital;
} /* end Portfolio::getInitialCapital() */

mpf_class Portfolio::getNetWorth() const throw()
{
  return NetWorth;
} /* end Portfolio::getNetWorth() */

mpf_class Portfolio::getCurrentCapital() const throw()
{
  return CurrentCapital;
} /* end Portfolio::getCurrentCapital() */

double Portfolio::getDBLInitialCapital()
{
  return InitialCapital.get_d();
} /* end Portfolio::getDBLInitialCapital() */

double Portfolio::getDBLNetWorth()
{
  /** TODO **/
  return NetWorth.get_d();
} /* end Portfolio::getDBLNetWorth() */

double Portfolio::getDBLCurrentCapital()
{
  /** TODO **/
  return CurrentCapital.get_d();
} /* end Portfolio::getDBLCurrentCapital() */

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
  InitialCapital = mpf_class( aAmount, 2 );
} /* end Portfolio::setInitalCapital() */

void Portfolio::setInitialCapital(
				  mpf_class aAmount
				  )
{
  InitialCapital = mpf_class( aAmount, 2 );
} /* end Portfolio::setInitialCapital() */

void Portfolio::action(
		       std::string aCompanyName,
		       int aAmount,               //<! Positive = buy, Negative = sell
		       double aSharePrice
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
      NetWorth += mpf_class( Database::getInstance()->getLatestPrice( it->first ) * it->second );
    }
} /* end Portfolio::calcNetWorth() */

void Portfolio::sell( std::string aCompanyName, int aAmount, double aSharePrice )
{
  std::unordered_map<std::string, int>::const_iterator got = Holdings.find( aCompanyName );

  if( got == Holdings.end() )
    {
      /* Don't own this stock */
      return;
    }

  int amountToSell = ( got->second > aAmount ) ? aAmount : got->second;

  CurrentCapital += mpf_class( amountToSell * aSharePrice );

  Holdings.at( aCompanyName ) -= amountToSell;

  if( Holdings.at( aCompanyName ) <= 0 )
    {
      Holdings.erase( aCompanyName );
    }

  /* recalculate networth */
  calcNetWorth();
} /* end Portfolio::sell() */

void Portfolio::buy( std::string aCompanyName, int aAmount, double aSharePrice )
{
  if( mpf_class( aAmount * aSharePrice ) > getCurrentCapital() )
    {
      /* don't have enough capital to make this purchase */
      /* maybe in the future we will remove this check   */
      /* if there is some way to get loans/buy on margin */
      return;
    }

  CurrentCapital -= mpf_class( aAmount * aSharePrice );

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

void Portfolio::setCurrentCapital( double aAmount )
{
  CurrentCapital = mpf_class( aAmount, 2 );
} /* end Portfolio::setCurrentCapital() */

void Portfolio::setCurrentCapital( mpf_class aAmount )
{
  CurrentCapital = mpf_class( aAmount, 2 );
} /* end Portfolio::setCurrentCapital() */
