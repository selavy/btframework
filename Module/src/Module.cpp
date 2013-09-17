#include "Module.hpp"
#include <iostream>

/*************************************************************/
/* Module::ModuleReaderException                             */
/*************************************************************/

Module::ModuleReaderException::ModuleReaderException()
  :
  FileName(""),
  MalformedLine(""),
  LineNumber( 0 )
{
} /* end Module::ModuleReaderException::ModuleReaderException() */

Module::ModuleReaderException::ModuleReaderException(
						     std::string aFileName,
						     std::string aMalformedLine,
						     int aLineNumber
						     )
  :
  FileName( aFileName ),
  MalformedLine( aMalformedLine ),
  LineNumber( aLineNumber )
{
} /* end Module::ModuleReaderException::ModuleReaderException() */

const char *Module::ModuleReaderException::what() const throw()
{
  std::string retStr = "Module Reader Exception";
  if( FileName != std::string("") )
    {
      retStr +=  std::string( " ( " );
      retStr += FileName;
      retStr += std::string( ")" );
    }

  if( MalformedLine != std::string("") )
    {
      retStr += std::string( " : Line " );
      retStr += std::to_string( LineNumber );
      retStr += std::string( " : " );
      retStr += MalformedLine;
    }

  return retStr.c_str();
} /* end Module::ModuleReaderException::what() */

/***************************************************************/
/* Module::ModuleHeaderReader                                  */
/***************************************************************/
Module::ModuleHeaderReader * Module::ModuleHeaderReader::mInstance = NULL;

Module::ModuleHeaderReader::ModuleHeaderReader()
  :
  ss(),
  FileName(""),
  Read( false )
{
} /* end Module::ModuleHeaderReader() */

Module::ModuleHeaderReader * Module::ModuleHeaderReader::getInstance()
{
  if( mInstance == NULL )
    {
      mInstance = new Module::ModuleHeaderReader();
    }

  return mInstance;
} /* end Module::ModuleHeaderReader::getInstance() */

void Module::ModuleHeaderReader::setFileName(
					std::string aFileName
					)
{
  FileName = aFileName;
} /* end Module::ModuleHeaderReader::setFileName() */

void Module::ModuleHeaderReader::read()
  throw( ModuleReaderException )
{
  if( Read )
    return;

  if( !ss.is_open() )
    {
      ss.open( FileName.c_str(), std::ifstream::in );
      if( !ss.is_open() )
	throw( new Module::ModuleReaderException );
    }

  /* read in the file */
  std::string line;
  
  while( getline( ss, line ) )
    {
	
    }

  Read = true;
} /* end Module::ModuleHeaderReader::read() */

/********************************************************************/
/* Module                                                           */
/********************************************************************/

Module::Module()
{
} /* end Module::Module() */

std::vector<std::string> Module::listOfNeededData() throw()
{
  try
    {
      Module::ModuleHeaderReader::getInstance()->read();
    }
  catch( Module::ModuleReaderException& e )
    {
      std::cerr << e.what() << std::endl;
      DataList.clear();
      DataList.push_back( std::string( "NOP" ) );
    }

  return DataList;
} /* end of Module::listOfNeededData() */

Date::GRANULARITY Module::getGranularity() const throw()
{
  return Granularity;
} /* end Module::getGranularity() */

void Module::setFileName( std::string aFileName )
{
  ModuleName = aFileName;
} /* end Module::setFileName() */
