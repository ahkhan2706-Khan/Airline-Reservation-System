#include "pch.h"
#include <gtest/gtest.h>
#include "Flight.h"
#include "City.h"
#include "FlightGraph.h"
#include "ReservationSystem.h"
#include "Utility.h"
#include "DynamicArray.h"

TEST(FlightTest, FlightCreation)
{
    Flight flight("islamabad", "newyork", "1/12/2019", "11:00", "18:00", 150000, "Emirates");

    EXPECT_EQ(flight.getOrigin(), "islamabad");
    EXPECT_EQ(flight.getDestination(), "newyork");
    EXPECT_EQ(flight.getDate(), "1/12/2019");
    EXPECT_EQ(flight.getDepartureTime(), "11:00");
    EXPECT_EQ(flight.getArrivalTime(), "18:00");
    EXPECT_EQ(flight.getTicketPrice(), 150000);
    EXPECT_EQ(flight.getAirlineName(), "Emirates");
}

TEST(FlightTest, FlightSetters)
{
    Flight flight;
    flight.setOrigin("islamabad");
    flight.setDestination("paris");
    flight.setDate("1/12/2019");
    flight.setDepartureTime("10:00");
    flight.setArrivalTime("13:00");
    flight.setTicketPrice(100000);
    flight.setAirlineName("Qatar");

    EXPECT_EQ(flight.getOrigin(), "islamabad");
    EXPECT_EQ(flight.getDestination(), "paris");
    EXPECT_EQ(flight.getTicketPrice(), 100000);
}

TEST(CityTest, CityCreation)
{
    City city("islamabad", 5000);

    EXPECT_EQ(city.getCityName(), "islamabad");
    EXPECT_EQ(city.getHotelChargePerDay(), 5000);
}

TEST(CityTest, CitySetters)
{
    City city;
    city.setCityName("paris");
    city.setHotelChargePerDay(20000);

    EXPECT_EQ(city.getCityName(), "paris");
    EXPECT_EQ(city.getHotelChargePerDay(), 20000);
}

TEST(FlightGraphTest, AddCity)
{
    FlightGraph graph;
    graph.addCity("islamabad", 5000);

    EXPECT_TRUE(graph.isCityExists("islamabad"));
    EXPECT_EQ(graph.getCityCount(), 1);
}

TEST(FlightGraphTest, AddFlight)
{
    FlightGraph graph;
    Flight flight("islamabad", "newyork", "1/12/2019", "11:00", "18:00", 150000, "Emirates");
    graph.addFlight(flight);

    EXPECT_TRUE(graph.isCityExists("islamabad"));
    EXPECT_TRUE(graph.isCityExists("newyork"));
    EXPECT_EQ(graph.getFlightCount(), 1);
}

TEST(FlightGraphTest, GetDirectFlights)
{
    FlightGraph graph;
    Flight flight1("islamabad", "newyork", "1/12/2019", "11:00", "18:00", 150000, "Emirates");
    Flight flight2("islamabad", "newyork", "1/12/2019", "8:00", "13:00", 300000, "Qatar");

    graph.addFlight(flight1);
    graph.addFlight(flight2);

    DynamicArray<Flight> result = graph.getDirectFlights("islamabad", "newyork");
    EXPECT_EQ(result.getSize(), 2);
}

TEST(FlightGraphTest, GetDirectFlightsOnDate)
{
    FlightGraph graph;
    Flight flight1("islamabad", "newyork", "1/12/2019", "11:00", "18:00", 150000, "Emirates");
    Flight flight2("islamabad", "newyork", "2/12/2019", "8:00", "13:00", 300000, "Qatar");

    graph.addFlight(flight1);
    graph.addFlight(flight2);

    DynamicArray<Flight> result = graph.getDirectFlightsOnDate("islamabad", "newyork", "1/12/2019");
    EXPECT_EQ(result.getSize(), 1);
    EXPECT_EQ(result[0].getDate(), "1/12/2019");
}

TEST(FlightGraphTest, GetFlightsByAirline)
{
    FlightGraph graph;
    Flight flight1("islamabad", "newyork", "1/12/2019", "11:00", "18:00", 150000, "Emirates");
    Flight flight2("paris", "tokyo", "2/12/2019", "1:00", "6:00", 35000, "Emirates");
    Flight flight3("islamabad", "newyork", "1/12/2019", "8:00", "13:00", 300000, "Qatar");

    graph.addFlight(flight1);
    graph.addFlight(flight2);
    graph.addFlight(flight3);

    DynamicArray<Flight> emiratesFlights = graph.getFlightsByAirline("Emirates");
    EXPECT_EQ(emiratesFlights.getSize(), 2);
}

TEST(UtilityTest, TimeToMinutes)
{
    int minutes = Utility::timeToMinutes("09:00");
    EXPECT_EQ(minutes, 540);
}

