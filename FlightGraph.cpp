#include "pch.h"
#include "FlightGraph.h"
#include "Utility.h"
#include <iostream>
using namespace std;

FlightGraph::FlightGraph()
{
    cities.clear();
    allEdges.clear();
}

void FlightGraph::addCity(string cityName, double hotelCharge)
{
    cityName = Utility::normalizeCityName(cityName);
    if (cities.find(cityName) == cities.end())
    {
        GraphNode node(cityName, hotelCharge);
        cities[cityName] = node;
    }
}

void FlightGraph::addFlight(Flight flight)
{
    string origin = Utility::normalizeCityName(flight.getOrigin());
    string destination = Utility::normalizeCityName(flight.getDestination());
    flight.setOrigin(origin);
    flight.setDestination(destination);
    
    // Add cities if they don't exist
    if (cities.find(origin) == cities.end())
    {
        addCity(origin, 0.0);
    }
    if (cities.find(destination) == cities.end())
    {
        addCity(destination, 0.0);
    }
    
    // Add flight to outgoing flights of origin city
    cities[origin].addOutgoingFlight(flight);
    
    // Store in allEdges
    allEdges.push_back(flight);
}

bool FlightGraph::isCityExists(string cityName) const
{
    cityName = Utility::normalizeCityName(cityName);
    return cities.find(cityName) != cities.end();
}

GraphNode* FlightGraph::getCity(string cityName)
{
    cityName = Utility::normalizeCityName(cityName);
    if (cities.find(cityName) != cities.end())
    {
        return &cities[cityName];
    }
    return nullptr;
}

map<string, GraphNode>& FlightGraph::getAllCities()
{
    return cities;
}

DynamicArray<Flight>& FlightGraph::getAllFlights()
{
    return allEdges;
}

int FlightGraph::getCityCount() const
{
    return cities.size();
}

int FlightGraph::getFlightCount() const
{
    return allEdges.getSize();
}

DynamicArray<Flight> FlightGraph::getDirectFlights(string origin, string destination)
{
    DynamicArray<Flight> result;

    origin = Utility::normalizeCityName(origin);
    destination = Utility::normalizeCityName(destination);

    if (cities.find(origin) == cities.end())
    {
        return result;
    }
    
    return cities.at(origin).getFlightsTo(destination);
}

DynamicArray<Flight> FlightGraph::getDirectFlightsOnDate(string origin, string destination, string date)
{
    DynamicArray<Flight> result;
    DynamicArray<Flight> directFlights = getDirectFlights(origin, destination);
    
    for (int i = 0; i < directFlights.getSize(); i++)
    {
        if (directFlights[i].getDate() == date)
        {
            result.push_back(directFlights[i]);
        }
    }
    
    return result;
}

DynamicArray<Flight> FlightGraph::getFlightsByAirline(string airline)
{
    DynamicArray<Flight> result;
    
    for (int i = 0; i < allEdges.getSize(); i++)
    {
        if (allEdges[i].getAirlineName() == airline)
        {
            result.push_back(allEdges[i]);
        }
    }
    
    return result;
}

void FlightGraph::displayGraph() const
{
    cout << "\n===== FLIGHT GRAPH =====" << endl;
    cout << "Total Cities: " << cities.size() << endl;
    cout << "Total Flights: " << allEdges.getSize() << endl;
    
    for (auto it = cities.begin(); it != cities.end(); it++)
    {
        cout << "\nCity: " << it->first << endl;
        cout << "Hotel Charge: " << it->second.getHotelChargePerDay() << endl;
        cout << "Outgoing Flights: " << it->second.getOutgoingFlights().getSize() << endl;
        
        const DynamicArray<Flight>& flights = it->second.getOutgoingFlights();
        for (int i = 0; i < flights.getSize(); i++)
        {
            cout << "  - ";
            flights[i].display();
        }
    }
}

void FlightGraph::displayCityConnections(string cityName) const
{
    if (cities.find(cityName) == cities.end())
    {
        cout << "City " << cityName << " not found in graph." << endl;
        return;
    }
    
    cout << "\n===== CONNECTIONS FOR " << cityName << " =====" << endl;
    
    auto it = cities.find(cityName);
    const DynamicArray<Flight>& flights = it->second.getOutgoingFlights();
    
    for (int i = 0; i < flights.getSize(); i++)
    {
        cout << i + 1 << ". ";
        flights[i].display();
    }
}
