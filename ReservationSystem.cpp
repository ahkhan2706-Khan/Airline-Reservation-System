#include "pch.h"
#include "ReservationSystem.h"
#include "Utility.h"
#include "DynamicArray.h"
#include <iostream>
using namespace std;

namespace
{
    bool isCityVisited(const DynamicArray<string>& visitedCities, const string& city)
    {
        for (int i = 0; i < visitedCities.getSize(); i++)
        {
            if (visitedCities[i] == city)
            {
                return true;
            }
        }
        return false;
    }

    int calculateTransitMinutes(const Flight& first, const Flight& second)
    {
        int arrivalMinutes = Utility::timeToMinutes(first.getArrivalTime());
        int departureMinutes = Utility::timeToMinutes(second.getDepartureTime());

        if (second.getDate() == first.getDate())
        {
            return departureMinutes - arrivalMinutes;
        }

        if (second.getDate() == Utility::addDaysToDate(first.getDate(), 1))
        {
            return (24 * 60 - arrivalMinutes) + departureMinutes;
        }

        return -1;
    }

    bool hasFlightsOnDate(FlightGraph& graph, const string& origin, const string& date)
    {
        GraphNode* node = graph.getCity(origin);
        if (node == nullptr)
        {
            return false;
        }

        const DynamicArray<Flight>& outgoing = node->getOutgoingFlights();
        for (int i = 0; i < outgoing.getSize(); i++)
        {
            if (outgoing[i].getDate() == date)
            {
                return true;
            }
        }

        return false;
    }
}

ReservationSystem::ReservationSystem()
{
    // Constructor
}

DynamicArray<Flight> ReservationSystem::getDirectFlightsWithDateRange(
    const string& origin,
    const string& destination,
    const string& date)
{
    string normalizedOrigin = Utility::normalizeCityName(origin);
    string normalizedDestination = Utility::normalizeCityName(destination);

    DynamicArray<Flight> result = graph.getDirectFlightsOnDate(normalizedOrigin, normalizedDestination, date);
    if (result.getSize() > 0)
    {
        return result;
    }

    string prevDate = Utility::addDaysToDate(date, -1);
    string nextDate = Utility::addDaysToDate(date, 1);

    DynamicArray<Flight> before = graph.getDirectFlightsOnDate(normalizedOrigin, normalizedDestination, prevDate);
    DynamicArray<Flight> after = graph.getDirectFlightsOnDate(normalizedOrigin, normalizedDestination, nextDate);

    for (int i = 0; i < before.getSize(); i++)
    {
        result.push_back(before[i]);
    }
    for (int i = 0; i < after.getSize(); i++)
    {
        result.push_back(after[i]);
    }

    return result;
}

void ReservationSystem::initialize(string flightFile, string hotelFile)
{
    // Load data from files
    manager.loadFlightsFromFile(flightFile);
    manager.loadCitiesFromFile(hotelFile);
    
    // Build graph from loaded data
    DynamicArray<City>& cities = manager.getAllCities();
    for (int i = 0; i < cities.getSize(); i++)
    {
        graph.addCity(cities[i].getCityName(), cities[i].getHotelChargePerDay());
    }
    
    DynamicArray<Flight>& flights = manager.getAllFlights();
    for (int i = 0; i < flights.getSize(); i++)
    {
        graph.addFlight(flights[i]);
    }
    
    cout << "\n===== RESERVATION SYSTEM INITIALIZED =====" << endl;
    cout << "Total Cities: " << graph.getCityCount() << endl;
    cout << "Total Flights: " << graph.getFlightCount() << endl;
}

DynamicArray<ReservationSystem::Journey> ReservationSystem::queryDirectFlightsSpecificAirline(
    string origin, 
    string destination, 
    string date, 
    string airline)
{
    DynamicArray<Journey> journeys = queryJourneysWithAirline(
        Utility::normalizeCityName(origin),
        Utility::normalizeCityName(destination),
        date,
        graph.getCityCount(),
        airline);

    sortJourneysByCost(journeys);
    return journeys;
}

