#ifndef FLIGHT_MANAGER_H
#define FLIGHT_MANAGER_H

#include "Flight.h"
#include "City.h"
#include "DynamicArray.h"
#include <string>
using namespace std;

class FlightManager
{
private:
DynamicArray<Flight> allFlights;
DynamicArray<City> allCities;

public:
    // Constructor
    FlightManager();

    // Load data from files
    void loadFlightsFromFile(string filename);
    void loadCitiesFromFile(string filename);

    // Getters
    DynamicArray<Flight>& getAllFlights();
    DynamicArray<City>& getAllCities();
    int getTotalFlights() const;
    int getTotalCities() const;

    // Display functions
    void displayAllFlights() const;
    void displayAllCities() const;

    // Search functions
    DynamicArray<Flight> getFlightsByOriginAndDestination(string origin, string destination);
    DynamicArray<Flight> getFlightsByOriginDestinationAndDate(string origin, string destination, string date);
    DynamicArray<Flight> getFlightsByAirline(string airline);
};

#endif
