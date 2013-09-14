#ifndef __MODULE_HPP__
#define __MODULE_HPP__

#include<thread>
#include<mutex>
#include<vector>
#include<string>
#include<exception>
#include<fstream>
#include "../../Date/src/Date.hpp"

class Module
{
  Module();
  virtual ~Module() {}

  /* The list consists of a strings which */
  /* designate what data the module needs */
  std::vector<std::string> listOfNeededData() throw();
  Date::GRANULARITY getGranularity() const throw();
  void setFileName( std::string aFileName );

private:

  /**
   * Nested Class : ModuleReaderException
   * 
   * Exception that can be thrown by ModuleHeaderReader
   */
  class ModuleReaderException : public std::exception
  {
  public:
    ModuleReaderException();
    ModuleReaderException( std::string aFileName, std::string aMalformedLine, int aLineNumber );
    virtual ~ModuleReaderException() {}

    const char * what() const throw();

  private:
    std::string FileName;
    std::string MalformedLine;
    int LineNumber;
  };

  /**
   * Nested Class : ModuleHeaderReader
   *
   * Handles reading and parsing the module file
   */
  class ModuleHeaderReader
  {
  public:
    virtual ~ModuleHeaderReader();

    static ModuleHeaderReader * getInstance();
    void setFileName( std::string aFileName );
    void read() throw( ModuleReaderException );
  private:
    ModuleHeaderReader();

    static ModuleHeaderReader * mInstance;

    std::ifstream ss;
    std::string FileName;
    bool Read;
  };

  /* Private variables */
  std::string ModuleName;
  Date::GRANULARITY Granularity;
  std::vector<std::string> DataList;
};

#endif
