// Programmer: Susie Chac
// Course: ECS 60
// Date: 08/26/2016
// Objective: Header file for maze.cpp

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class CMaze
{
  public:
    CMaze(int numRows, int numColumns);
    ~CMaze(void);
    void MakeMaze(int seed);
    void PrintMaze();
    void SolveMaze();
    vector<string> GetGrid();
    int GetNumRoots();
    void MakeMazeHelper();
    int GetSqr2(int sqr1);
    int GetInBtw(int sqr1, int sqr2);
    
    struct Node
    {
        vector<int> path;
        int cur_pos;
    };
    
    int CheckOpenPath(Node *n, Node *nxt, queue<Node> &q);

  private:
    //disjoint set methods
    void Union(int item1, int item2);
    int Find(int itemIndex);
    
    int height;
    int width;
    int maxVal;

    vector<int> keys;
    vector<int> soln;
    vector<string> maze;
};
