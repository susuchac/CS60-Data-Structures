// Programmers: Susie Chac & Jonathan Hoeck

#include "Graph.h"
#include "Taxi.h"
#include <iostream>

using namespace std;

//**************************CTaxi()**********************************
/* Constructor for CTaxi.
**/
CTaxi::CTaxi()
{
    m_bAvailable = true; // taxi is initially available
}

//**************************~CTaxi()*********************************
/* Destructor for CTaxi
**/
CTaxi::~CTaxi()
{
}

//**************************SetLocation()****************************
/* Sets location of taxi to input location v
**/
void CTaxi::SetLocation(int v)
{
    m_location = v;
}

//**************************GetLocation()****************************
/* Returns location of taxi
**/
int CTaxi::GetLocation()
{
    return m_location;
}

//**************************IsAvailable()****************************
/* Returns availability status of taxi
**/
bool CTaxi::IsAvailable()
{
    return m_bAvailable;
}

//**************************SetAvailable()***************************
/* Sets availabiliy of taxi to input true/false
**/
void CTaxi::SetAvailable(bool b)
{
    m_bAvailable = b;
}

//**************************SetDropoff()*****************************
/* Sets dropoff location for customer given input location d
**/
void CTaxi::SetDropoff(int d)
{
    m_dropoff = d;
}

//**************************SetRoute()*******************************
/* Sets taxi route to shortest path to input destination.
 * Two possible routes:
 *      1. Pick up customer
 *      2. Drop off customer
**/
void CTaxi::SetRoute(CGraph *graph, int dest)
{
    // resets distance left on route to new route distance
    m_distLeftOnRoute = graph->CalcShortestPath(m_location, dest);
    m_route = graph->ShortestPath(m_location, dest);

}

//**************************PrintRoute()*****************************
/* Prints route by iterating through list of route vertices
**/
void CTaxi::PrintRoute()
{
    cout << "Planned route: ";
    for (list<int>::const_iterator it = m_route.begin(); 
        it != m_route.end(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;
}

//**************************GetTaxiName()****************************
/* Takes in input taxiIndex and returns taxi name
**/
string CTaxi::GetTaxiName(int taxiIndex)
{
    switch(taxiIndex)
    {
        case 0:
            return "RED";
            break;
        case 1:
            return "GREEN";
            break;
        case 2:
            return "BLUE";
            break;
        case 3:
            return "YELLOW";
            break;
        case 4:
            return "PINK";
            break;
    }
}

//**************************MoveTimeStep()***************************
/* Decrements distance left on route each time function is called.
 * Checks if distance left is 0, then two possibilities:
 *          1. Taxi has arrived at customer pickup location
 *          2. Taxi has arrived at customer dropoff location
**/
void CTaxi::MoveTimeStep(int dt, CGraph *graph, int taxiIndex)
{
    m_distLeftOnRoute -= dt;
    // if arrived at destination
    if(m_distLeftOnRoute == 0)
    {
        if(m_location == m_dropoff)
        {
            cout << "Taxi " << GetTaxiName(taxiIndex) << 
                " dropping off passenger at " << m_location 
                << "." << endl;
            // taxi is available after dropping off customer
            SetAvailable(true);
        }
        else
        {
            cout << "Taxi " << GetTaxiName(taxiIndex) << 
                " picking passenger up at " << m_location 
                << "." << endl;
            // get shortest path to dropoff location
            SetRoute(graph, m_dropoff);
            // set location to dropoff
            SetLocation(m_dropoff);
            PrintRoute();
        }
    }
}
