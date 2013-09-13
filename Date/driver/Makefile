CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic -g -std=c++11

all: driver
	../build/driver
driver: Date_Driver.o Date.o
	$(CC) $(CFLAGS) ../build/DateException.o ../build/Date.o ../build/Date_Driver.o -o ../build/driver
Date_Driver.o:
	$(CC) $(CFLAGS) -c Date_Driver.cpp -o ../build/Date_Driver.o
Date.o: DateException.o
	$(CC) $(CFLAGS) -c ../src/Date.cpp -o ../build/Date.o
DateException.o:
	$(CC) $(CFLAGS) -c ../src/DateException.cpp -o ../build/DateException.o
clean:
	rm -rf *.o *~ ../build/* ../src/*~