DynamicArray<ReservationSystem::Journey> ReservationSystem::queryMinimalTravelTime(
    string origin, 
    string destination, 
    string date)
{
    DynamicArray<Journey> journeys = queryJourneys(
        Utility::normalizeCityName(origin),
        Utility::normalizeCityName(destination),
        date,
        graph.getCityCount());

    sortJourneysByTravelTime(journeys);
    return journeys;
}

DynamicArray<ReservationSystem::Journey> ReservationSystem::queryConnectingWithTransit(
    string origin, 
    string destination, 
    string date, 
    string transitLocation)
{
    return queryJourneysWithTransit(
        Utility::normalizeCityName(origin),
        Utility::normalizeCityName(destination),
        date,
        graph.getCityCount(),
        Utility::normalizeCityName(transitLocation),
        -1,
        -1);
}

DynamicArray<Flight> ReservationSystem::queryDirectFlightsOnly(
    string origin, 
    string destination, 
    string date)
{
    return getDirectFlightsWithDateRange(
        Utility::normalizeCityName(origin),
        Utility::normalizeCityName(destination),
        date);
}

void ReservationSystem::searchJourneysRecursive(
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
    DynamicArray<Journey>& results)
{
    if (currentCity == destination && currentPath.getSize() > 0)
    {
        if (transitConstraint != nullptr && transitConstraint->enabled && !transitSatisfied)
        {
            return;
        }

        Journey journey;
        journey.flights = currentPath;
        journey.totalCost = currentCost;
        journey.totalTransitTime = currentTransitMinutes;
        journey.totalTravelTime = currentFlightMinutes + currentTransitMinutes;
        results.push_back(journey);
        return;
    }

    if (remainingLegs == 0)
    {
        return;
    }

    GraphNode* node = graph.getCity(currentCity);
    if (node == nullptr)
    {
        return;
    }

    const DynamicArray<Flight>& outgoing = node->getOutgoingFlights();
    for (int i = 0; i < outgoing.getSize(); i++)
    {
        const Flight& flight = outgoing[i];

        if (airlineConstraint != nullptr && airlineConstraint->enabled &&
            flight.getAirlineName() != airlineConstraint->airline)
        {
            continue;
        }

        if (isCityVisited(visitedCities, flight.getDestination()))
        {
            continue;
        }

        int addedTransit = 0;
        bool nextTransitSatisfied = transitSatisfied;
        if (currentPath.getSize() == 0)
        {
            if (allowDateRange)
            {
                if (!Utility::isDateInRange(flight.getDate(), baseDate, 1, 1))
                {
                    continue;
                }
            }
            else if (flight.getDate() != baseDate)
            {
                continue;
            }
        }
        else
        {
            addedTransit = calculateTransitMinutes(currentPath.back(), flight);
            if (addedTransit < 0)
            {
                continue;
            }

            if (transitConstraint != nullptr && transitConstraint->enabled &&
                currentCity == transitConstraint->city)
            {
                int minMinutes = transitConstraint->minHours >= 0 ? transitConstraint->minHours * 60 : 0;
                int maxMinutes = transitConstraint->maxHours >= 0 ? transitConstraint->maxHours * 60 : -1;

                if (addedTransit < minMinutes)
                {
                    continue;
                }
                if (maxMinutes >= 0 && addedTransit > maxMinutes)
                {
                    continue;
                }

                nextTransitSatisfied = true;
            }
        }

        int flightDuration = Utility::calculateFlightDuration(
            flight.getDepartureTime(),
            flight.getArrivalTime());

        double hotelCharge = 0.0;
        if (addedTransit > 0)
        {
            int transitHours = (addedTransit + 59) / 60;
            hotelCharge = Utility::calculateHotelCharge(
                transitHours,
                node->getHotelChargePerDay());
        }

        currentPath.push_back(flight);
        visitedCities.push_back(flight.getDestination());

        searchJourneysRecursive(
            flight.getDestination(),
            destination,
            baseDate,
            remainingLegs - 1,
            currentPath,
            currentCost + flight.getTicketPrice() + hotelCharge,
            currentFlightMinutes + flightDuration,
            currentTransitMinutes + addedTransit,
            visitedCities,
            transitConstraint,
            airlineConstraint,
            nextTransitSatisfied,
            allowDateRange,
            results);

        visitedCities.pop_back();
        currentPath.pop_back();
    }
}

