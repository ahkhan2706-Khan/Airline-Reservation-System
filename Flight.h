#ifndef FLIGHT_H
#define FLIGHT_H

#define _ITERATOR_DEBUG_LEVEL 2

#include <string>
using namespace std;

class Flight
{
private:
    string origin;
    string destination;
    string date;
    string departureTime;
    string arrivalTime;
    double ticketPrice;
    string airlineName;

public:
    // Constructor
    Flight();
    Flight(string org, string dest, string d, string depTime, string arrTime, double price, string airline);

    // Getters
    string getOrigin() const;
    string getDestination() const;
    string getDate() const;
    string getDepartureTime() const;
    string getArrivalTime() const;
    double getTicketPrice() const;
    string getAirlineName() const;

    // Setters
    void setOrigin(string org);
    void setDestination(string dest);
    void setDate(string d);
    void setDepartureTime(string depTime);
    void setArrivalTime(string arrTime);
    void setTicketPrice(double price);
    void setAirlineName(string airline);

    // Display
    void display() const;
};

#endif
