#include<iostream>
#include<string>

using namespace std;

int main( int argc, char** argv )
{
  if( argc != 14 )
    {
      cout << "NOP" << endl;
      return 1;
    }

  string companyName( argv[1] );
  string strCurrentNShares( argv[13] );
  string strRawData;
  double rawData[10];

  for( int i = 0; i < 10; ++i )
    {
      strRawData = argv[ i + 2 ];
      rawData[i] = std::stod( strRawData );
    }
  string strCapital( argv[12] );

  double sharePrice  = rawData[9];
  double capital     = std::stod( strCapital        );
  int currentNShares = std::stod( strCurrentNShares );


  double fiveDayMvAvg = 0.0;
  double tenDayMvAvg = 0.0;
  for( int i = 0; i < 5; ++i )
    {
      tenDayMvAvg += rawData[i];
    }

  for( int i = 5; i < 10; ++i )
    {
      fiveDayMvAvg += rawData[i];
    }

  tenDayMvAvg += fiveDayMvAvg;
  fiveDayMvAvg = fiveDayMvAvg / 5;
  tenDayMvAvg = tenDayMvAvg / 10;

  if( fiveDayMvAvg > tenDayMvAvg )
    {
      cout << companyName << " " << static_cast<int>( capital * .2 / sharePrice ) << endl;
    }
  else if( 1.2 * fiveDayMvAvg < tenDayMvAvg )
    {
      cout << companyName << " " << static_cast<int>( -1 * currentNShares * .5 ) << endl;
    }
  else
    {
      cout << companyName << " 0" << endl;
    }
  return 0;
}