DynamicArray<ReservationSystem::Journey> ReservationSystem::queryJourneys(
    string origin,
    string destination,
    string date,
    int maxLegs)
{
    DynamicArray<Journey> results;
    DynamicArray<Flight> currentPath;
    DynamicArray<string> visitedCities;
    origin = Utility::normalizeCityName(origin);
    destination = Utility::normalizeCityName(destination);
    visitedCities.push_back(origin);
    bool allowDateRange = !hasFlightsOnDate(graph, origin, date);

    searchJourneysRecursive(
        origin,
        destination,
        date,
        maxLegs,
        currentPath,
        0.0,
        0,
        0,
        visitedCities,
        nullptr,
        nullptr,
        false,
        allowDateRange,
        results);

    return results;
}

DynamicArray<ReservationSystem::Journey> ReservationSystem::queryJourneysWithinBudget(
    string origin,
    string destination,
    string date,
    int maxLegs,
    double maxCost)
{
    DynamicArray<Journey> journeys = queryJourneys(origin, destination, date, maxLegs);
    DynamicArray<Journey> filtered;

    for (int i = 0; i < journeys.getSize(); i++)
    {
        if (journeys[i].totalCost <= maxCost)
        {
            filtered.push_back(journeys[i]);
        }
    }

    sortJourneysByCost(filtered);
    return filtered;
}

DynamicArray<ReservationSystem::Journey> ReservationSystem::queryJourneysCombined(
    string origin,
    string destination,
    string date,
    int maxLegs,
    string airline,
    string transitCity,
    int minTransitHours,
    int maxTransitHours,
    bool sortByCost)
{
    DynamicArray<Journey> results;
    DynamicArray<Flight> currentPath;
    DynamicArray<string> visitedCities;
    origin = Utility::normalizeCityName(origin);
    destination = Utility::normalizeCityName(destination);
    transitCity = Utility::normalizeCityName(transitCity);
    visitedCities.push_back(origin);
    bool allowDateRange = !hasFlightsOnDate(graph, origin, date);

    TransitConstraint transitConstraint;
    transitConstraint.city = transitCity;
    transitConstraint.minHours = minTransitHours;
    transitConstraint.maxHours = maxTransitHours;
    transitConstraint.enabled = !transitCity.empty();

    AirlineConstraint airlineConstraint;
    airlineConstraint.airline = airline;
    airlineConstraint.enabled = !airline.empty();

    const TransitConstraint* transitPtr = transitConstraint.enabled ? &transitConstraint : nullptr;
    const AirlineConstraint* airlinePtr = airlineConstraint.enabled ? &airlineConstraint : nullptr;

    searchJourneysRecursive(
        origin,
        destination,
        date,
        maxLegs,
        currentPath,
        0.0,
        0,
        0,
        visitedCities,
        transitPtr,
        airlinePtr,
        false,
        allowDateRange,
        results);

    if (sortByCost)
    {
        sortJourneysByCost(results);
    }
    else
    {
        sortJourneysByTravelTime(results);
    }

    return results;
}

void ReservationSystem::sortJourneysByCost(DynamicArray<Journey>& journeys) const
{
    for (int i = 0; i < journeys.getSize(); i++)
    {
        for (int j = 0; j < journeys.getSize() - 1 - i; j++)
        {
            if (journeys[j].totalCost > journeys[j + 1].totalCost)
            {
                Journey temp = journeys[j];
                journeys[j] = journeys[j + 1];
                journeys[j + 1] = temp;
            }
        }
    }
}

