#ifndef CITY_H
#define CITY_H

#define _ITERATOR_DEBUG_LEVEL 2

#include <string>
using namespace std;

class City
{
private:
    string cityName;
    double hotelChargePerDay;

public:
    // Constructor
    City();
    City(string name, double hotelCharge);

    // Getters
    string getCityName() const;
    double getHotelChargePerDay() const;

    // Setters
    void setCityName(string name);
    void setHotelChargePerDay(double charge);

    // Display
    void display() const;
};

#endif
