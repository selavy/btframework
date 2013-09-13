#include "PortfolioController.hpp"

/* class variable */
std::mutex PortfolioController::mtx;

PortfolioController::PortfolioController()
{
} /* end PortfolioController::PortfolioController() */

PortfolioController::~PortfolioController()
{
} /* end PortfolioController::~PortfolioController() */

void PortfolioController::addPortfolio(
				       std::string aName,
				       mpf_class initialValue,
				       std::unordered_map<std::string, int> aHoldings
				       )
{
  PortfoliosList.push_back( new Portfolio( aName, initialValue, aHoldings ) );
} /* end PortfolioController::addPortfolio() */

void PortfolioController::addPortfolio(
				       std::string aName,
				       double initialValue,
				       std::unordered_map<std::string, int> aHoldings
			     )
{
  PortfoliosList.push_back( new Portfolio( aName, mpf_class( initialValue, 2 ), aHoldings ) );
} /* end PortfolioController::addPortfolio() */

void PortfolioController::addPortfolio(
				       std::string aName,
				       mpf_class initialValue
				       )
{
  PortfoliosList.push_back( new Portfolio( aName, initialValue ) );
} /* end PortfolioController::addPortfolio() */

void PortfolioController::addPortfolio(
				       std::string aName,
				       double initialValue
				       )
{
  PortfoliosList.push_back( new Portfolio( aName, mpf_class( initialValue, 2 ) ) );
} /* end PortfolioController::addPortfolio() */

void PortfolioController::run(
			      void (*visitor)( Portfolio* )
			      )
{
  std::vector<std::thread> threadList;

  for( auto it = std::begin( PortfoliosList ); it != std::end( PortfoliosList ); ++it )
    {
      threadList.push_back( std::thread( visitor, *it ) );
    }

  for( std::vector<std::thread>::iterator it = threadList.begin(); it != threadList.end(); ++it )
    {
      it->join();
    }

} /* end PortfolioController::run() */

void PortfolioController::removePortfolio(
					  std::string aName
					  )
{
  for( auto it = std::begin( PortfoliosList ); it != std::end( PortfoliosList ); ++it )
    {
      if( (*it)->getName() == aName )
	{
	  PortfoliosList.erase( it );
	  return;
	}
    }
} /* end PortfolioController::removePortfolio() */

/**
 * Class method
 */
void PortfolioController::lockMutex()
{
  mtx.lock();
} /* end PortfolioController::lockMutex() */

/**
 * Class method
 */
void PortfolioController::unlockMutex()
{
  mtx.unlock();
} /* end PortfolioController::unlockMutex() */
