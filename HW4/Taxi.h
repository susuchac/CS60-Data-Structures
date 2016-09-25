// Programmers: Susie Chac & Jonathan Hoeck

//#pragma once

#include <list>
#include <string>

class CGraph;

class CTaxi
{
    public:
	CTaxi(void);
	~CTaxi(void);

	//access functions
	void SetLocation(int v);
	int GetLocation();
	bool IsAvailable();
	void SetAvailable(bool b);

	void SetDropoff(int d);

	//causes the taxi to calculate (and store) its route
	void SetRoute(CGraph * graph, int dest);
	void PrintRoute();

	//update the position of the taxi
	void MoveTimeStep(int dt, CGraph * graph, int taxiIndex);

        std::string GetTaxiName(int taxiIndex);

    private:
	//current location
	int m_location;

	//true if the taxi does not have a passenger
	bool m_bAvailable;

	//must save this to calculate the route from the pickup 
        //to the drop off
	int m_dropoff;

	//route to take to destination
	//Note, there will be two routes, one on the way to pick up 
        //a passenger and one to take the passenger to his destination
        std::list <int> m_route;
	int m_distLeftOnRoute;

};
