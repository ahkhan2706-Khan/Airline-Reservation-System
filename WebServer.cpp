#include "pch.h"
#include "ReservationSystem.h"
#include "Utility.h"
#include "httplib.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace
{
    bool getRequiredParam(const httplib::Request& req, const string& key, string& value)
    {
        if (!req.has_param(key))
        {
            return false;
        }
        value = req.get_param_value(key);
        return !value.empty();
    }

    string jsonEscape(const string& value)
    {
        string out;
        out.reserve(value.size());
        for (size_t i = 0; i < value.size(); i++)
        {
            unsigned char ch = static_cast<unsigned char>(value[i]);
            switch (ch)
            {
            case '\\':
                out += "\\\\";
                break;
            case '"':
                out += "\\\"";
                break;
            case '\n':
                out += "\\n";
                break;
            case '\r':
                out += "\\r";
                break;
            case '\t':
                out += "\\t";
                break;
            default:
                if (ch < 0x20)
                {
                    const char* hex = "0123456789ABCDEF";
                    out += "\\u00";
                    out += hex[(ch >> 4) & 0x0F];
                    out += hex[ch & 0x0F];
                }
                else
                {
                    out += static_cast<char>(ch);
                }
                break;
            }
        }
        return out;
    }

    void writeFlightJson(stringstream& ss, const Flight& flight)
    {
        ss << "{";
        ss << "\"origin\":\"" << jsonEscape(flight.getOrigin()) << "\",";
        ss << "\"destination\":\"" << jsonEscape(flight.getDestination()) << "\",";
        ss << "\"date\":\"" << jsonEscape(flight.getDate()) << "\",";
        ss << "\"departureTime\":\"" << jsonEscape(flight.getDepartureTime()) << "\",";
        ss << "\"arrivalTime\":\"" << jsonEscape(flight.getArrivalTime()) << "\",";
        ss << "\"ticketPrice\":" << flight.getTicketPrice() << ",";
        ss << "\"airline\":\"" << jsonEscape(flight.getAirlineName()) << "\"";
        ss << "}";
    }

    string journeysToJson(const DynamicArray<ReservationSystem::Journey>& journeys)
    {
        stringstream ss;
        ss << "{";
        ss << "\"count\":" << journeys.getSize() << ",";
        ss << "\"journeys\":[";
        for (int i = 0; i < journeys.getSize(); i++)
        {
            if (i > 0)
            {
                ss << ",";
            }
            const auto& journey = journeys[i];
            ss << "{";
            ss << "\"totalCost\":" << journey.totalCost << ",";
            ss << "\"totalTravelTime\":" << journey.totalTravelTime << ",";
            ss << "\"totalTransitTime\":" << journey.totalTransitTime << ",";
            ss << "\"flights\":[";
            for (int j = 0; j < journey.flights.getSize(); j++)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                writeFlightJson(ss, journey.flights[j]);
            }
            ss << "]";
            ss << "}";
        }
        ss << "]";
        ss << "}";
        return ss.str();
    }

    string flightsToJson(const DynamicArray<Flight>& flights)
    {
        stringstream ss;
        ss << "{";
        ss << "\"count\":" << flights.getSize() << ",";
        ss << "\"flights\":[";
        for (int i = 0; i < flights.getSize(); i++)
        {
            if (i > 0)
            {
                ss << ",";
            }
            writeFlightJson(ss, flights[i]);
        }
        ss << "]";
        ss << "}";
        return ss.str();
    }

    ReservationSystem& getSystem()
    {
        static ReservationSystem system;
        static bool initialized = false;
        if (!initialized)
        {
            system.initialize("Flights.txt", "HotelCharges_perday.txt");
            initialized = true;
        }
        return system;
    }

    void respondBadRequest(httplib::Response& res, const string& message)
    {
        stringstream ss;
        ss << "{\"error\":\"" << jsonEscape(message) << "\"}";
        res.status = 400;
        res.set_content(ss.str(), "application/json");
    }
}

