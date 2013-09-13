CC = g++
CFLAGS = -Wall -Werror -pedantic -ansi -g -std=c++11

all: driver
	./driver
driver: Controller_Driver.o Controller.o
	$(CC) $(CFLAGS) Controller_Driver.o Controller.o -o driver
Controller_Driver.o:
	$(CC) $(CFLAGS) -c Controller_Driver.cpp -o Controller_Driver.o
Controller.o:
	$(CC) $(CFLAGS) -c ../src/Controller.cpp -o Controller.cpp -o Controller.o
clean:
	rm -rf *.o *~ driver
