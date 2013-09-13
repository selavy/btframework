#include "DateException.hpp"

DateException::DateException() :
  reason("Date exception")
{}

DateException::DateException( const char * message ) :
  reason( message )
{}

const char * DateException::what() const throw() {
  return reason.c_str();
}
