
#include "Graph.h"
#include <iterator>
#include <queue>
#include <vector>

using namespace std;

//***************************CGraphNode()****************************
/* Constructor for CGraphNode
**/
CGraphNode::CGraphNode()
{
}

//***************************~CGraphNode()***************************
/* Destructor for CGraphNode
**/
CGraphNode::~CGraphNode()
{
}

//***************************CGraph()********************************
/* Constructor for CGraph
 * Takes in input of initSize and initializes number of nodes in
 * graph, size of vertices list, and size of edges list.
**/
CGraph::CGraph(int initSize)
{
    m_size = initSize;
    m_adjList = new list<EDGE>[m_size]; // use new b/c of pointer
    m_verts = new CGraphNode[m_size];
    m_lastDijkCall = -1; // Dijkstras not called yet
}

//**************************~CGraph()********************************
/* Destructor for CGraph
 * Deletes vertices list and edges list b/c created with 'new'
**/
CGraph::~CGraph()
{
    delete m_adjList;
    delete m_verts;
}

//**************************AddEdge()********************************
/* Adds an edge to the graph given input of start vertex, end
 * vertex, and weight of the edge
**/
void CGraph::AddEdge(int start, int end, int weight)
{
    edge e;
    e.endVert = end;
    e.weight = weight;
    m_adjList[start].push_back(e);
}

//*************************GetEdgeLength()***************************
/* Takes in input start vertex, end vertex, and edge length.
 * Checks if edge exists (returns false if it doesn't).
 * Else iterates through edge list, searching for correct edge
 * and changes value of input pointer length if found.
**/
bool CGraph::GetEdgeLength(int start, int end, int *length)
{	
    if(m_adjList[start].size() == 0)
    {
        return false;
    }

    list<EDGE>::iterator it = m_adjList[start].begin();

    while(it != m_adjList[start].end())
    {
        edge e = *it;
	if(e.endVert == end)
	{
	    length = &e.weight;
	}
	else
	{
	    advance(it, 1);
	}
    }
    return true;
}

//**************************CalcShortestPath()***********************
/* Calls Dijkstras on start vertex, and returns the shortest
 * distance to arrive at the end vertex.
**/
int CGraph::CalcShortestPath(int start, int end)
{
    if(m_lastDijkCall != start)
    {
        Dijkstras(start);
        m_lastDijkCall = start;
    }
    return m_verts[end].m_dist;
}

//**************************ShortestPath()***************************
/* Returns a list containing the shortest path to arrive at end 
 * vertex from start vertex.
**/
list<int> CGraph::ShortestPath(int start, int end)
{
    list <int> path;
		
    int cur_node = end;
    path.push_front(end);
    while(cur_node != start)
    {
        path.push_front(m_verts[cur_node].m_path);
	cur_node = m_verts[cur_node].m_path;
    }
    return path;
}

// comparator for two graph nodes
struct comparator {
    bool operator() (CGraphNode a, CGraphNode b) 
    {
	return a.m_dist > b.m_dist;
    }
};

//**************************Dijkstras()******************************
/* Finds the shortest path to all vertices in graph.
**/
void CGraph::Dijkstras(int startVert)
{
    // re-initailize vertex variables each time Dijkstras is called
    for(int i = 0; i < m_size; i++)
    {
	m_verts[i].id = i;
	m_verts[i].m_dist = INFINITY;
	m_verts[i].m_known = false;
    }

    // priority queue to store min heap of nodes. shortest dist @ top
    priority_queue<CGraphNode, std::vector<CGraphNode>, 
        comparator> min_heap;
  
    // start vertex distance from start is 0
    m_verts[startVert].m_dist = 0;
	
    min_heap.push(m_verts[startVert]);

    while(!min_heap.empty())
    {
        CGraphNode v = min_heap.top(); // smallest vertex
        min_heap.pop(); // deleteMin
	
        // if shortest path to vertex is unknown
        if(!v.m_known)
	{
	    for(list<EDGE>::const_iterator it = m_adjList[v.id].
                begin(); it != m_adjList[v.id].end(); ++it) 
	    {
                // if shortest path to endVert is unknown
                if(!m_verts[(*it).endVert].m_known)
                {			
                    // if new path to endVert shorter than cur path
		    if(v.m_dist + (*it).weight < 
                        m_verts[(*it).endVert].m_dist)    
                    {	
                        // update path and dist of endVert
                        m_verts[(*it).endVert].m_path = v.id;
    			m_verts[(*it).endVert].m_dist = v.m_dist 
                            + (*it).weight;
                        min_heap.push(m_verts[(*it).endVert]);
                    }	
                }
	    }
	}
    }
}
