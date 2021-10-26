BIN = main
TARGETS =  main_sequence.o

CC = g++
FLAGS = -Wall -g

all : $(BIN)

$(BIN) : $(TARGETS)
	$(CC) $(TARGETS) -o $(BIN) $(FLAGS)

main_sequence.o : main_sequence.cpp sequence.hpp
	$(CC) -c main_sequence.cpp $(FLAGS)

clean :
	rm $(BIN) *.o vgcore.*
