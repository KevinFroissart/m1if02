all: main.exe

main.exe: main.cpp SequenceCirculaire.hpp
	g++ -g main.cpp -Wall -std=c++14 -o main.exe

run: main.exe
	main.exe

valgrind: main.exe
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./main.exe

clean:
	del *.exe
