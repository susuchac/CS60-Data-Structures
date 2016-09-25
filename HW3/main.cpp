#include <iostream>
#include <stdlib.h>
#include"Maze.h"
 
using namespace std;
 
int main(int argc, char* argv[])
{
      if(argc < 4)
      {
            cout << "Usage: Maze <height> <width> <seed>" << endl;
            return - 1;
      }
 
      int width, height, seed;
      height = atoi(argv[1]);
      width = atoi(argv[2]);
      seed = atoi(argv[3]);
 
      CMaze theMaze(height,width);
      //build the maze
      theMaze.MakeMaze(seed);
      //print it to cout
      theMaze.PrintMaze();
      //find the solution and print out the successful (shortest) path and maze with solution
      theMaze.SolveMaze();
 
 
      return 0;
}