#include<iostream>
#include<string>
#include<fstream>

int main( int argc, char** argv )
{
  std::ifstream ss("TestModuleHeader.txt");

  if( !ss.is_open() )
    {
      std::cout << "unable to open the file!" << std::endl;
      return 1;
    }

  std::string line;
  bool commandMode = true;

  while( getline( ss, line ) )
    {
      if( line.at(0) == '#' )
	{
	  continue;
	}
      else if( line == std::string("END") )
	{
	  break;
	}
      else if( line == std::string("ARGUMENTS") )
	{
	  commandMode = false;
	}
      else if( commandMode )
	{

	  std::size_t pos = line.find(" ");

	  if( pos == std::string::npos )
	    {
	      std::cout << "malformed command : " << line << std::endl;
	      return 1;
	    }
	  
	  std::string command = line.substr(0, pos);
	  
	  std::cout << "got command : " << command;

	  line = line.substr( pos );
	  pos = line.find(" ");

	  if( pos == std::string::npos )
	    {
	      std::cout << "\nmalformed command : " << line << std::endl;
	      return 1;
	    }

	  std::cout << "( " << line << ")" << std::endl;
	}
      else if( ! commandMode )
	{
	  if( line == std::string("END ARGUMENTS") )
	    {
	      commandMode = true;
	    }
	  else
	    {
	      std::cout << "Argument definition : " << line << std::endl;
	    }
	}
    }

  return 0;
}
