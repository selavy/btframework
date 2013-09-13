#ifndef __DATEEXCEPTION_HPP__
#define __DATEEXCEPTION_HPP__

#include<exception>
#include<string>

class DateException : public std::exception
{
public:
  DateException();
  DateException( const char * );
  ~DateException() throw() {}
  virtual const char * what() const throw(); 
private:
  std::string reason;
};

#endif
