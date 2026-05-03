#ifndef FLIGHT_GRAPH_H
#define FLIGHT_GRAPH_H

#include "GraphNode.h"
#include "DynamicArray.h"
#include <map>
#include <string>
using namespace std;

class FlightGraph
{
private:
map<string, GraphNode> cities;
DynamicArray<Flight> allEdges;

public:
    // Constructor
    FlightGraph();

    // Graph building
    void addCity(string cityName, double hotelCharge);
    void addFlight(Flight flight);
    
    // Getters
    bool isCityExists(string cityName) const;
    GraphNode* getCity(string cityName);
    map<string, GraphNode>& getAllCities();
    DynamicArray<Flight>& getAllFlights();
    int getCityCount() const;
    int getFlightCount() const;

    // Search functions
    DynamicArray<Flight> getDirectFlights(string origin, string destination);
    DynamicArray<Flight> getDirectFlightsOnDate(string origin, string destination, string date);
    DynamicArray<Flight> getFlightsByAirline(string airline);
    
    // Display
    void displayGraph() const;
    void displayCityConnections(string cityName) const;
};

#endif
