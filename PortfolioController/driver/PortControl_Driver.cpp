#include<iostream>
#include "../src/PortfolioController.hpp"

using namespace std;

void printer( Portfolio * p );

int main( int argc, char ** argv )
{
  PortfolioController PortControl;

  cout << "Adding portfolio named first with $100000" << endl;
  PortControl.addPortfolio( "first", 100000 );

  cout << "Adding portfolio named second with $1" << endl;
  PortControl.addPortfolio( "second", 1 );

  cout << "Adding portfolio named third with $99999.99" << endl;
  PortControl.addPortfolio( "third", 99999.99 );

  cout << "Printing portfolios..." << endl;
  PortControl.run( &printer );

  return 0;
}

void printer( Portfolio * p )
{
  cout << p->getName() << " with $" << p->getCurrentCapital() << endl;
}
