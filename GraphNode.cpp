#include "pch.h"
#include "GraphNode.h"
#include <iostream>
using namespace std;

GraphNode::GraphNode()
{
    cityName = "";
    hotelChargePerDay = 0.0;
    outgoingFlights.clear();
}

GraphNode::GraphNode(string name, double hotelCharge)
{
    cityName = name;
    hotelChargePerDay = hotelCharge;
    outgoingFlights.clear();
}

string GraphNode::getCityName() const
{
    return cityName;
}

double GraphNode::getHotelChargePerDay() const
{
    return hotelChargePerDay;
}

DynamicArray<Flight>& GraphNode::getOutgoingFlights()
{
    return outgoingFlights;
}

const DynamicArray<Flight>& GraphNode::getOutgoingFlights() const
{
    return outgoingFlights;
}

void GraphNode::setCityName(string name)
{
    cityName = name;
}

void GraphNode::setHotelChargePerDay(double charge)
{
    hotelChargePerDay = charge;
}

void GraphNode::addOutgoingFlight(Flight flight)
{
    outgoingFlights.push_back(flight);
}

DynamicArray<Flight> GraphNode::getFlightsTo(string destination)
{
    DynamicArray<Flight> result;
    
    for (int i = 0; i < outgoingFlights.getSize(); i++)
    {
        if (outgoingFlights[i].getDestination() == destination)
        {
            result.push_back(outgoingFlights[i]);
        }
    }
    
    return result;
}

void GraphNode::display() const
{
    cout << "City: " << cityName << " | Hotel Charge: " << hotelChargePerDay << endl;
    cout << "Outgoing Flights: " << outgoingFlights.getSize() << endl;
}