void ReservationSystem::sortJourneysByTravelTime(DynamicArray<Journey>& journeys) const
{
    for (int i = 0; i < journeys.getSize(); i++)
    {
        for (int j = 0; j < journeys.getSize() - 1 - i; j++)
        {
            if (journeys[j].totalTravelTime > journeys[j + 1].totalTravelTime)
            {
                Journey temp = journeys[j];
                journeys[j] = journeys[j + 1];
                journeys[j + 1] = temp;
            }
        }
    }
}

void ReservationSystem::displayJourneyResults(const DynamicArray<Journey>& journeys) const
{
    if (journeys.getSize() == 0)
    {
        cout << "No journeys found matching criteria." << endl;
        return;
    }

    cout << "\n===== JOURNEY RESULTS =====" << endl;
    cout << "Total Journeys: " << journeys.getSize() << endl;

    for (int i = 0; i < journeys.getSize(); i++)
    {
        cout << i + 1 << ". Total Cost: " << journeys[i].totalCost
            << " | Total Travel Time: " << journeys[i].totalTravelTime
            << " mins" << endl;

        for (int j = 0; j < journeys[i].flights.getSize(); j++)
        {
            cout << "   Leg " << j + 1 << ": ";
            journeys[i].flights[j].display();
        }
    }
}

DynamicArray<ReservationSystem::Journey> ReservationSystem::queryJourneysWithTransit(
    string origin,
    string destination,
    string date,
    int maxLegs,
    string transitCity,
    int minTransitHours,
    int maxTransitHours)
{
    DynamicArray<Journey> results;
    DynamicArray<Flight> currentPath;
    DynamicArray<string> visitedCities;
    origin = Utility::normalizeCityName(origin);
    destination = Utility::normalizeCityName(destination);
    transitCity = Utility::normalizeCityName(transitCity);
    visitedCities.push_back(origin);
    bool allowDateRange = !hasFlightsOnDate(graph, origin, date);

    TransitConstraint constraint;
    constraint.city = transitCity;
    constraint.minHours = minTransitHours;
    constraint.maxHours = maxTransitHours;
    constraint.enabled = !transitCity.empty();

    searchJourneysRecursive(
        origin,
        destination,
        date,
        maxLegs,
        currentPath,
        0.0,
        0,
        0,
        visitedCities,
        &constraint,
        nullptr,
        false,
        allowDateRange,
        results);

    return results;
}

DynamicArray<ReservationSystem::Journey> ReservationSystem::queryJourneysWithAirline(
    string origin,
    string destination,
    string date,
    int maxLegs,
    string airline)
{
    DynamicArray<Journey> results;
    DynamicArray<Flight> currentPath;
    DynamicArray<string> visitedCities;
    origin = Utility::normalizeCityName(origin);
    destination = Utility::normalizeCityName(destination);
    visitedCities.push_back(origin);
    bool allowDateRange = !hasFlightsOnDate(graph, origin, date);

    AirlineConstraint constraint;
    constraint.airline = airline;
    constraint.enabled = !airline.empty();

    searchJourneysRecursive(
        origin,
        destination,
        date,
        maxLegs,
        currentPath,
        0.0,
        0,
        0,
        visitedCities,
        nullptr,
        &constraint,
        false,
        allowDateRange,
        results);

    return results;
}

double ReservationSystem::calculateTotalCost(DynamicArray<Flight> journey)
{
    double totalCost = 0.0;
    
    for (int i = 0; i < journey.getSize(); i++)
    {
        totalCost += journey[i].getTicketPrice();
    }
    
    return totalCost;
}

int ReservationSystem::calculateTotalTravelTime(DynamicArray<Flight> journey)
{
    int totalTime = 0;
    
    for (int i = 0; i < journey.getSize(); i++)
    {
        totalTime += Utility::calculateFlightDuration(
            journey[i].getDepartureTime(), 
            journey[i].getArrivalTime());
    }
    
    return totalTime;
}

