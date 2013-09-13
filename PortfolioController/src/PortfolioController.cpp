#include "PortfolioController.hpp"

PortfolioController::PortfolioController()
{
} /* end PortfolioController::PortfolioController() */

PortfolioController::~PortfolioController()
{
} /* end PortfolioController::~PortfolioController() */

void PortfolioController::addPortfolio(
			     std::string aName,
			     double initialValue,
			     std::unordered_map<std::string, int> aHoldings
			     )
{
  PortfoliosList.push_back( new Portfolio( aName, initialValue, aHoldings ) );
} /* end PortfolioController::addPortfolio() */

void PortfolioController::addPortfolio(
			     std::string aName,
			     double initialValue
			     )
{
  PortfoliosList.push_back( new Portfolio( aName, initialValue ) );
} /* end PortfolioController::addPortfolio() */

void PortfolioController::run(
		    void (*visitor)( Portfolio* )
		    )
{
  for( auto it = std::begin( PortfoliosList ); it != std::end( PortfoliosList ); ++it )
    {
      (*visitor)( *it );
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
