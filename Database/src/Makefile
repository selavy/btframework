CC = g++
CFLAGS = -Wall -Werror -g -ansi -pedantic -std=c++11
all: Database.o

Database.o:
	$(CC) $(CFLAGS) -c Database.cpp -o ../build/Database.o
clean:	
	rm -rf *~ *.o ../build/*.o
