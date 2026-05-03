#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include "Flight.h"
#include "DynamicArray.h"
#include <string>
using namespace std;

class GraphNode
{
private:
string cityName;
double hotelChargePerDay;
DynamicArray<Flight> outgoingFlights;

public:
    // Constructor
    GraphNode();
    GraphNode(string name, double hotelCharge);

    // Getters
    string getCityName() const;
    double getHotelChargePerDay() const;
    DynamicArray<Flight>& getOutgoingFlights();
    const DynamicArray<Flight>& getOutgoingFlights() const;

    // Setters
    void setCityName(string name);
    void setHotelChargePerDay(double charge);

    // Flight management
    void addOutgoingFlight(Flight flight);
    DynamicArray<Flight> getFlightsTo(string destination);
    
    // Display
    void display() const;
};

#endif
