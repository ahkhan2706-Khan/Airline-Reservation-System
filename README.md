<div align="center">

# ✈️ Airline Reservation System

**A C++ data structures project modelling a real-world airline reservation platform**

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue?logo=cplusplus&logoColor=white)](https://en.cppreference.com/w/cpp/17)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey?logo=windows&logoColor=white)](https://visualstudio.microsoft.com/)
[![IDE](https://img.shields.io/badge/IDE-Visual%20Studio-purple?logo=visualstudio&logoColor=white)](https://visualstudio.microsoft.com/)
[![Testing](https://img.shields.io/badge/Tests-Google%20Test-green?logo=google&logoColor=white)](https://github.com/google/googletest)
[![API](https://img.shields.io/badge/Web%20API-cpp--httplib-orange)](https://github.com/yhirose/cpp-httplib)
[![University](https://img.shields.io/badge/FAST%20NUCES-Spring%202026-red)](https://nu.edu.pk/)

<br/>

*Search flights · Filter by airline, cost, or transit · Book multi-leg journeys · All via CLI or a live web UI*

</div>

---

## 📑 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Data Structures & Algorithms](#data-structures--algorithms)
- [Query Scenarios](#query-scenarios)
- [Data Files](#data-files)
- [Web API](#web-api)
- [Building the Project](#building-the-project)
- [Running Tests](#running-tests)
- [Technologies Used](#technologies-used)

---

## Overview

The system reads flight schedules and hotel pricing from flat text files, builds an in-memory **flight graph** (cities as vertices, flights as directed edges), and answers passenger queries using recursive depth-first search combined with cost/time optimisation.

> 🗺️ **Find cheapest routes** · ⏱️ **Find fastest routes** · 🏨 **Factor hotel costs** · 🔄 **±1 day date fallback**

Key capabilities:

- Find the cheapest multi-leg journey between any two cities.
- Find the fastest multi-leg journey (including transit wait time).
- Filter results by preferred airline, mandatory transit city, and transit duration.
- Automatically expand the date range by ±1 day when no flights exist on the requested date.
- Charge hotel costs for transits longer than 12 hours.

---

## Features

| ✅ Feature | Details |
|---|---|
| Direct-flight search | Exact date (±1 day fallback) |
| Connecting-flight search | Up to configurable number of legs via recursive DFS |
| Cost optimisation | Ticket price + hotel charges for long transits |
| Time optimisation | Flight duration + all transit waiting time |
| Airline filter | Restrict results to a single carrier |
| Transit-city filter | Force routing through a specific city |
| Transit-duration filter | Minimum and maximum layover hours |
| Budget filter | Discard journeys above a cost ceiling |
| Web UI | Single-page HTML form served by the embedded HTTP server |
| REST API | Four JSON endpoints covering all major query types |
| Unit tests | Google Test suite covering models, graph, utilities, and scenarios |

---

## Project Structure

```
Airline-Reservation-System/
│
├── Flight.h / Flight.cpp           # Flight entity (origin, destination, date,
│                                   #   departure/arrival time, price, airline)
├── City.h / City.cpp               # City entity (name, hotel charge per day)
├── GraphNode.h / GraphNode.cpp     # Graph vertex: a city + its outgoing flights
├── FlightGraph.h / FlightGraph.cpp # Directed graph (adjacency list via std::map)
├── FlightManager.h / FlightManager.cpp  # File I/O: loads Flights.txt & HotelCharges_perday.txt
├── ReservationSystem.h / ReservationSystem.cpp  # Core query engine
├── Utility.h / Utility.cpp         # Time/date helpers, hotel-charge calculator, sort helpers
├── DynamicArray.h                  # Custom generic resizable array template
│
├── WebServer.cpp                   # cpp-httplib HTTP server + REST endpoints (main when RUN_WEBSERVER defined)
├── httplib.h                       # cpp-httplib single-header HTTP library
├── index.html                      # Browser UI served at /
│
├── test.cpp                        # Google Test unit tests (main when RUN_WEBSERVER not defined)
├── pch.h / pch.cpp                 # Precompiled headers
│
├── Flights.txt                     # Flight schedule data
├── HotelCharges_perday.txt         # Hotel prices per city
├── ProjectDescription.txt          # Original assignment brief
│
├── DSA PROJECT.sln                 # Visual Studio solution file
├── DSA PROJECT.vcxproj             # Visual Studio project file
└── packages.config                 # NuGet packages (Google Test)
```

---

## Data Structures & Algorithms

### Custom `DynamicArray<T>` (DynamicArray.h)

A hand-rolled generic resizable array that avoids STL `vector`. Supports:

- `push_back`, `pop_back`, `insert`, `erase`
- Copy constructor and assignment operator with deep copy
- Iterators (`begin`/`end`) for range-based operations
- Automatic capacity doubling on growth

### Flight Graph (FlightGraph / GraphNode)

- **Vertices** — `GraphNode` objects keyed by city name in a `std::map<string, GraphNode>`.
- **Edges** — each `GraphNode` stores a `DynamicArray<Flight>` of outgoing flights.
- Cities and their hotel charges are loaded from `HotelCharges_perday.txt`; edges are added from `Flights.txt`.

### Journey Search — Recursive DFS (ReservationSystem)

`searchJourneysRecursive` performs a depth-limited DFS from the origin to the destination:

1. At each city, all outgoing flights within the date window are enumerated.
2. A visited-city list prevents cycles.
3. Optional `TransitConstraint` and `AirlineConstraint` objects are checked at each step.
4. Transit time between consecutive legs is calculated; hotel charges are added when the layover exceeds 12 hours.
5. Completed paths are collected and then sorted by cost or travel time using selection sort.

### Cost Calculation

```
totalCost = Σ ticketPrice(leg)
          + Σ hotelChargePerDay(transitCity) × ⌈transitHours / 24⌉  (only when transit > 12 h)
```

### Date Handling

Dates are stored as `d/m/yyyy` strings. `Utility::addDaysToDate` performs arithmetic to compute the previous/next calendar day, enabling the ±1 day fallback search.

---

## Query Scenarios

| # | Scenario | Inputs | Sort order |
|---|---|---|---|
| 1 | Flights of a specific airline | Origin, Destination, Date, Airline | Cost ↑ |
| 2 | All routes with minimal travel time | Origin, Destination, Date | Total time ↑ |
| 3 | Connecting routes through a transit city | Origin, Destination, Date, Transit city | Cost & time displayed |
| 4 | Connecting routes with transit duration range | Origin, Destination, Date, Transit city, Min/max hours | Travel time ↑ |
| 5 | Direct flights only | Origin, Destination, Date | — |
| + | Journeys within a budget | Origin, Destination, Date, Max cost | Cost ↑ |
| + | Combined filters | Any combination of airline + transit + sort criterion | Configurable |

---

## Data Files

### `Flights.txt`

Space-separated records, one flight per line:

```
<Origin> <Destination> <Date d/m/yyyy> <DepartureTime HH:MM> <ArrivalTime HH:MM> <TicketPrice> <Airline>
```

Example:
```
Islamabad Newyork 1/12/2019 11:00 18:00 150000 Emirates
```

Airlines present in the dataset: **Emirates**, **Qatar**, **ANA**

Cities covered: Islamabad, New York, Paris, Tokyo, London (Lodon), Singapore, HongKong, Berlin (Berline), Seoul, Amsterdam

### `HotelCharges_perday.txt`

Two columns — city name and charge per day (PKR):

```
Islamabad 5000
NewYork   8000
Paris     20000
Tokyo     15000
London    10000
Singapore 18000
HongKong  7500
Berline   11000
Seoul     10500
Amsterdam 17000
```

---

## Web API

Start the web server by compiling with the `RUN_WEBSERVER` preprocessor macro defined. The server listens on **`http://localhost:8080`**.

### Endpoints

| Method | Path | Required params | Description |
|---|---|---|---|
| `GET` | `/` | — | Serves `index.html` |
| `GET` | `/api/min-time` | `origin`, `destination`, `date` | Journeys sorted by minimal travel time |
| `GET` | `/api/by-airline` | `origin`, `destination`, `date`, `airline` | Journeys for a specific airline, sorted by cost |
| `GET` | `/api/with-transit` | `origin`, `destination`, `date`, `transit` | Journeys routed through a transit city |
| `GET` | `/api/direct` | `origin`, `destination`, `date` | Direct flights only |

All endpoints return JSON. Date format: `d/m/yyyy`.

**Journey response shape:**
```json
{
  "count": 2,
  "journeys": [
    {
      "totalCost": 150000,
      "totalTravelTime": 420,
      "totalTransitTime": 0,
      "flights": [
        {
          "origin": "islamabad",
          "destination": "newyork",
          "date": "1/12/2019",
          "departureTime": "11:00",
          "arrivalTime": "18:00",
          "ticketPrice": 150000,
          "airline": "Emirates"
        }
      ]
    }
  ]
}
```

**Error response shape:**
```json
{ "error": "Missing origin, destination, or date." }
```

---

## Building the Project

> 💡 **Quick start:** Open the solution in Visual Studio, restore NuGet packages, and press `Ctrl+Shift+B`.

### Prerequisites

- **Visual Studio 2019 / 2022** (Windows) with the *Desktop development with C++* workload.
- NuGet package restore will download **Google Test** automatically.

### Steps

1. Open `DSA PROJECT.sln` in Visual Studio.
2. Select the desired configuration:
   - **Debug / Release** — builds the Google Test runner (`test.cpp` contains `main`).
   - Add `RUN_WEBSERVER` to *Project Properties → C/C++ → Preprocessor → Preprocessor Definitions* to build the HTTP server instead (`WebServer.cpp` contains `main`).
3. Build the solution (`Ctrl+Shift+B`).
4. Ensure `Flights.txt` and `HotelCharges_perday.txt` are in the working directory (same folder as the executable, or the project root when running from the IDE).

---

## Running Tests

The test suite uses **Google Test** and is located in `test.cpp`.

Build without `RUN_WEBSERVER` defined, then run the output executable. Example output:

```
[==========] Running 14 tests from 5 test suites.
[----------] 3 tests from FlightTest
[ RUN      ] FlightTest.FlightCreation          ... OK
[ RUN      ] FlightTest.FlightSetters           ... OK
...
[  PASSED  ] 14 tests.
```

### Test Coverage

| Suite | Tests |
|---|---|
| `FlightTest` | Construction, setters/getters |
| `CityTest` | Construction, setters/getters |
| `FlightGraphTest` | Add city/flight, direct-flight queries, airline filter |
| `UtilityTest` | Time conversion, duration, hotel charges |
| `ReservationSystemTest` | All 5 scenarios + budget + combined filters |

---

## Technologies Used

| Technology | Role |
|---|---|
| **C++17** | Core language |
| **STL `std::map`** | City-to-node index in the flight graph |
| **Custom `DynamicArray<T>`** | Replaces `std::vector` throughout |
| **[cpp-httplib](https://github.com/yhirose/cpp-httplib)** (single header) | Embedded HTTP server |
| **HTML5 / CSS3 / Vanilla JS** | Browser-based search UI |
| **Google Test** | Unit testing framework |
| **Visual Studio** | IDE + build system (MSBuild) |
| **NuGet** | Package management (Google Test) |

---

<div align="center">

*Built at FAST NUCES · Cyber Security · Data Structures · Spring 2026*

</div>
