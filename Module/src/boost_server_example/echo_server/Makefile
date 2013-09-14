CC = g++
CFLAGS = -Wall -Werror -pedantic -std=c++11 -g
THREAD = -lpthread
BOOST = -lboost_system -lboost_thread

all:
	$(CC) $(CFLAGS) blocking_tcp_echo_client.cpp $(THREAD) $(BOOST) -o blocking_tcp_echo_client
	$(CC) $(CFLAGS) blocking_tcp_echo_server.cpp $(THREAD) $(BOOST) -o blocking_tcp_echo_server
	$(CC) $(CFLAGS) async_tcp_echo_server.cpp $(THREAD) $(BOOST) -o async_tcp_echo_server
clean:
	rm -rf *.o *~ blocking_tcp_echo_client blocking_tcp_echo_server async_tcp_echo_server
