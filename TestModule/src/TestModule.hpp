#include "../../Module/src/Module.hpp"
#include<vector>
#include<utility>

namespace TestModuleTrigger
{

std::vector<std::pair> trigger( std::vector<std::string> args )
{
      /**************************************/
      /** Module Message Format            **/
      /* arg #  |  data                    **/
      /* ------------------------          **/
      /*  0     | Current Capital          **/
      /*  1     | Five Day Moving Average  **/
      /*  2     | Ten Day Moving Average   **/
      /*  3     | Company Name             **/
      /*  4     | Current Price Per Share  **/
      /**************************************/

  std::vector<std::pair> message;
  if( args.length() != 5 ) /* mal-formatted message */
    {
      message.push_back( std::make_pair( "", 0 ) );
      return message;
    }

  fiveDay = std::atod( args.at(1) );
  tenDay = std::atod( args.at(2) );

  if( fiveDay > tenDay )
    {
      std::vector<std::pair> message;
      int amountToBuy = ( args.at(0) * .2 ) / args.at(4);
      message.push_back( std::make_pair( args.at(3), amountToBuy ) );
      return message;
    }
  else
    {
      message.push_back( std::make_pair( args.at(3), 0 ) );
      return message;
    }
}

}
