#include "pch.h"
#include "City.h"
#include <iostream>
using namespace std;

City::City()
{
    cityName = "";
    hotelChargePerDay = 0.0;
}

City::City(string name, double hotelCharge)
{
    cityName = name;
    hotelChargePerDay = hotelCharge;
}

string City::getCityName() const
{
    return cityName;
}

double City::getHotelChargePerDay() const
{
    return hotelChargePerDay;
}

void City::setCityName(string name)
{
    cityName = name;
}

void City::setHotelChargePerDay(double charge)
{
    hotelChargePerDay = charge;
}

void City::display() const
{
    cout << "City: " << cityName << " | Hotel Charge Per Day: " << hotelChargePerDay << endl;
}
