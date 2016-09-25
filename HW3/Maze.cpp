// Programmer: Susie Chac 
// Course: ECS 60
// Date: 08/26/2016
// Objective: This program builds a maze given command line
//            arguments of height, width, and a seed that is
//            used to generate random numbers.
//            This program can also solve the maze once it
//            has been created. Only one solution possible.

#include "Maze.h"
#include <cstdlib>
#include <time.h>

using namespace std;

//********************CMaze()********************************
/* Accepts input num rows and num cols
 * and sets as size of vector keys.
 * Each item in keys starts in own equiv class,
 * so set value equal to -1 to indicate root.
**/
CMaze::CMaze(int numRows, int numColumns)
{
    height = numRows;
    width = numColumns;
    keys = vector<int>(numRows*numColumns);

    for(int i = 0; i < keys.size(); i++)
    {
        keys[i] = -1;
    }
}

//********************~CMaze()*******************************
/* Empty destructor for CMaze
**/
CMaze::~CMaze(void) {

}

//********************GetGrid()******************************
/* Creates and returns a vector of strings storing grid.
 * Each row in vector is a string of characters.
 * Each string of characters is an array of characters.
 * Can use vector as a 2D-array.
**/
vector<string> CMaze::GetGrid()
{
    vector<string> grid;

    for (int i = 0; i < this->height * 2 + 1; ++i) {
        string single_row;
        for (int j = 0; j < this->width * 2 + 1; ++j) { 
         
            if (i % 2 == 0 && j % 2 == 0) { 
                single_row += "+";
            }
            else if (i % 2 == 0 && j % 2 != 0) {
                single_row += "-";
            }
            else if (i % 2 != 0 && j % 2 == 0) {
                single_row += "|";
            } else {
                single_row += " ";
            }
        }
        grid.push_back(single_row);
    }

    return grid;
}

//********************MakeMaze()*****************************
/* Accepts input of a seed to create random variables.
 * Sets global variable maze equal to grid.
 * Removes walls to make entrance and exit.
 * Uses helper function GetNumRoots() to check if all 
 * squares in maze are in the same equivalence class.
 * If not, uses MakeMazeHelper() to remove walls until
 * condition is satiasfied.
**/
void CMaze::MakeMaze(int seed)
{
    maze = GetGrid();

    // make entrance and exit
    maze[0][1] = ' ';
    maze[1][0] = ' ';
    maze[(height*2)-1][width*2] = ' ';
    maze[height*2][(width*2)-1] = ' ';

    srand(seed);

    // while not every sqr in maze is in same EC
    while(GetNumRoots() != 1)
    {
        // remove walls
        MakeMazeHelper();
    }
}

//********************MakeMazeHelper()***********************
/* Takes a random square sqr1 and uses helper function
 * GetSqr2() to get a random adjacent square sqr2.
 * Then checks if the two squares are in the same EC.
 * If they're not, the wall between the two squares is
 * removed, and Union() is used to put them into the
 * same equivalence class.
**/
void CMaze::MakeMazeHelper()
{
    maxVal = (width*height) - 1;

    long int sqr1 = (int) (maxVal * (rand() 
        / (float)(RAND_MAX + 1.0)));

    int sqr1_row = (sqr1 / width) * 2 + 1;
    int sqr1_col = (sqr1 % width) * 2 + 1;

    int sqr2 = GetSqr2(sqr1);

    int sqr2_row = (sqr2 / width) * 2 + 1;
    int sqr2_col = (sqr2 % width) * 2 + 1;

    int row_to_rm = GetInBtw(sqr1_row, sqr2_row);
    int col_to_rm = GetInBtw(sqr1_col, sqr2_col);

    // if sqrs are NOT in same equivalence class
    if(Find(sqr1) != Find(sqr2))
    {
        // change wall to empty space
        maze[row_to_rm][col_to_rm] = ' ';

        // check the size of each disjoint set
        if(keys[Find(sqr1)] < keys[Find(sqr2)])
        {
            // make sqr1 parent of sqr2
            Union(Find(sqr1), Find(sqr2));
        }
        else
        {
            // make sqr2 parent of sqr1
            Union(Find(sqr2), Find(sqr1));
        }
    }
}

//********************GetSqr2()******************************
/* Returns a random adjacent square to input sqr1.
**/
int CMaze::GetSqr2(int sqr1)
{
    int sqr2;
    bool flag = false;
    while(flag != true)
    {
        int adj_sqr = rand() % 4;
        switch(adj_sqr)
        {
            case 0: 
            {
                if(!(sqr1 - width < 0))
                {
                    // if above sqr not null
                    sqr2 = sqr1 - width; 
                    flag = true;
                }
                break; 
            }
            case 1:
            {
                if(!((sqr1 + 1) % width == 0))
                {
                    // if right sqr not null
                    sqr2 = sqr1 + 1; 
                    flag = true;  
                }
                break;
            }
            case 2: 
            {
                if(!(sqr1 + width > maxVal))
                {
                    // if below sqr not null
                    sqr2 = sqr1 + width; 
                    flag = true;
                }
                break;
            }
            case 3:
            {
                if(!(sqr1 % width == 0))
                {
                    // if left sqr not null
                    sqr2 = sqr1 - 1; 
                    flag = true;
                }
                break;
            }
            default:
                sqr2 = -1; break;
        }
    }
    return sqr2;
}

