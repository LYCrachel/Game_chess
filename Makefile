all: main

main: main.o Player.o Board.o 
	g++ -o main main.o Player.o Board.o 

main.o: main.cpp Player.h Board.h
	g++ -c -std=c++11 main.cpp

Board.o: Board.cpp Board.h
	g++ -c -std=c++11 Board.cpp

Player.o: Player.cpp Board.h Player.h
	g++ -c -std=c++11 Player.cpp

clean:
	rm -f *.o main
