#include<iostream>
#include<string>

#include "../../Database/src/Database.hpp"

#include "../src/Portfolio.hpp"

int main( int argc, char ** argv )
{
  Portfolio a( "Peter's Portfolio", 1000000 );
  std::cout << "Printing empty portfolio...\n" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  a.action( "GE", 1000, Database::getInstance()->getLatestPrice( "GE" ) );
  a.action( "GOOGL", 500, Database::getInstance()->getLatestPrice( "GOOGL" ) );
  a.action( "GE", -500, Database::getInstance()->getLatestPrice( "GE" ) );
  a.action( "YHOO", 1000, Database::getInstance()->getLatestPrice( "YHOO" ) );
  a.print(std::cout);


  std::cout << a.getName() << std::endl;
  return 0;
}
