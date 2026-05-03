#include "pch.h"
#include "Flight.h"
#include <iostream>
using namespace std;

Flight::Flight()
{
    origin = "";
    destination = "";
    date = "";
    departureTime = "";
    arrivalTime = "";
    ticketPrice = 0.0;
    airlineName = "";
}

Flight::Flight(string org, string dest, string d, string depTime, string arrTime, double price, string airline)
{
    origin = org;
    destination = dest;
    date = d;
    departureTime = depTime;
    arrivalTime = arrTime;
    ticketPrice = price;
    airlineName = airline;
}

string Flight::getOrigin() const
{
    return origin;
}

string Flight::getDestination() const
{
    return destination;
}

string Flight::getDate() const
{
    return date;
}

string Flight::getDepartureTime() const
{
    return departureTime;
}

string Flight::getArrivalTime() const
{
    return arrivalTime;
}

double Flight::getTicketPrice() const
{
    return ticketPrice;
}

string Flight::getAirlineName() const
{
    return airlineName;
}

void Flight::setOrigin(string org)
{
    origin = org;
}

void Flight::setDestination(string dest)
{
    destination = dest;
}

void Flight::setDate(string d)
{
    date = d;
}

void Flight::setDepartureTime(string depTime)
{
    departureTime = depTime;
}

void Flight::setArrivalTime(string arrTime)
{
    arrivalTime = arrTime;
}

void Flight::setTicketPrice(double price)
{
    ticketPrice = price;
}

void Flight::setAirlineName(string airline)
{
    airlineName = airline;
}

void Flight::display() const
{
    cout << "Origin: " << origin << " | Destination: " << destination 
         << " | Date: " << date << " | Departure: " << departureTime 
         << " | Arrival: " << arrivalTime << " | Price: " << ticketPrice 
         << " | Airline: " << airlineName << endl;
}
