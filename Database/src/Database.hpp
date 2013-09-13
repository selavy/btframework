#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

#include<unordered_map>
#include<thread>
#include<mutex>

class Database
{
public:
  virtual ~Database() {}
  static Database * getInstance();

  double getLatestPrice( std::string aCompanyName );

private:
  Database( std::string aDatabaseName );

  static Database * instance;
  static void lockMutex();
  static void unlockMutex();

  std::unordered_map<std::string, double> Mean;
  std::unordered_map<std::string, double> Variance;

  static std::mutex mtx;
};

#endif
