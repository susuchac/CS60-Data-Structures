
//#pragma once
#include <list>

#define INFINITY 99999

using namespace std;

class CGraphNode
{
    public:
	CGraphNode();
	~CGraphNode(void);

	int id;
	long m_dist;
	bool m_known;
	int m_path;
};


typedef struct edge
{
    int endVert;
    int weight;
} EDGE;

class CGraph
{
    public:
	CGraph(int initSize);

	~CGraph(void);

	//adds an edge to the graph going from start to end and 
        //having weight "weight"
	void AddEdge(int start, int end, int weight);

	//return the length of a specified edge through the parameter length. 
	//returns false if there is no such edge, otherwise true
	bool GetEdgeLength(int start, int end, int * length);

	//calculates the weight of the shortest path between start and end
	int CalcShortestPath(int start, int end);
	list<int> ShortestPath(int start, int end);

    private:
	//runs Dijkstra's algorithm to calculate the shortest path
	void Dijkstras(int startVert);

	list <EDGE> * m_adjList;	

	//number of nodes in the graph
	int m_size;

	int m_lastDijkCall;

    public:
	CGraphNode * m_verts;
};
