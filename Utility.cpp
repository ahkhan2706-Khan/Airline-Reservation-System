#include "pch.h"
#include "Utility.h"
#include <sstream>
#include <iomanip>
#include <cctype>
using namespace std;

namespace
{
    struct DateParts
    {
        int day;
        int month;
        int year;
    };

    bool isLeapYear(int year)
    {
        return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    }

    int daysInMonth(int month, int year)
    {
        static const int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (month == 2 && isLeapYear(year))
        {
            return 29;
        }
        return daysPerMonth[month - 1];
    }

    DateParts parseDate(const string& date)
    {
        DateParts parts = { 0, 0, 0 };
        char sep1, sep2;
        stringstream ss(date);
        ss >> parts.day >> sep1 >> parts.month >> sep2 >> parts.year;
        return parts;
    }

    long long daysBeforeYear(int year)
    {
        return (long long)year * 365 + year / 4 - year / 100 + year / 400;
    }

    long long dateToSerial(const DateParts& parts)
    {
        static const int cumulativeDays[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
        long long days = daysBeforeYear(parts.year);
        days += cumulativeDays[parts.month - 1];
        if (parts.month > 2 && isLeapYear(parts.year))
        {
            days += 1;
        }
        days += (parts.day - 1);
        return days;
    }

    DateParts serialToDate(long long serial)
    {
        int low = 0;
        int high = 10000;

        while (low + 1 < high)
        {
            int mid = (low + high) / 2;
            if (daysBeforeYear(mid) <= serial)
            {
                low = mid;
            }
            else
            {
                high = mid;
            }
        }

        int year = low;
        long long dayOfYear = serial - daysBeforeYear(year);

        int month = 1;
        while (month <= 12)
        {
            int dim = daysInMonth(month, year);
            if (dayOfYear < dim)
            {
                break;
            }
            dayOfYear -= dim;
            month++;
        }

        DateParts parts = { (int)dayOfYear + 1, month, year };
        return parts;
    }

    string formatDate(const DateParts& parts)
    {
        stringstream ss;
        ss << parts.day << "/" << parts.month << "/" << parts.year;
        return ss.str();
    }
}

int Utility::timeToMinutes(string timeStr)
{
    // timeStr format: "HH:MM"
    stringstream ss(timeStr);
    int hours, minutes;
    char colon;

    ss >> hours >> colon >> minutes;

    return hours * 60 + minutes;
}

string Utility::minutesToTime(int minutes)
{
    int hours = minutes / 60;
    int mins = minutes % 60;

    string result;
    if (hours < 10) result += "0";
    result += to_string(hours) + ":";
    if (mins < 10) result += "0";
    result += to_string(mins);

    return result;
}

string Utility::normalizeCityName(string name)
{
    for (int i = 0; i < static_cast<int>(name.size()); i++)
    {
        name[i] = static_cast<char>(tolower(static_cast<unsigned char>(name[i])));
    }
    return name;
}

bool Utility::isValidTime(string timeStr)
{
    if (timeStr.size() != 5 || timeStr[2] != ':')
    {
        return false;
    }

    for (int i = 0; i < 5; i++)
    {
        if (i == 2)
        {
            continue;
        }
        if (!isdigit(static_cast<unsigned char>(timeStr[i])))
        {
            return false;
        }
    }

    int hours = (timeStr[0] - '0') * 10 + (timeStr[1] - '0');
    int minutes = (timeStr[3] - '0') * 10 + (timeStr[4] - '0');
    return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60;
}

bool Utility::isValidDate(string dateStr)
{
    int day = 0;
    int month = 0;
    int year = 0;
    char sep1 = 0;
    char sep2 = 0;
    stringstream ss(dateStr);
    if (!(ss >> day >> sep1 >> month >> sep2 >> year))
    {
        return false;
    }
    if (sep1 != '/' || sep2 != '/')
    {
        return false;
    }
    if (month < 1 || month > 12 || day < 1)
    {
        return false;
    }

    int dim = daysInMonth(month, year);
    return day <= dim;
}

bool Utility::isValidCityName(string name)
{
    if (name.empty())
    {
        return false;
    }

    for (int i = 0; i < static_cast<int>(name.size()); i++)
    {
        char ch = name[i];
        if (!isalpha(static_cast<unsigned char>(ch)))
        {
            return false;
        }
    }
    return true;
}

int Utility::calculateFlightDuration(string departureTime, string arrivalTime)
{
    int depMinutes = timeToMinutes(departureTime);
    int arrMinutes = timeToMinutes(arrivalTime);

    // If arrival time is less than departure time, it means next day arrival
    if (arrMinutes < depMinutes)
    {
        arrMinutes += 24 * 60; // Add 24 hours
    }

    return arrMinutes - depMinutes;
}

bool Utility::isDateInRange(string targetDate, string baseDate, int daysBefore, int daysAfter)
{
    DateParts target = parseDate(targetDate);
    DateParts base = parseDate(baseDate);

    long long targetSerial = dateToSerial(target);
    long long baseSerial = dateToSerial(base);

    long long minSerial = baseSerial - daysBefore;
    long long maxSerial = baseSerial + daysAfter;

    return targetSerial >= minSerial && targetSerial <= maxSerial;
}

string Utility::addDaysToDate(string date, int days)
{
    DateParts parts = parseDate(date);
    long long serial = dateToSerial(parts);
    serial += days;

    DateParts result = serialToDate(serial);
    return formatDate(result);
}

double Utility::calculateHotelCharge(int transitHours, double hotelChargePerDay)
{
    if (transitHours > 12)
    {
        double days = (double)transitHours / 24.0;
        return days * hotelChargePerDay;
    }
    return 0.0;
}

void Utility::sortFlightsByCost(DynamicArray<int>& indices, const DynamicArray<pair<double, int>>& costs)
{
    // Simple bubble sort for basic DSA approach
    for (int i = 0; i < indices.getSize(); i++)
    {
        for (int j = 0; j < indices.getSize() - 1 - i; j++)
        {
            if (costs[indices[j]].first > costs[indices[j + 1]].first)
            {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
}

void Utility::sortFlightsByTime(DynamicArray<int>& indices, const DynamicArray<pair<int, int>>& times)
{
    // Simple bubble sort for basic DSA approach
    for (int i = 0; i < indices.getSize(); i++)
    {
        for (int j = 0; j < indices.getSize() - 1 - i; j++)
        {
            if (times[indices[j]].first > times[indices[j + 1]].first)
            {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
}