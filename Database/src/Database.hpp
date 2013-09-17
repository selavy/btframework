#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

#include<unordered_map>
#include<thread>
#include<mutex>
#include<exception>
#include "../../Date/src/Date.hpp"

class Database
{
public:
  enum STATUS {
    DEAD = 0,
    STARTING,
    ALIVE,
    STOPPING,
    STOPPED,
    WARNING
  };

  virtual ~Database() {}
  static Database * getInstance();

  double getLatestPrice( std::string aCompanySymbol );

  double getDaysLow( std::string aCompanySymbol, Date aDate );
  double getDaysHigh( std::string aCompanySymbol, Date aDate );
  double get52WeekLow( std::string aCompanySymbol, Date aDate );
  double get52WeekHigh( std::string aCompanySymbol, Date aDate );
  double get50DayMovingAverage( std::string aCompanySymbol, Date aDate );
  double get200DayMovingAverage( std::string aCompanySymbol, Date aDate );
  double getChange50DayMovingAverage( std::string aCompanySymbol, Date aDate );
  double getChange200DayMovingAverage( std::string aCompanySymbol, Date aDate );
  std::string getString( std::string aCompanySymbol );
  std::string getSymbol( std::string aCompanyName );
  long int getVolume( std::string aCompanySymbol, Date aDate );
  std::string getStockExchange( std::string aCompanySymbol );

private:
  class DatabaseException : public std::exception
  {
  public:
    DatabaseException();
    DatabaseException( std::string aMesssage, int aErrorCode );
    virtual ~DatabaseException() {}

    virtual const char * what() const throw();

  private:
    std::string Message;
    int ErrorCode;
  };

  Database( std::string aDatabaseName, unsigned int aMaxNumberOfRequests = 1 );

  long int getUptime();
  Database::STATUS getStatus();

  static Database * instance;
  static void lockMutex();
  static void unlockMutex();

  std::unordered_map<std::string, double> Mean;
  std::unordered_map<std::string, double> Variance;

  // TODO
  /* Add a maximum number of threads and give out that */
  /* many of database request threads (rather than     */
  /* just 1 thread :P )                                */

  static std::mutex mtx;
  unsigned int MaxNumberOfRequests;
};

#endif
