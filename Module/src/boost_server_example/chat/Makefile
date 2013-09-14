CC = g++
CFLAGS = -Wall -Werror -pedantic -ansi -std=c++11 -g
THREAD = -lpthread
BOOST = -lboost_system -lboost_thread

all:
	$(CC) $(CFLAGS) chat_message.hpp chat_client.cpp $(BOOST) $(THREAD) -o chat_client
	$(CC) $(CFLAGS) chat_message.hpp chat_server.cpp $(BOOST) $(THREAD) -o chat_server
clean:
	rm -rf *.o *~ chat
