#include<iostream>
#include<string>
#include<ctime>
#include "../src/Date.hpp"
#include "../src/DateException.hpp"

using namespace std;

int main( int argc, char ** argv )
{
  /* Should be initialized to the current date */
  Date a;
  cout << "A: " << a.toString(true) << endl;

  time_t aTime;
  struct tm * timeinfo;

  time( &aTime );
  timeinfo = localtime( &aTime );

  Date b( *timeinfo );
  cout << "B: " << b.toString() << endl;

  timeinfo->tm_hour = 0;
  timeinfo->tm_min = 0;
  timeinfo->tm_sec = 0;
  timeinfo->tm_mon = 0;
  timeinfo->tm_mday = 1;

  Date c( *timeinfo );
  cout << "C: " << c.toString() << endl;

  if( b == c )
    cout << "B == C" << endl;
  else
    cout << "B != C" << endl;


  cout << "running B = C" << endl;
  b = c;

  if( b == c )
    cout << "B == C" << endl;
  else
    cout << "B != C" << endl;

  cout << "Now b = " << b.toString(true) << " and c = " << c.toString(true) << endl;

  cout << "Now b should be less than a..." << endl;

  if( b < a )
    cout << "b is less than a" << endl;
  else
    cout << "b is not less than a" << endl;

  cout << "a - b = " << Date::secondsToDays( a - b ) << " days." << endl; 
  return 0;
}
