CC = g++
CFLAGS = -Wall -Werror -g -pedantic -ansi -std=c++11

all: driver
	../build/driver
driver: PortfolioController.o Portfolio.o PortControl_Driver.o Database.o
	$(CC) $(CFLAGS) ../build/PortControl_Driver.o ../build/PortfolioController.o ../build/Portfolio.o ../build/Database.o -o ../build/driver
PortControl_Driver.o:
	$(CC) $(CFLAGS) -c PortControl_Driver.cpp -o ../build/PortControl_Driver.o
PortfolioController.o:
	$(CC) $(CFLAGS) -c ../src/PortfolioController.cpp -o ../build/PortfolioController.o
Portfolio.o:
	$(CC) $(CFLAGS) -c ../../Portfolio/src/Portfolio.cpp -o ../build/Portfolio.o
Database.o:
	$(CC) $(CFLAGS) -c ../../Database/src/Database.cpp -o ../build/Database.o
clean:
	rm -rf ../build/* ../src/*~ *~
