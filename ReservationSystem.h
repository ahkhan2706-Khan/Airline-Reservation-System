#ifndef RESERVATION_SYSTEM_H
#define RESERVATION_SYSTEM_H

#include "FlightGraph.h"
#include "FlightManager.h"
#include "DynamicArray.h"
#include <string>
using namespace std;

class ReservationSystem
{
private:
    struct Journey;
    struct TransitConstraint
    {
        string city;
        int minHours;
        int maxHours;
        bool enabled;
    };

    struct AirlineConstraint
    {
        string airline;
        bool enabled;
    };

    DynamicArray<Flight> getDirectFlightsWithDateRange(
        const string& origin,
        const string& destination,
        const string& date);
    FlightGraph graph;
    FlightManager manager;

    void searchJourneysRecursive(
        const string& currentCity,
        const string& destination,
        const string& baseDate,
        int remainingLegs,
        DynamicArray<Flight>& currentPath,
        double currentCost,
        int currentFlightMinutes,
        int currentTransitMinutes,
        DynamicArray<string>& visitedCities,
        const TransitConstraint* transitConstraint,
        const AirlineConstraint* airlineConstraint,
        bool transitSatisfied,
        bool allowDateRange,
        DynamicArray<struct Journey>& results);

public:
struct Journey
{
    DynamicArray<Flight> flights;
    double totalCost;
    int totalTravelTime;
    int totalTransitTime;
};

    // Constructor
    ReservationSystem();

    // Initialization
    void initialize(string flightFile, string hotelFile);
    
    // Query functions - Scenario based
    
    // Scenario 1: Direct flights with specific airline, sorted by cost
    DynamicArray<Journey> queryDirectFlightsSpecificAirline(
        string origin, 
        string destination, 
        string date, 
        string airline);
    
    // Scenario 2: All flights with minimal travel time (including connecting)
    DynamicArray<Journey> queryMinimalTravelTime(
        string origin, 
        string destination, 
        string date);
    
    // Scenario 3: Connecting flights with transit location
    DynamicArray<Journey> queryConnectingWithTransit(
        string origin, 
        string destination, 
        string date, 
        string transitLocation);
    
    // Scenario 5: Direct flights only
    DynamicArray<Flight> queryDirectFlightsOnly(
        string origin, 
        string destination, 
        string date);

    // Recursive journey search (multi-leg)
    DynamicArray<Journey> queryJourneys(
        string origin,
        string destination,
        string date,
        int maxLegs);

    DynamicArray<Journey> queryJourneysWithTransit(
        string origin,
        string destination,
        string date,
        int maxLegs,
        string transitCity,
        int minTransitHours,
        int maxTransitHours);

    DynamicArray<Journey> queryJourneysWithAirline(
        string origin,
        string destination,
        string date,
        int maxLegs,
        string airline);

    DynamicArray<Journey> queryJourneysCombined(
        string origin,
        string destination,
        string date,
        int maxLegs,
        string airline,
        string transitCity,
        int minTransitHours,
        int maxTransitHours,
        bool sortByCost);

    DynamicArray<Journey> queryJourneysWithinBudget(
        string origin,
        string destination,
        string date,
        int maxLegs,
        double maxCost);

    void sortJourneysByCost(DynamicArray<Journey>& journeys) const;
    void sortJourneysByTravelTime(DynamicArray<Journey>& journeys) const;
    void displayJourneyResults(const DynamicArray<Journey>& journeys) const;
    
    // Helper functions
    double calculateTotalCost(DynamicArray<Flight> journey);
    int calculateTotalTravelTime(DynamicArray<Flight> journey);
    
    // Display
    void displayQueryResults(DynamicArray<Flight> results);
    void displayGraphStatistics() const;
    void handleUserQuery();
};

#endif
