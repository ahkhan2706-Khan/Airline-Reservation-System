#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include "DynamicArray.h"
using namespace std;

class Utility
{
public:
    // Time conversion functions
    static int timeToMinutes(string timeStr);
    static string minutesToTime(int minutes);

    static string normalizeCityName(string name);
    static bool isValidTime(string timeStr);
    static bool isValidDate(string dateStr);
    static bool isValidCityName(string name);
    
    // Calculate travel duration
    static int calculateFlightDuration(string departureTime, string arrivalTime);
    
    // Date comparison
    static bool isDateInRange(string targetDate, string baseDate, int daysBefore, int daysAfter);
    static string addDaysToDate(string date, int days);
    
    // Hotel charge calculation
    static double calculateHotelCharge(int transitHours, double hotelChargePerDay);
    
    // Sorting utilities
    static void sortFlightsByCost(DynamicArray<int>& indices, const DynamicArray<pair<double, int>>& costs);
    static void sortFlightsByTime(DynamicArray<int>& indices, const DynamicArray<pair<int, int>>& times);
};

#endif
