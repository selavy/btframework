#include<iostream>
#include<boost/asio.hpp>
#include<boost/thread/thread.hpp>
#include<boost/date_time/posix_time/posix_time.hpp>
#include<boost/date_time/posix_time/posix_time_io.hpp>

void timer_expired( const boost::system::error_code& e )
{
  boost::posix_time::ptime now_time = boost::posix_time::second_clock::local_time();
  std::cout << now_time << " : timer expired." << std::endl;
}

int main()
{
  boost::posix_time::ptime now_time;


  boost::asio::io_service asio_service;

  boost::asio::deadline_timer timer( asio_service,
				     boost::posix_time::seconds(5) );
  now_time  = boost::posix_time::second_clock::local_time();
  std::cout << now_time << " : request async_wait 5-seconds" << std::endl;
  timer.async_wait( timer_expired );

  now_time = boost::posix_time::second_clock::local_time();
  std::cout << now_time << " : sleep 3-seconds" << std::endl;
  boost::this_thread::sleep( boost::posix_time::seconds(3) );

  now_time = boost::posix_time::second_clock::local_time();
  std::cout << now_time << " : calling io_service::run" << std::endl;
  asio_service.run();

  now_time = boost::posix_time::second_clock::local_time();
  std::cout << now_time << " : done." << std::endl;

  return 1;
}
