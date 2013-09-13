CC = g++
CFLAGS = -Wall -Werror -g -pedantic -ansi -std=c++11
all: driver
	../build/driver
driver: Portfolio.o Portfolio_Driver.o Database.o
	$(CC) $(CFLAGS) ../build/Portfolio.o ../build/Portfolio_Driver.o ../build/Database.o -o ../build/driver
Portfolio_Driver.o: Portfolio.o
	$(CC) $(CFLAGS) -c Portfolio_Driver.cpp -o ../build/Portfolio_Driver.o
Portfolio.o: Database.o
	$(CC) $(CFLAGS) -c ../src/Portfolio.cpp -o ../build/Portfolio.o
Database.o:
	$(CC) $(CFLAGS) -c ../../Database/src/Database.cpp -o ../build/Database.o
clean:
	rm -rf *~ ../build/* ../src/*~
