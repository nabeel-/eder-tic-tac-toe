CXXFLAGS = -Wall -Werror 
main: tictactoe.o
	g++ tictactoe.o -o main
tictactoe.o: tictactoe.cc tictactoe.h 
	g++ $(CXXFLAGS) -c tictactoe.cc
clean:
	rm *.o main