void ReservationSystem::displayQueryResults(DynamicArray<Flight> results)
{
    if (results.getSize() == 0)
    {
        cout << "No flights found matching criteria." << endl;
        return;
    }
    
    cout << "\n===== QUERY RESULTS =====" << endl;
    cout << "Total Results: " << results.getSize() << endl;
    
    for (int i = 0; i < results.getSize(); i++)
    {
        cout << i + 1 << ". ";
        results[i].display();
    }
}

void ReservationSystem::displayGraphStatistics() const
{
    cout << "\n===== SYSTEM STATISTICS =====" << endl;
    cout << "Total Cities: " << graph.getCityCount() << endl;
    cout << "Total Flights: " << graph.getFlightCount() << endl;
}

void ReservationSystem::handleUserQuery()
{
    int scenario = 0;
    cout << "\nSelect scenario (1-6): ";
    cin >> scenario;

    string origin;
    string destination;
    string date;
    cout << "Origin: ";
    cin >> origin;
    while (!Utility::isValidCityName(origin))
    {
        cout << "Invalid origin. Enter again: ";
        cin >> origin;
    }

    cout << "Destination: ";
    cin >> destination;
    while (!Utility::isValidCityName(destination))
    {
        cout << "Invalid destination. Enter again: ";
        cin >> destination;
    }

    cout << "Date (d/m/yyyy): ";
    cin >> date;
    while (!Utility::isValidDate(date))
    {
        cout << "Invalid date. Enter again: ";
        cin >> date;
    }

    if (scenario == 1)
    {
        string airline;
        cout << "Airline: ";
        cin >> airline;
        DynamicArray<Journey> journeys = queryDirectFlightsSpecificAirline(origin, destination, date, airline);
        displayJourneyResults(journeys);
    }
    else if (scenario == 2)
    {
        DynamicArray<Journey> journeys = queryMinimalTravelTime(origin, destination, date);
        displayJourneyResults(journeys);
    }
    else if (scenario == 3)
    {
        string transitCity;
        cout << "Transit city: ";
        cin >> transitCity;
        while (!Utility::isValidCityName(transitCity))
        {
            cout << "Invalid transit city. Enter again: ";
            cin >> transitCity;
        }
        DynamicArray<Journey> journeys = queryConnectingWithTransit(origin, destination, date, transitCity);
        displayJourneyResults(journeys);
    }
    else if (scenario == 4)
    {
        string transitCity;
        int minHours = 0;
        int maxHours = 0;
        cout << "Transit city: ";
        cin >> transitCity;
        while (!Utility::isValidCityName(transitCity))
        {
            cout << "Invalid transit city. Enter again: ";
            cin >> transitCity;
        }
        cout << "Minimum transit hours: ";
        cin >> minHours;
        cout << "Maximum transit hours: ";
        cin >> maxHours;
        DynamicArray<Journey> journeys = queryJourneysWithTransit(
            origin,
            destination,
            date,
            graph.getCityCount(),
            transitCity,
            minHours,
            maxHours);
        sortJourneysByTravelTime(journeys);
        displayJourneyResults(journeys);
    }
    else if (scenario == 5)
    {
        DynamicArray<Flight> results = queryDirectFlightsOnly(origin, destination, date);
        displayQueryResults(results);
    }
    else if (scenario == 6)
    {
        double maxCost = 0.0;
        cout << "Maximum total cost: ";
        cin >> maxCost;
        if (maxCost < 0)
        {
            cout << "Invalid cost." << endl;
            return;
        }

        DynamicArray<Journey> journeys = queryJourneysWithinBudget(
            origin,
            destination,
            date,
            graph.getCityCount(),
            maxCost);
        displayJourneyResults(journeys);
    }
    else
    {
        cout << "Invalid scenario." << endl;
    }
}