#ifdef RUN_WEBSERVER
int main()
{
    httplib::Server server;

    server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_file_content("index.html", "text/html");
    });

    server.Get("/index.html", [](const httplib::Request&, httplib::Response& res) {
        res.set_file_content("index.html", "text/html");
    });

    server.Get("/api/min-time", [](const httplib::Request& req, httplib::Response& res) {
        string origin;
        string destination;
        string date;
        if (!getRequiredParam(req, "origin", origin) ||
            !getRequiredParam(req, "destination", destination) ||
            !getRequiredParam(req, "date", date))
        {
            respondBadRequest(res, "Missing origin, destination, or date.");
            return;
        }
        if (!Utility::isValidCityName(origin) || !Utility::isValidCityName(destination))
        {
            respondBadRequest(res, "Invalid origin or destination.");
            return;
        }
        if (!Utility::isValidDate(date))
        {
            respondBadRequest(res, "Invalid date format. Use d/m/yyyy.");
            return;
        }

        auto journeys = getSystem().queryMinimalTravelTime(origin, destination, date);
        res.set_content(journeysToJson(journeys), "application/json");
    });

    server.Get("/api/by-airline", [](const httplib::Request& req, httplib::Response& res) {
        string origin;
        string destination;
        string date;
        string airline;
        if (!getRequiredParam(req, "origin", origin) ||
            !getRequiredParam(req, "destination", destination) ||
            !getRequiredParam(req, "date", date) ||
            !getRequiredParam(req, "airline", airline))
        {
            respondBadRequest(res, "Missing origin, destination, date, or airline.");
            return;
        }
        if (!Utility::isValidCityName(origin) || !Utility::isValidCityName(destination))
        {
            respondBadRequest(res, "Invalid origin or destination.");
            return;
        }
        if (!Utility::isValidDate(date))
        {
            respondBadRequest(res, "Invalid date format. Use d/m/yyyy.");
            return;
        }

        auto journeys = getSystem().queryDirectFlightsSpecificAirline(origin, destination, date, airline);
        res.set_content(journeysToJson(journeys), "application/json");
    });

    server.Get("/api/with-transit", [](const httplib::Request& req, httplib::Response& res) {
        string origin;
        string destination;
        string date;
        string transit;
        if (!getRequiredParam(req, "origin", origin) ||
            !getRequiredParam(req, "destination", destination) ||
            !getRequiredParam(req, "date", date) ||
            !getRequiredParam(req, "transit", transit))
        {
            respondBadRequest(res, "Missing origin, destination, date, or transit.");
            return;
        }
        if (!Utility::isValidCityName(origin) || !Utility::isValidCityName(destination) ||
            !Utility::isValidCityName(transit))
        {
            respondBadRequest(res, "Invalid origin, destination, or transit city.");
            return;
        }
        if (!Utility::isValidDate(date))
        {
            respondBadRequest(res, "Invalid date format. Use d/m/yyyy.");
            return;
        }

        auto journeys = getSystem().queryConnectingWithTransit(origin, destination, date, transit);
        res.set_content(journeysToJson(journeys), "application/json");
    });

    server.Get("/api/direct", [](const httplib::Request& req, httplib::Response& res) {
        string origin;
        string destination;
        string date;
        if (!getRequiredParam(req, "origin", origin) ||
            !getRequiredParam(req, "destination", destination) ||
            !getRequiredParam(req, "date", date))
        {
            respondBadRequest(res, "Missing origin, destination, or date.");
            return;
        }
        if (!Utility::isValidCityName(origin) || !Utility::isValidCityName(destination))
        {
            respondBadRequest(res, "Invalid origin or destination.");
            return;
        }
        if (!Utility::isValidDate(date))
        {
            respondBadRequest(res, "Invalid date format. Use d/m/yyyy.");
            return;
        }

        auto flights = getSystem().queryDirectFlightsOnly(origin, destination, date);
        res.set_content(flightsToJson(flights), "application/json");
    });

    cout << "Server running on http://localhost:8080" << endl;
    return server.listen("0.0.0.0", 8080) ? 0 : 1;
}
#endif
