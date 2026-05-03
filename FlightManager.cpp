#include "pch.h"
#include "FlightManager.h"
#include "Utility.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

namespace
{
    bool isDuplicateCity(const DynamicArray<City>& cities, const string& cityName)
    {
        for (int i = 0; i < cities.getSize(); i++)
        {
            if (cities[i].getCityName() == cityName)
            {
                return true;
            }
        }
        return false;
    }

    bool isDuplicateFlight(const DynamicArray<Flight>& flights, const Flight& flight)
    {
        for (int i = 0; i < flights.getSize(); i++)
        {
            const Flight& existing = flights[i];
            if (existing.getOrigin() == flight.getOrigin() &&
                existing.getDestination() == flight.getDestination() &&
                existing.getDate() == flight.getDate() &&
                existing.getDepartureTime() == flight.getDepartureTime() &&
                existing.getArrivalTime() == flight.getArrivalTime() &&
                existing.getTicketPrice() == flight.getTicketPrice() &&
                existing.getAirlineName() == flight.getAirlineName())
            {
                return true;
            }
        }
        return false;
    }
}

FlightManager::FlightManager()
{
    allFlights.clear();
    allCities.clear();
}

void FlightManager::loadFlightsFromFile(string filename)
{
    ifstream file(filename);
    
    if (!file.is_open())
    {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string origin, destination, date, depTime, arrTime;
        if (!(ss >> origin >> destination >> date >> depTime >> arrTime))
        {
            continue;
        }

        DynamicArray<string> tokens;
        string token;
        while (ss >> token)
        {
            tokens.push_back(token);
        }

        if (tokens.getSize() == 0)
        {
            continue;
        }

        double price = 0.0;
        string airline;
        if (tokens.getSize() >= 2)
        {
            price = atof(tokens[0].c_str());
            airline = tokens[1];
        }
        else
        {
            airline = tokens[0];
        }

        origin = Utility::normalizeCityName(origin);
        destination = Utility::normalizeCityName(destination);

        Flight flight(origin, destination, date, depTime, arrTime, price, airline);
        if (!isDuplicateFlight(allFlights, flight))
        {
            allFlights.push_back(flight);
        }
    }

    file.close();
    cout << "Loaded " << allFlights.getSize() << " flights from file." << endl;
}

void FlightManager::loadCitiesFromFile(string filename)
{
    ifstream file(filename);
    
    if (!file.is_open())
    {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string cityName;
        double hotelCharge;

        ss >> cityName >> hotelCharge;

        cityName = Utility::normalizeCityName(cityName);

        City city(cityName, hotelCharge);
        if (!isDuplicateCity(allCities, cityName))
        {
            allCities.push_back(city);
        }
    }

    file.close();
    cout << "Loaded " << allCities.getSize() << " cities from file." << endl;
}

DynamicArray<Flight>& FlightManager::getAllFlights()
{
    return allFlights;
}

DynamicArray<City>& FlightManager::getAllCities()
{
    return allCities;
}

int FlightManager::getTotalFlights() const
{
    return allFlights.getSize();
}

int FlightManager::getTotalCities() const
{
    return allCities.getSize();
}

void FlightManager::displayAllFlights() const
{
    cout << "\n===== ALL FLIGHTS =====" << endl;
    for (int i = 0; i < allFlights.getSize(); i++)
    {
        cout << i + 1 << ". ";
        allFlights[i].display();
    }
}

void FlightManager::displayAllCities() const
{
    cout << "\n===== ALL CITIES =====" << endl;
    for (int i = 0; i < allCities.getSize(); i++)
    {
        cout << i + 1 << ". ";
        allCities[i].display();
    }
}

DynamicArray<Flight> FlightManager::getFlightsByOriginAndDestination(string origin, string destination)
{
    DynamicArray<Flight> result;
    
    for (int i = 0; i < allFlights.getSize(); i++)
    {
        if (allFlights[i].getOrigin() == origin && allFlights[i].getDestination() == destination)
        {
            result.push_back(allFlights[i]);
        }
    }
    
    return result;
}

DynamicArray<Flight> FlightManager::getFlightsByOriginDestinationAndDate(string origin, string destination, string date)
{
    DynamicArray<Flight> result;
    
    for (int i = 0; i < allFlights.getSize(); i++)
    {
        if (allFlights[i].getOrigin() == origin && 
            allFlights[i].getDestination() == destination &&
            allFlights[i].getDate() == date)
        {
            result.push_back(allFlights[i]);
        }
    }
    
    return result;
}

DynamicArray<Flight> FlightManager::getFlightsByAirline(string airline)
{
    DynamicArray<Flight> result;
    
    for (int i = 0; i < allFlights.getSize(); i++)
    {
        if (allFlights[i].getAirlineName() == airline)
        {
            result.push_back(allFlights[i]);
        }
    }
    
    return result;
}
