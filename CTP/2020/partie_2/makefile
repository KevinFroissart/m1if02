BIN = main
TARGETS =  main_circulateur.o

CC = g++
FLAGS = -Wall -g

all : $(BIN)

$(BIN) : $(TARGETS)
	$(CC) $(TARGETS) -o $(BIN) $(FLAGS)

main_circulateur.o : main_circulateur.cpp circulateur.hpp
	$(CC) -c main_circulateur.cpp $(FLAGS)

clean :
	rm $(BIN) *.o vgcore.*