//********************GetInBtw()*****************************
/* Accepts input of either rows or cols of sqr1 and sqr2,
 * and returns row or col inbetween the inputs.
**/
int CMaze::GetInBtw(int sqr1, int sqr2)
{
    return (sqr2 + sqr1)/2;
}

//********************GetNumRoots()**************************
/* Returns the number of root nodes in the grid,
 * which indicates whether or not all of the squares
 * are in the same equivalence class.
**/
int CMaze::GetNumRoots()
{
    int root_count = 0;
    for(int i = 0; i < keys.size(); i++)
    {
        // if value is negative (roots are negative)
        if(keys[i] < 0)
        {
            root_count++;
         }
    }
    return root_count;
}

//********************PrintMaze()****************************
/* Prints out the maze
**/
void CMaze::PrintMaze()
{   
    for(int i = 0; i < maze.size(); i++)
    {
        cout <<  maze[i] << endl;
    }
}

//********************SolveMaze()****************************
/* Prints out maze solution and solved maze. 
 * Solution path is depicted with 'O'.
 * Only one solution possible.
 * When solving maze, only visits each position once
 * for maximum efficieny.
 * Uses helper function CheckOpenPath() to see if a 
 * wall exists between two positions in maze.
**/
void CMaze::SolveMaze()
{   
    // print 2 empty lines before solving maze
    cout << "\n" << endl;

    queue<Node> q;
    vector<int> visited = vector<int>(width*height);
    Node n;
    n.cur_pos = 0; // start pos
    n.path.push_back(n.cur_pos);
    // push first position into queue
    q.push(n);

    while(!q.empty())
    {
        Node nxt;
        n = q.front();
        q.pop();
        // checks if current pos is last pos in maze
        if(n.cur_pos == maxVal)
        {
            // sets soln equal to path taken to reach end
            soln = n.path;
            for (int i  = 0; i < soln.size(); ++i) 
            {
                int row = (soln[i] / width) * 2 + 1;
                int col = (soln[i] % width) * 2 + 1;
                maze[row][col] = 'O';
                // prints out solution positions
                cout << soln[i] << " " ;
            }
            break;
        }
        else
        {
                // check up
                if(!(n.cur_pos - width < 0))
                {   
                    // update next position
                    nxt.cur_pos = n.cur_pos - width;
                    // check if next pos visited yet b/c
                    // don't want to visit same pos twice
                    if (!visited[nxt.cur_pos]) {
                        // check if wall exists between 
                        // next and current position
                        CheckOpenPath(&n, &nxt, q);
                    }
                }

                // check right
                if(!((n.cur_pos + 1) % width == 0))
                {
                    nxt.cur_pos = n.cur_pos + 1;
                    if (!visited[nxt.cur_pos]) {
                        CheckOpenPath(&n, &nxt, q);
                    }
                }

                // check down
                if(!(n.cur_pos + width > maxVal))
                {
                    nxt.cur_pos = n.cur_pos + width;
                    if (!visited[nxt.cur_pos]) {
                        CheckOpenPath(&n, &nxt, q);
                    }
                }

                // check left
                if(!(n.cur_pos % width == 0))
                {
                    nxt.cur_pos = n.cur_pos - 1;
                    if (!visited[nxt.cur_pos]) {
                        CheckOpenPath(&n, &nxt, q);
                    }
                }
        }
        // update current position to visited
        visited[n.cur_pos] = 1;
    }

    cout << "\n" << endl;

    PrintMaze();
}

//********************Union()********************************
/* Accepts input of two root nodes, item1 and item2,
 * and puts them into the same equivalence class.
 * item1 size updated to (current item1 size + item2 size)
 * The parent of item2 becomes item1.
**/
void CMaze::Union(int item1, int item2)
{
    // item1 and item2 are roots (negative values)
    // update size of item1
    keys[item1] = keys[item1] + (keys[item2]);

    // make item1 parent of item2
    keys[item2] = item1;
}

//********************Find()*********************************
/* Accepts input itemIndex and returns the index of the
 * set that it belongs to, by using recursion.
**/
int CMaze::Find(int itemIndex)
{
    // returns set itemIndex belongs in
    if(keys[itemIndex] < 0)
    {
        // if itemIndex is root node
        return itemIndex;
    }
    else
    {
        // find set that parent of itemIndex belongs to
        return Find(keys[itemIndex]);
    }
}

//********************CheckOpenPath()************************
/* Accepts input of current and next node, 
 * and a queue containing nodes to be checked 
 * if they lead to valid paths.
 * Checks if a wall exists between the two input nodes,
 * and updates the path if there is no wall in between them.
**/
int CMaze::CheckOpenPath(Node* n, Node* nxt, queue<Node> &q)
{
    // get row of position between the two nodes
    int row = GetInBtw((n->cur_pos / width) * 2 + 1,
        (nxt->cur_pos / width) * 2 + 1);
    // get col of position between the two nodes
    int col = GetInBtw((n->cur_pos % width) * 2 + 1,
        (nxt->cur_pos % width) * 2 + 1);

    // if no wall exists at position between the two nodes
    if(maze[row][col] == ' ')
    {
        // update path and add current position
        nxt->path = n->path;
        nxt->path.push_back(nxt->cur_pos);
        q.push(*nxt);
        
        return 1; // exit success
    }
}
