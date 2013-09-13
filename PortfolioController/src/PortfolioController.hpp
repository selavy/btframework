#ifndef __PORTFOLIOCONTROLLER_HPP__
#define __PORTFOLIOCONTROLLER_HPP__

#include "../../Portfolio/src/Portfolio.hpp"
#include<vector>
#include<unordered_map>
#include<thread>
#include<mutex>
#include<gmpxx.h>

class PortfolioController
{
public:
  PortfolioController();
  virtual ~PortfolioController();

  void addPortfolio( std::string aName, mpf_class initialValue, std::unordered_map<std::string, int> aHoldings );
  void addPortfolio( std::string aName, double initialValue, std::unordered_map<std::string, int> aHoldings );
  void addPortfolio( std::string aName, mpf_class initialValue );
  void addPortfolio( std::string aName, double initialValue );

  void run( void (*visitor)( Portfolio* ) );

  void removePortfolio( std::string aName );

  static void lockMutex();
  static void unlockMutex();
private:
  std::vector<Portfolio*> PortfoliosList;
  static std::mutex mtx;
};

#endif
