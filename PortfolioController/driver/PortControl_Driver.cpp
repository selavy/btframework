#include<iostream>
#include "../src/PortfolioController.hpp"
#include<thread>
#include<mutex>
#include<gmpxx.h>
#include<iomanip>

using namespace std;

void printer( Portfolio * p );

int main( int argc, char ** argv )
{
  PortfolioController PortControl;

  cout << "Adding portfolio named first with $100000" << endl;
  PortControl.addPortfolio( "first", mpf_class( 100000 ) );

  cout << "Adding portfolio named second with $1" << endl;
  PortControl.addPortfolio( "second", 1 );

  cout << "Adding portfolio named third with $99999.99" << endl;
  PortControl.addPortfolio( "third", mpf_class( "99999.99", 512 ) );

  cout << "Printing portfolios..." << endl;
  PortControl.run( &printer );

  return 0;
}

void printer( Portfolio * p )
{
  PortfolioController::lockMutex();
  cout << p->getName() << " with $" << setprecision(12) << p->getCurrentCapital() << endl;
  PortfolioController::unlockMutex();
}
