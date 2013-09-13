CC = g++
CFLAGS = -Wall -Werror -g -pedantic -ansi -std=c++11
THREADS = -lpthread
GMP = -lgmpxx -lgmp

all: driver
	../build/driver
driver: PortfolioController.o Portfolio.o PortControl_Driver.o Database.o
	$(CC) $(CFLAGS) ../build/PortControl_Driver.o ../build/PortfolioController.o ../build/Portfolio.o ../build/Database.o $(THREADS) $(GMP) -o ../build/driver
PortControl_Driver.o:
	$(CC) $(CFLAGS) -c PortControl_Driver.cpp $(THREADS) $(GMP) -o ../build/PortControl_Driver.o
PortfolioController.o:
	$(CC) $(CFLAGS) -c ../src/PortfolioController.cpp $(THREADS) -o ../build/PortfolioController.o
Portfolio.o:
	$(CC) $(CFLAGS) -c ../../Portfolio/src/Portfolio.cpp $(THREADS) $(GMP) -o ../build/Portfolio.o
Database.o:
	$(CC) $(CFLAGS) -c ../../Database/src/Database.cpp $(THREADS) -o ../build/Database.o
clean:
	rm -rf ../build/* ../src/*~ *~
