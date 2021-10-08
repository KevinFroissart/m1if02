output: Cellule.o
	g++ Cellule.o -o Cellule

Cellule.o: Cellule.cpp
	g++ -c Cellule.cpp

all:
	g++ -Wall -Wextra -std=c++11 -o exec *.cpp

clear:
	rm -f *.o
	rm -r exec