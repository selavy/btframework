CC = g++
CFLAGS = -Wall -Werror -pedantic -ansi -g -std=c++11
THREAD = -lpthread
BOOST = -lboost_system -lboost_thread

all: Module.o

Module.o:
	$(CC) $(CFLAGS) -c Module.cpp $(BOOST) $(THREAD) -o ../build/Module.o
clean:
	rm -rf *~ ../build/*
