#ifndef __PORTFOLIO_HPP__
#define __PORTFOLIO_HPP__

#include<string>
#include<unordered_map>
#include<iostream>

class Portfolio
{
public:
  /* Constructors / Destructor */
  Portfolio();
  Portfolio( std::string aName, double aInitialValue );
  Portfolio( std::string aName, double aInitialValue, std::unordered_map<std::string, int> aHoldings );
  Portfolio( const Portfolio& aPortfolio );

  virtual ~Portfolio() {}

  /* Accessors */
  std::string getName() const throw();
  int hasHolding( std::string companyName ) const;
  double getInitialCapital() const throw();
  double getNetWorth() const throw();
  double getCurrentCapital() const throw();
  std::unordered_map<std::string, int> getHoldings() const throw();
  std::unordered_map<std::string, int> getInitialHoldings() const throw();
  void print( std::ostream & os );

  /* Modifiers */
  void setName( std::string aName );
  void setInitialCapital( double aAmount );

  /* Methods */
  void action( std::string aCompanyName, int aAmount, int aSharePrice );
  void sellAllPositions();

private:
  void calcNetWorth();
  void sell( std::string aCompanyName, int aAmount, int aSharePrice );
  void buy( std::string aCompanyName, int Amount, int aSharePrice );

  std::string Name;
  std::unordered_map<std::string, int> Holdings;
  std::unordered_map<std::string, int> InitialHoldings;
  double InitialCapital;
  double CurrentCapital;
  double NetWorth;
};

#endif
