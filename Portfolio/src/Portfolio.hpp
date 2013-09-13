#ifndef __PORTFOLIO_HPP__
#define __PORTFOLIO_HPP__

#include<string>
#include<unordered_map>
#include<iostream>
#include<gmpxx.h>

class Portfolio
{
public:
  /* Constructors / Destructor */
  Portfolio();
  Portfolio( std::string aName, double aInitialValue );
  Portfolio( std::string aName, double aInitialValue, std::unordered_map<std::string, int> aHoldings );
  Portfolio( std::string aName, mpf_class aInitialValue );
  Portfolio( std::string aName, mpf_class aInitialValue, std::unordered_map<std::string, int> aHoldings );
  Portfolio( const Portfolio& aPortfolio );

  virtual ~Portfolio() {}

  /* Accessors */
  std::string getName() const throw();
  int hasHolding( std::string companyName ) const;
  mpf_class getInitialCapital() const throw();
  mpf_class getNetWorth() const throw();
  mpf_class getCurrentCapital() const throw();
  double getDBLInitialCapital();
  double getDBLNetWorth();
  double getDBLCurrentCapital();
 
  std::unordered_map<std::string, int> getHoldings() const throw();
  std::unordered_map<std::string, int> getInitialHoldings() const throw();
  void print( std::ostream & os );

  /* Modifiers */
  void setName( std::string aName );
  void setInitialCapital( double aAmount );
  void setInitialCapital( mpf_class aAmount );

  /* Methods */
  void action( std::string aCompanyName, int aAmount, double aSharePrice );
  void sellAllPositions();

private:
  void calcNetWorth();
  void sell( std::string aCompanyName, int aAmount, double aSharePrice );
  void buy( std::string aCompanyName, int Amount, double aSharePrice );
  void setCurrentCapital( double aAmount );
  void setCurrentCapital( mpf_class aAmount );


  std::string Name;
  std::unordered_map<std::string, int> Holdings;
  std::unordered_map<std::string, int> InitialHoldings;
  mpf_class InitialCapital;
  mpf_class CurrentCapital;
  mpf_class NetWorth;
};

#endif
