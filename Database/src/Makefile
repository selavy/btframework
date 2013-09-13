CC = g++
CFLAGS = -Wall -Werror -g -ansi -pedantic -std=c++11
THREADS = -lpthread
all: Database.o

Database.o:
	$(CC) $(CFLAGS) -c Database.cpp $(THREADS) -o ../build/Database.o
clean:	
	rm -rf *~ *.o ../build/*.o
