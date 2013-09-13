#ifndef __PORTFOLIOCONTROLLER_HPP__
#define __PORTFOLIOCONTROLLER_HPP__

#include "../../Portfolio/src/Portfolio.hpp"
#include<vector>
#include<unordered_map>

class PortfolioController
{
public:
  PortfolioController();
  virtual ~PortfolioController();

  void addPortfolio( std::string aName, double initialValue, std::unordered_map<std::string, int> aHoldings );
  void addPortfolio( std::string aName, double initialValue );

  void run( void (*visitor)( Portfolio* ) );

  void removePortfolio( std::string aName );

private:
  std::vector<Portfolio*> PortfoliosList;
};

#endif