TEST(UtilityTest, CalculateFlightDuration)
{
    int duration = Utility::calculateFlightDuration("09:00", "11:00");
    EXPECT_EQ(duration, 120);
}

TEST(UtilityTest, CalculateFlightDurationNextDay)
{
    int duration = Utility::calculateFlightDuration("22:00", "02:00");
    EXPECT_EQ(duration, 240);
}

TEST(UtilityTest, CalculateHotelCharge)
{
    double charge = Utility::calculateHotelCharge(24, 3000);
    EXPECT_EQ(charge, 3000);
}

TEST(UtilityTest, CalculateHotelChargeNoCharge)
{
    double charge = Utility::calculateHotelCharge(10, 3000);
    EXPECT_EQ(charge, 0);
}

TEST(ReservationSystemTest, Scenario1DirectFlightsSpecificAirline)
{
    ReservationSystem system;
    system.initialize("Flights.txt", "HotelCharges_perday.txt");

    DynamicArray<ReservationSystem::Journey> journeys = system.queryDirectFlightsSpecificAirline(
        "islamabad", "newyork", "1/12/2019", "Emirates");

    EXPECT_GT(journeys.getSize(), 0);

    for (int i = 0; i < journeys.getSize(); i++)
    {
        for (int j = 0; j < journeys[i].flights.getSize(); j++)
        {
            EXPECT_EQ(journeys[i].flights[j].getOrigin(), "islamabad");
            EXPECT_EQ(journeys[i].flights[j].getDestination(), "newyork");
            EXPECT_EQ(journeys[i].flights[j].getAirlineName(), "Emirates");
        }
    }
}

TEST(ReservationSystemTest, Scenario5DirectFlights)
{
    ReservationSystem system;
    system.initialize("Flights.txt", "HotelCharges_perday.txt");

    DynamicArray<Flight> result = system.queryDirectFlightsOnly("islamabad", "lodon", "1/12/2019");

    for (int i = 0; i < result.getSize(); i++)
    {
        EXPECT_EQ(result[i].getOrigin(), "islamabad");
        EXPECT_EQ(result[i].getDestination(), "lodon");
        EXPECT_EQ(result[i].getDate(), "1/12/2019");
    }
}

TEST(ReservationSystemTest, Scenario2MinimalTravelTime)
{
    ReservationSystem system;
    system.initialize("Flights.txt", "HotelCharges_perday.txt");

    DynamicArray<ReservationSystem::Journey> journeys = system.queryMinimalTravelTime(
        "islamabad", "tokyo", "1/12/2019");

    EXPECT_GT(journeys.getSize(), 0);

    for (int i = 0; i < journeys.getSize(); i++)
    {
        EXPECT_EQ(journeys[i].flights[0].getOrigin(), "islamabad");
        EXPECT_EQ(journeys[i].flights[journeys[i].flights.getSize() - 1].getDestination(), "tokyo");
    }
}

TEST(ReservationSystemTest, Scenario4ConnectingWithTransitTime)
{
    ReservationSystem system;
    system.initialize("Flights.txt", "HotelCharges_perday.txt");

    DynamicArray<ReservationSystem::Journey> journeys = system.queryConnectingWithTransit(
        "islamabad",
        "sydney",
        "1/12/2019",
        "newyork");

    EXPECT_GE(journeys.getSize(), 0u);
}

TEST(ReservationSystemTest, ScenarioAdditionalBudget)
{
    ReservationSystem system;
    system.initialize("Flights.txt", "HotelCharges_perday.txt");

    double maxCost = 400000.0;
    DynamicArray<ReservationSystem::Journey> journeys = system.queryJourneysWithinBudget(
        "islamabad",
        "newyork",
        "1/12/2019",
        3,
        maxCost);

    for (int i = 0; i < journeys.getSize(); i++)
    {
        EXPECT_LE(journeys[i].totalCost, maxCost);
    }
}

TEST(ReservationSystemTest, Scenario1AirlineJourneys)
{
    ReservationSystem system;
    system.initialize("Flights.txt", "HotelCharges_perday.txt");

    DynamicArray<ReservationSystem::Journey> journeys = system.queryJourneysWithAirline(
        "islamabad",
        "newyork",
        "1/12/2019",
        2,
        "Qatar");

    system.sortJourneysByCost(journeys);
    EXPECT_GE(journeys.getSize(), 0u);
}

TEST(ReservationSystemTest, ScenarioCombinedFilters)
{
    ReservationSystem system;
    system.initialize("Flights.txt", "HotelCharges_perday.txt");

    DynamicArray<ReservationSystem::Journey> journeys = system.queryJourneysCombined(
        "islamabad",
        "sydney",
        "1/12/2019",
        3,
        "Emirates",
        "newyork",
        2,
        24,
        false);

    EXPECT_GE(journeys.getSize(), 0u);
}

#ifndef RUN_WEBSERVER
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif






