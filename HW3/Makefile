maze.exe: main.o Maze.o
	g++ -o maze main.o Maze.o

main.o: main.cpp Maze.h
	g++ -c main.cpp

Maze.o: Maze.cpp Maze.h
	g++ -c Maze.cpp

clean: 
	rm *.o *.out *.stackdump
