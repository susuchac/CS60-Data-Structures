
#include "Dispatcher.h"
#include "Graph.h"
#include <sstream>
#include <iostream>
#include <vector>
// #define NDEBUG
#include <cassert>

using namespace std;

//**************************CDispatcher()****************************
/* Constructor for CDispatcher
**/
CDispatcher::CDispatcher()
{
}

//**************************~CDispatcher()***************************
/* Destructor for CDispatcher
**/
CDispatcher::~CDispatcher()
{
}

//**************************UpdateTaxis()****************************
/* Increment positions of taxis that currently have customers
**/
void CDispatcher::UpdateTaxis(int dt)
{
    for(int i = 0; i < NUM_TAXIS; i++)
    {
        if(!m_taxis[i].IsAvailable())
        {
            m_taxis[i].MoveTimeStep(dt, m_roadMap, i);
        }
    }
}

//**************************ProcessCall()****************************
/* Processes customer's call.
 * Dispatch sends the taxi closest to the customer.
**/
void CDispatcher::ProcessCall(string buf)
{
    istringstream strBuf(buf);

    char command;
    strBuf >> command;

    int client_loc, client_dest;
    strBuf >> client_loc;
    strBuf >> client_dest;

    // list of available taxis
    vector<int> avail_taxis;
    for(int i = 0; i < NUM_TAXIS; i++)
    {
        if(m_taxis[i].IsAvailable())
        {
            avail_taxis.push_back(i);
        }
    }
    // use taxi RED for first distance to compare
    int shortest_dist = m_roadMap->CalcShortestPath(m_taxis[RED].
        GetLocation(), client_loc);
    int closest_taxi = RED;
    for(int i = 1; i < avail_taxis.size(); i++)
    {
        // compare distances to customer
        if(m_roadMap->CalcShortestPath(m_taxis[i].GetLocation(), 
              client_loc) < shortest_dist)
        {
            // update closest taxi
            shortest_dist = m_roadMap->CalcShortestPath(
                m_taxis[i].GetLocation(), client_loc);
            closest_taxi = i;
        }
    }
    // update taxi route, dropoff point, and availability status
    m_taxis[closest_taxi].SetRoute(m_roadMap, client_loc);
    m_taxis[closest_taxi].SetDropoff(client_dest);
    m_taxis[closest_taxi].SetAvailable(false);
    
    // set taxi loc to client loc even tho not taxi not already at loc
    m_taxis[closest_taxi].SetLocation(client_loc);
    cout << "Dispatching taxi " << m_taxis[closest_taxi].
        GetTaxiName(closest_taxi) << " to location " << client_loc
        << " with destination " << client_dest << endl;
    
    // print out taxi route
    m_taxis[closest_taxi].PrintRoute();
}

//**************************SetMap()*********************************
/* Builds a map given a string of vertices and weights.
**/
void CDispatcher::SetMap(string buf)
{
    istringstream strBuf(buf);

    char command;
    strBuf >> command;

    int numVerts, vert1, vert2, weight;
    strBuf >> numVerts;

    m_roadMap = new CGraph(numVerts);

    while(!strBuf.eof())
    {
        strBuf >> vert1;
	strBuf >> vert2;
	strBuf >> weight;

	m_roadMap->AddEdge(vert1, vert2, weight);
    }
}

//**************************SetTaxiLocations()***********************
/* Sets taxi locations given a string of commands and locations.
**/
void CDispatcher::SetTaxiLocations(string buf)
{
    istringstream strBuf(buf);
 
    //dump command from buffer
    char command, taxi;
    strBuf >> command;

    int location;

    //position all the taxis
    while(!strBuf.eof())
    {
        strBuf >> taxi;
        strBuf >> location;
        int index;
 
        switch (taxi)
        {
            case 'R':
                index = RED;
                break;
            case 'G':
                index = GREEN;
                break;
            case 'B':
                index = BLUE;
                break;
            case 'Y':
                index = YELLOW;
                break;
            case 'P':
                index = PINK;
                break;
            default:
                assert(false);
        }
        m_taxis[index].SetLocation(location);
    }
}
