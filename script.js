const FLIGHTS_KEY = 'ars_flights_v1';
const RES_KEY = 'ars_reservations_v1';
const CITIES_KEY = 'ars_cities_v1';
const SEED_VERSION_KEY = 'ars_seed_version_v1';
const SEED_VERSION = '2026-05-03';
const NO_TRANSIT_LIMIT = -1;

const flightsSeed = `Islamabad Newyork 1/12/2019 11:00 18:00 150000 Emirates
Islamabad Newyork 1/12/2019 8:00 13:00 300000 Qatar
Newyork Islamabad 2/12/2019 11:00 18:00 150000 Emirates
Islamabad Paris 1/12/2019 8:00 13:00 100000 Qatar
Paris Islamabad 1/12/2019 15:00 20:00 100000 Qatar
Paris Islamabad 1/12/2019 14:00 17:00 90000 ANA
Islamabad Tokyo 1/12/2019 11:00 17:00 85000 ANA
Islamabad Lodon 1/12/2019 15:00 23:00 78000 Emirates
Newyork Amsterdam 1/12/2019 19:00 1:00 75000 ANA
Amsterdam Singapore 2/12/2019 8:00 1:00 65000 ANA
Singapore HongKong 1/12/2019 6:00 11:00 45000 Qatar
Berline Sydney 1/12/2019 5:00 9:00 35000 Emirates
Seoul Amsterdam 1/12/2019 6:00 14:00 150000 Qatar
Newyork Seoul 1/12/2019 20:00 24:00 36000 ANA
Paris Berlin 1/12/2019 0:30 4:00 25000 Qatar
Paris Tokyo 2/12/2019 1:00 6:00 35000 Emirates
Newyork Sydney 1/12/2019 15:00 23:50 Emirates
Islamabad Berlin 1/12/2019 1:00 7:00 85000 Qatar
Newyork Islamabad 1/12/2019 10:00 15:00 100000 ANA
Singapore Berlin 1/12/2019 5:00 10:00 50000 Emirates
Islamabad Newyork 3/12/2019 8:00 13:00 300000 Qatar
Paris Islamabad 5/12/2019 14:00 17:00 90000 ANA
Islamabad Tokyo 2/12/2019 11:00 17:00 85000 ANA
Seoul Paris 3/12/2019 8:00 13:00 100000 Qatar
Paris Islamabad 3/12/2019 15:00 20:00 100000 Qatar
Newyork Seoul 4/12/2019 20:00 24:00 36000 ANA
Singapore Berlin 5/12/2019 0:30 4:00 25000 Qatar
Paris Tokyo 6/12/2019 1:00 6:00 35000 Emirates
Tokyo Sydney 2/12/2019 5:00 9:00 35000 Emirates
Seoul Amsterdam 3/12/2019 6:00 14:00 150000 Qatar
Islamabad Amsterdam 3/12/2019 1:00 7:00 85000 Qatar
Newyork Islamabad 4/12/2019 10:00 15:00 100000 ANA
Islamabad Lodon 2/12/2019 15:00 23:00 78000 Emirates
Newyork Amsterdam 3/12/2019 19:00 1:00 75000 ANA
Amsterdam Singapore 4/12/2019 8:00 1:00 65000 ANA
Singapore Seoul 2/12/2019 6:00 11:00 45000 Qatar
Newyork Islamabad 4/12/2019 11:00 18:00 150000 Emirates
Singapore Berlin 2/12/2019 5:00 10:00 50000 Emirates
Amsterdam Islamabad 2/12/2019 11:00 16:00 100000 ANA
Newyork Sydney 2/12/2019 15:00 23:50 Emirates
Islamabad Tokyo 2/12/2019 11:00 18:00 150000 Emirates
Newyork Islamabad 3/12/2019 11:00 18:00 150000 Emirates
Islamabad Paris 4/12/2019 8:00 13:00 100000 Qatar
Paris Islamabad 5/12/2019 15:00 20:00 100000 Qatar
Paris Islamabad 6/12/2019 14:00 17:00 90000 ANA
Islamabad Tokyo 2/12/2019 11:00 17:00 85000 ANA
Newyork Amsterdam 3/12/2019 19:00 1:00 75000 ANA
Amsterdam Singapore 2/12/2019 8:00 1:00 65000 ANA
Singapore HongKong 4/12/2019 6:00 11:00 45000 Qatar
Newyork Islamabad 5/12/2019 11:00 16:00 100000 ANA
Berline Sydney 2/12/2019 5:00 9:00 35000 Emirates
Seoul Amsterdam 3/12/2019 6:00 14:00 150000 Qatar
Newyork Seoul 5/12/2019 20:00 24:00 36000 ANA
Paris Berlin 6/12/2019 0:30 4:00 25000 Qatar
Hongkong Tokyo 2/12/2019 1:00 6:00 35000 Emirates
Newyork Tokyo 4/12/2019 15:00 23:50 Emirates
Islamabad Berlin 2/12/2019 1:00 7:00 85000 Qatar
Newyork Islamabad 1/12/2019 10:00 15:00 100000 ANA
Singapore Berlin 2/12/2019 5:00 10:00 50000 Emirates
Paris Islamabad 5/12/2019 14:00 17:00 90000 ANA
Islamabad Tokyo 4/12/2019 11:00 17:00 85000 ANA
Seoul Paris 3/12/2019 8:00 13:00 100000 Qatar
Paris Islamabad 5/12/2019 15:00 20:00 100000 Qatar
Newyork Seoul 1/12/2019 20:00 24:00 36000 ANA
Singapore Tokyo 2/12/2019 1:00 6:00 35000 Emirates
Tokyo Sydney 4/12/2019 5:00 9:00 35000 Emirates
Seoul Amsterdam 6/12/2019 6:00 14:00 150000 Qatar
Islamabad Amsterdam 7/12/2019 1:00 7:00 85000 Qatar
Newyork Islamabad 2/12/2019 10:00 15:00 100000 ANA
Islamabad Lodon 4/12/2019 15:00 23:00 78000 Emirates
Newyork Amsterdam 2/12/2019 19:00 1:00 75000 ANA
Amsterdam Singapore 3/12/2019 8:00 1:00 65000 ANA
Singapore Seoul 6/12/2019 6:00 11:00 45000 Qatar
Berlin Islamabad 7/12/2019 11:00 18:00 150000 Emirates
Newyork Islamabad 2/12/2019 11:00 16:00 100000 ANA
Singapore Berlin 1/12/2019 5:00 10:00 50000 Emirates
Amsterdam Islamabad 1/12/2019 11:00 16:00 100000 ANA
Newyork Sydney 1/12/2019 15:00 23:50 Emirates
Seoul Newyork 6/12/2019 6:00 14:00 150000 Qatar
Islamabad Amsterdam 7/12/2019 1:00 7:00 85000 Qatar
Newyork Islamabad 2/12/2019 10:00 15:00 100000 ANA
Islamabad Lodon 4/12/2019 15:00 23:00 78000 Emirates
Newyork Amsterdam 2/12/2019 19:00 1:00 75000 ANA
Amsterdam Singapore 3/12/2019 8:00 1:00 65000 ANA
Singapore Seoul 6/12/2019 6:00 11:00 45000 Qatar
Berlin Islamabad 7/12/2019 11:00 18:00 150000 Emirates
Newyork Islamabad 2/12/2019 11:00 16:00 100000 ANA
Singapore Berlin 1/12/2019 5:00 10:00 50000 Emirates
Amsterdam Islamabad 1/12/2019 11:00 16:00 100000 ANA
Newyork Sydney 1/12/2019 15:00 23:50 Emirates
Hongkong Berlin 2/12/2019 1:00 6:00 35000 ANA
Berlin London 7/12/2019 11:00 18:00 150000 Emirates
Hongkong Paris 2/12/2019 1:00 6:00 35000 Qatar
London Hongkong 7/12/2019 11:00 18:00 150000 Emirates
Seoul Hongkong 1/12/2019 5:00 10:00 50000 Emirates
Islamabad Lodon 2/12/2019 15:00 23:00 78000 Emirates
Newyork Amsterdam 3/12/2019 19:00 1:00 75000 ANA
Amsterdam Singapore 5/12/2019 8:00 1:00 65000 ANA
Singapore Seoul 2/12/2019 6:00 11:00 45000 Qatar
Berlin Islamabad 2/12/2019 11:00 18:00 150000 Emirates
Newyork Islamabad 4/12/2019 11:00 16:00 100000 ANA
Singapore Berlin 3/12/2019 5:00 10:00 50000 Emirates
Amsterdam Islamabad 2/12/2019 11:00 16:00 100000 ANA
Newyork Sydney 5/12/2019 15:00 23:50 Emirates
Seoul Newyork 4/12/2019 6:00 14:00 150000 Qatar`;

const citySeed = `Islamabad 5000
NewYork 8000
Paris 20000
Tokyo 15000
London 10000
Singapore 18000
HongKong 7500
Berline 11000
Seoul 10500
Amsterdam 17000
`;

const normalizeCityName = (value) => (value || '').trim().toLowerCase();
const formatCityName = (value) =>
  value ? value.charAt(0).toUpperCase() + value.slice(1) : '';

const timeToMinutes = (timeStr) => {
  const [h, m] = timeStr.split(':').map(Number);
  return h * 60 + m;
};

const minutesToTime = (minutes) => {
  const hours = Math.floor(minutes / 60);
  const mins = minutes % 60;
  return `${hours.toString().padStart(2, '0')}:${mins.toString().padStart(2, '0')}`;
};

const isValidTime = (timeStr) => {
  if (!/^\d{2}:\d{2}$/.test(timeStr)) {
    return false;
  }
  const [hours, minutes] = timeStr.split(':').map(Number);
  return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60;
};

const isValidCityName = (name) => !!name && /^[a-zA-Z]+$/.test(name);

const parseDate = (dateStr) => {
  const [day, month, year] = dateStr.split('/').map(Number);
  return { day, month, year };
};

const isLeapYear = (year) =>
  year % 400 === 0 || (year % 4 === 0 && year % 100 !== 0);

const daysInMonth = (month, year) => {
  const days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
  if (month === 2 && isLeapYear(year)) {
    return 29;
  }
  return days[month - 1];
};

const isValidDate = (dateStr) => {
  const parts = parseDate(dateStr);
  if (!parts.day || !parts.month || !parts.year) {
    return false;
  }
  if (parts.month < 1 || parts.month > 12 || parts.day < 1) {
    return false;
  }
  return parts.day <= daysInMonth(parts.month, parts.year);
};

const daysBeforeYear = (year) =>
  year * 365 + Math.floor(year / 4) - Math.floor(year / 100) + Math.floor(year / 400);

const dateToSerial = (parts) => {
  const cumulativeDays = [0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334];
  let days = daysBeforeYear(parts.year);
  days += cumulativeDays[parts.month - 1];
  if (parts.month > 2 && isLeapYear(parts.year)) {
    days += 1;
  }
  days += parts.day - 1;
  return days;
};

const serialToDate = (serial) => {
  let low = 0;
  let high = 10000;
  while (low + 1 < high) {
    const mid = Math.floor((low + high) / 2);
    if (daysBeforeYear(mid) <= serial) {
      low = mid;
    } else {
      high = mid;
    }
  }
  const year = low;
  let dayOfYear = serial - daysBeforeYear(year);
  let month = 1;
  while (month <= 12) {
    const dim = daysInMonth(month, year);
    if (dayOfYear < dim) {
      break;
    }
    dayOfYear -= dim;
    month += 1;
  }
  return { day: dayOfYear + 1, month, year };
};

const formatDate = (parts) => `${parts.day}/${parts.month}/${parts.year}`;

const addDaysToDate = (date, days) => {
  const parts = parseDate(date);
  const serial = dateToSerial(parts) + days;
  return formatDate(serialToDate(serial));
};

const isDateInRange = (targetDate, baseDate, daysBefore, daysAfter) => {
  const targetSerial = dateToSerial(parseDate(targetDate));
  const baseSerial = dateToSerial(parseDate(baseDate));
  return targetSerial >= baseSerial - daysBefore && targetSerial <= baseSerial + daysAfter;
};

const calculateFlightDuration = (departureTime, arrivalTime) => {
  let depMinutes = timeToMinutes(departureTime);
  let arrMinutes = timeToMinutes(arrivalTime);
  if (arrMinutes < depMinutes) {
    arrMinutes += 24 * 60;
  }
  return arrMinutes - depMinutes;
};

const calculateHotelCharge = (transitHours, hotelChargePerDay) => {
  if (transitHours > 12) {
    return (transitHours / 24) * hotelChargePerDay;
  }
  return 0;
};

const calculateTransitMinutes = (first, second) => {
  const arrivalMinutes = timeToMinutes(first.arrivalTime);
  const departureMinutes = timeToMinutes(second.departureTime);
  if (second.date === first.date) {
    return departureMinutes - arrivalMinutes;
  }
  if (second.date === addDaysToDate(first.date, 1)) {
    return (24 * 60 - arrivalMinutes) + departureMinutes;
  }
  return -1;
};

const parseFlightLine = (line) => {
  const tokens = line.trim().split(/\s+/);
  if (tokens.length < 6) {
    return null;
  }
  const [origin, destination, date, departureTime, arrivalTime, ...rest] = tokens;
  let ticketPrice = 0;
  let airline = '';
  if (rest.length >= 2) {
    ticketPrice = Number(rest[0]);
    if (Number.isNaN(ticketPrice)) {
      ticketPrice = 0;
    }
    airline = rest.slice(1).join(' ');
  } else {
    airline = rest[0];
  }
  return {
    origin: normalizeCityName(origin),
    destination: normalizeCityName(destination),
    date,
    departureTime,
    arrivalTime,
    ticketPrice,
    airline,
  };
};

const isDuplicateFlight = (flights, flight) =>
  flights.some(
    (existing) =>
      existing.origin === flight.origin &&
      existing.destination === flight.destination &&
      existing.date === flight.date &&
      existing.departureTime === flight.departureTime &&
      existing.arrivalTime === flight.arrivalTime &&
      existing.ticketPrice === flight.ticketPrice &&
      existing.airline === flight.airline,
  );

const loadSeedFlights = () =>
  flightsSeed
    .split('\n')
    .map((line) => parseFlightLine(line))
    .filter(Boolean);

const loadSeedCities = () => {
  const cities = {};
  citySeed.split('\n').forEach((line) => {
    const tokens = line.trim().split(/\s+/);
    if (tokens.length === 2) {
      cities[normalizeCityName(tokens[0])] = Number(tokens[1]);
    }
  });
  return cities;
};

const mergeFlights = (existing, seeds) => {
  const merged = [...existing];
  seeds.forEach((flight) => {
    if (!isDuplicateFlight(merged, flight)) {
      merged.push(flight);
    }
  });
  return merged;
};

const mergeCities = (existing, seeds) => {
  const merged = { ...existing };
  Object.keys(seeds).forEach((city) => {
    if (!(city in merged)) {
      merged[city] = seeds[city];
    }
  });
  return merged;
};

function initData() {
  const seedFlights = loadSeedFlights();
  const seedCities = loadSeedCities();
  const storedFlights = JSON.parse(localStorage.getItem(FLIGHTS_KEY) || '[]');
  const storedCities = JSON.parse(localStorage.getItem(CITIES_KEY) || '{}');
  const seedVersion = localStorage.getItem(SEED_VERSION_KEY);

  if (!localStorage.getItem(FLIGHTS_KEY)) {
    localStorage.setItem(FLIGHTS_KEY, JSON.stringify(seedFlights));
  } else if (seedVersion !== SEED_VERSION) {
    localStorage.setItem(FLIGHTS_KEY, JSON.stringify(mergeFlights(storedFlights, seedFlights)));
  }

  if (!localStorage.getItem(CITIES_KEY)) {
    localStorage.setItem(CITIES_KEY, JSON.stringify(seedCities));
  } else if (seedVersion !== SEED_VERSION) {
    localStorage.setItem(CITIES_KEY, JSON.stringify(mergeCities(storedCities, seedCities)));
  }

  if (!localStorage.getItem(RES_KEY)) {
    localStorage.setItem(RES_KEY, '[]');
  }

  localStorage.setItem(SEED_VERSION_KEY, SEED_VERSION);
}

const getFlights = () => JSON.parse(localStorage.getItem(FLIGHTS_KEY) || '[]');
const saveFlights = (flights) =>
  localStorage.setItem(FLIGHTS_KEY, JSON.stringify(flights));
const getCities = () => JSON.parse(localStorage.getItem(CITIES_KEY) || '{}');
const getReservations = () => JSON.parse(localStorage.getItem(RES_KEY) || '[]');
const saveReservations = (reservations) =>
  localStorage.setItem(RES_KEY, JSON.stringify(reservations));

const getCityCount = () => {
  const cities = new Set(Object.keys(getCities()));
  getFlights().forEach((flight) => {
    cities.add(flight.origin);
    cities.add(flight.destination);
  });
  return cities.size;
};

const getDirectFlights = (origin, destination) =>
  getFlights().filter(
    (flight) => flight.origin === origin && flight.destination === destination,
  );

const getDirectFlightsOnDate = (origin, destination, date) =>
  getDirectFlights(origin, destination).filter((flight) => flight.date === date);

const getDirectFlightsWithDateRange = (origin, destination, date) => {
  const exact = getDirectFlightsOnDate(origin, destination, date);
  if (exact.length) {
    return exact;
  }
  const previous = getDirectFlightsOnDate(origin, destination, addDaysToDate(date, -1));
  const next = getDirectFlightsOnDate(origin, destination, addDaysToDate(date, 1));
  return [...previous, ...next];
};

const hasFlightsOnDate = (origin, date) =>
  getFlights().some((flight) => flight.origin === origin && flight.date === date);

const searchJourneysRecursive = (
  currentCity,
  destination,
  baseDate,
  remainingLegs,
  currentPath,
  currentCost,
  currentFlightMinutes,
  currentTransitMinutes,
  visitedCities,
  transitConstraint,
  airlineConstraint,
  transitSatisfied,
  allowDateRange,
  results,
) => {
  if (currentCity === destination && currentPath.length > 0) {
    if (transitConstraint?.enabled && !transitSatisfied) {
      return;
    }
    results.push({
      flights: [...currentPath],
      totalCost: currentCost,
      totalTransitTime: currentTransitMinutes,
      totalTravelTime: currentFlightMinutes + currentTransitMinutes,
    });
    return;
  }

  if (remainingLegs === 0) {
    return;
  }

  const outgoing = getFlights().filter((flight) => flight.origin === currentCity);
  for (const flight of outgoing) {
    if (airlineConstraint?.enabled && flight.airline !== airlineConstraint.airline) {
      continue;
    }
    if (visitedCities.has(flight.destination)) {
      continue;
    }

    let addedTransit = 0;
    let nextTransitSatisfied = transitSatisfied;

    if (currentPath.length === 0) {
      if (allowDateRange) {
        if (!isDateInRange(flight.date, baseDate, 1, 1)) {
          continue;
        }
      } else if (flight.date !== baseDate) {
        continue;
      }
    } else {
      addedTransit = calculateTransitMinutes(
        currentPath[currentPath.length - 1],
        flight,
      );
      if (addedTransit < 0) {
        continue;
      }
      if (transitConstraint?.enabled && currentCity === transitConstraint.city) {
        const minMinutes =
          transitConstraint.minHours >= 0 ? transitConstraint.minHours * 60 : 0;
        const maxMinutes =
          transitConstraint.maxHours >= 0
            ? transitConstraint.maxHours * 60
            : NO_TRANSIT_LIMIT;
        if (addedTransit < minMinutes) {
          continue;
        }
        if (maxMinutes !== NO_TRANSIT_LIMIT && addedTransit > maxMinutes) {
          continue;
        }
        nextTransitSatisfied = true;
      }
    }

    const flightDuration = calculateFlightDuration(flight.departureTime, flight.arrivalTime);
    let hotelCharge = 0;
    if (addedTransit > 0) {
      const transitHours = Math.ceil(addedTransit / 60);
      const cityCharge = getCities()[currentCity] || 0;
      hotelCharge = calculateHotelCharge(transitHours, cityCharge);
    }

    currentPath.push(flight);
    visitedCities.add(flight.destination);

    searchJourneysRecursive(
      flight.destination,
      destination,
      baseDate,
      remainingLegs - 1,
      currentPath,
      currentCost + flight.ticketPrice + hotelCharge,
      currentFlightMinutes + flightDuration,
      currentTransitMinutes + addedTransit,
      visitedCities,
      transitConstraint,
      airlineConstraint,
      nextTransitSatisfied,
      allowDateRange,
      results,
    );

    visitedCities.delete(flight.destination);
    currentPath.pop();
  }
};

const queryJourneys = (origin, destination, date, maxLegs = getCityCount()) => {
  const results = [];
  const visited = new Set([origin]);
  const allowDateRange = !hasFlightsOnDate(origin, date);
  searchJourneysRecursive(
    origin,
    destination,
    date,
    maxLegs,
    [],
    0,
    0,
    0,
    visited,
    null,
    null,
    false,
    allowDateRange,
    results,
  );
  return results;
};

const queryJourneysWithTransit = (
  origin,
  destination,
  date,
  maxLegs,
  transitCity,
  minTransitHours,
  maxTransitHours,
) => {
  const results = [];
  const visited = new Set([origin]);
  const allowDateRange = !hasFlightsOnDate(origin, date);
  const constraint = {
    city: transitCity,
    minHours: minTransitHours,
    maxHours: maxTransitHours,
    enabled: !!transitCity,
  };

  searchJourneysRecursive(
    origin,
    destination,
    date,
    maxLegs,
    [],
    0,
    0,
    0,
    visited,
    constraint,
    null,
    false,
    allowDateRange,
    results,
  );
  return results;
};

const queryJourneysWithAirline = (origin, destination, date, maxLegs, airline) => {
  const results = [];
  const visited = new Set([origin]);
  const allowDateRange = !hasFlightsOnDate(origin, date);
  const constraint = { airline, enabled: !!airline };

  searchJourneysRecursive(
    origin,
    destination,
    date,
    maxLegs,
    [],
    0,
    0,
    0,
    visited,
    null,
    constraint,
    false,
    allowDateRange,
    results,
  );
  return results;
};

const queryJourneysCombined = (
  origin,
  destination,
  date,
  maxLegs,
  airline,
  transitCity,
  minTransitHours,
  maxTransitHours,
  sortByCost,
) => {
  const results = [];
  const visited = new Set([origin]);
  const allowDateRange = !hasFlightsOnDate(origin, date);
  const transitConstraint = {
    city: transitCity,
    minHours: minTransitHours,
    maxHours: maxTransitHours,
    enabled: !!transitCity,
  };
  const airlineConstraint = { airline, enabled: !!airline };

  searchJourneysRecursive(
    origin,
    destination,
    date,
    maxLegs,
    [],
    0,
    0,
    0,
    visited,
    transitConstraint.enabled ? transitConstraint : null,
    airlineConstraint.enabled ? airlineConstraint : null,
    false,
    allowDateRange,
    results,
  );

  if (sortByCost) {
    sortJourneysByCost(results);
  } else {
    sortJourneysByTravelTime(results);
  }
  return results;
};

const queryDirectFlightsSpecificAirline = (origin, destination, date, airline) => {
  const journeys = queryJourneysWithAirline(origin, destination, date, getCityCount(), airline);
  sortJourneysByCost(journeys);
  return journeys;
};

const queryMinimalTravelTime = (origin, destination, date) => {
  const journeys = queryJourneys(origin, destination, date, getCityCount());
  sortJourneysByTravelTime(journeys);
  return journeys;
};

const queryConnectingWithTransit = (origin, destination, date, transitLocation) =>
  queryJourneysWithTransit(
    origin,
    destination,
    date,
    getCityCount(),
    transitLocation,
    NO_TRANSIT_LIMIT,
    NO_TRANSIT_LIMIT,
  );

const queryDirectFlightsOnly = (origin, destination, date) =>
  getDirectFlightsWithDateRange(origin, destination, date);

const queryJourneysWithinBudget = (origin, destination, date, maxLegs, maxCost) => {
  const journeys = queryJourneys(origin, destination, date, maxLegs);
  const filtered = journeys.filter((journey) => journey.totalCost <= maxCost);
  sortJourneysByCost(filtered);
  return filtered;
};

const sortJourneysByCost = (journeys) =>
  journeys.sort((a, b) => a.totalCost - b.totalCost);

const sortJourneysByTravelTime = (journeys) =>
  journeys.sort((a, b) => a.totalTravelTime - b.totalTravelTime);

const calculateTotalCost = (journey) =>
  journey.reduce((sum, flight) => sum + flight.ticketPrice, 0);

const calculateTotalTravelTime = (journey) =>
  journey.reduce(
    (sum, flight) =>
      sum + calculateFlightDuration(flight.departureTime, flight.arrivalTime),
    0,
  );

const renderFlightsTable = (flights) => {
  if (!flights.length) {
    return '<p class="muted">No flights found.</p>';
  }
  const rows = flights
    .map(
      (flight) => `<tr>
    <td>${formatCityName(flight.origin)}</td>
    <td>${formatCityName(flight.destination)}</td>
    <td>${flight.date}</td>
    <td>${flight.departureTime}</td>
    <td>${flight.arrivalTime}</td>
    <td>${flight.ticketPrice.toFixed(0)}</td>
    <td>${flight.airline}</td>
  </tr>`,
    )
    .join('');
  return `<table>
    <tr>
      <th>Origin</th>
      <th>Destination</th>
      <th>Date</th>
      <th>Departure</th>
      <th>Arrival</th>
      <th>Price</th>
      <th>Airline</th>
    </tr>
    ${rows}
  </table>`;
};

const renderJourneys = (journeys) => {
  if (!journeys.length) {
    return '<p class="muted">No journeys found matching criteria.</p>';
  }
  return journeys
    .map((journey, index) => {
      const totalCost = Number.isFinite(journey.totalCost)
        ? journey.totalCost
        : calculateTotalCost(journey.flights);
      const totalTravelTime = Number.isFinite(journey.totalTravelTime)
        ? journey.totalTravelTime
        : calculateTotalTravelTime(journey.flights);
      const totalTransitTime = Number.isFinite(journey.totalTransitTime)
        ? journey.totalTransitTime
        : 0;
      return `<div class="journey">
        <div class="journey-header">
          <span>Journey ${index + 1}</span>
          <span class="pill">Cost: ${totalCost.toFixed(2)}</span>
          <span class="pill">Travel: ${totalTravelTime} mins</span>
          <span class="pill">Transit: ${totalTransitTime} mins</span>
        </div>
        ${renderFlightsTable(journey.flights)}
      </div>`;
    })
    .join('');
};

const renderReservationsTable = (reservations) => {
  if (!reservations.length) {
    return '<p class="muted">No reservations found.</p>';
  }
  const rows = reservations
    .map(
      (res) => `<tr>
    <td>${res.id}</td>
    <td>${res.passenger}</td>
    <td>${res.status}</td>
    <td>${res.journey.totalCost.toFixed(2)}</td>
    <td>${res.journey.totalTravelTime}</td>
    <td>${new Date(res.createdAt).toLocaleString()}</td>
  </tr>`,
    )
    .join('');
  const details = reservations
    .map(
      (res) => `<details>
        <summary>${res.id} · ${res.passenger}</summary>
        ${renderFlightsTable(res.journey.flights)}
      </details>`,
    )
    .join('');
  return `<table>
    <tr>
      <th>ID</th>
      <th>Passenger</th>
      <th>Status</th>
      <th>Cost</th>
      <th>Travel Time</th>
      <th>Created</th>
    </tr>
    ${rows}
  </table>
  <div class="results">${details}</div>`;
};

const setMessage = (element, message, isError = false) => {
  element.textContent = message;
  element.style.color = isError ? '#c0392b' : '#1b5e20';
};

const validateCityPair = (origin, destination, target) => {
  if (!isValidCityName(origin) || !isValidCityName(destination)) {
    setMessage(target, 'Invalid origin or destination. Use letters only.', true);
    return false;
  }
  return true;
};

const validateDateInput = (date, target) => {
  if (!isValidDate(date)) {
    setMessage(target, 'Invalid date. Use d/m/yyyy.', true);
    return false;
  }
  return true;
};

const generateShieldToken = () => {
  if (typeof crypto === 'undefined' || !crypto.getRandomValues) {
    return null;
  }
  const bytes = new Uint8Array(8);
  crypto.getRandomValues(bytes);
  return [...bytes].map((value) => value.toString(16).padStart(2, '0')).join('').toUpperCase();
};

const getThreatLevel = (score) => {
  if (score < 20) return 'Low';
  if (score < 45) return 'Guarded';
  if (score < 70) return 'Elevated';
  return 'Critical';
};

const threatColorMap = {
  Low: '#22d3ee',
  Guarded: '#fbbf24',
  Elevated: '#fb7185',
  Critical: '#ff5cff',
};
const INITIAL_THREAT_SCORE = 6; // Baseline risk before anomalies are detected.
const MAX_TICKET_PRICE = 500000; // Policy ceiling for ticket price validation.
const SAFE_TEXT_PATTERN = /^[a-zA-Z0-9 .,'-]+$/;
const MAX_DISPLAYED_ISSUES = 5;
const isSafeText = (value) => !!value && SAFE_TEXT_PATTERN.test(value.trim());

const runSecurityScan = () => {
  const flights = getFlights();
  const reservations = getReservations();
  let score = INITIAL_THREAT_SCORE;
  const issues = [];
  let token = generateShieldToken();

  const pushIssue = (message, weight = 10) => {
    issues.push(message);
    score = Math.min(100, score + weight);
  };

  if (!token) {
    pushIssue('Shield token unavailable: crypto module missing.', 6);
    token = 'UNAVAILABLE';
  }

  flights.forEach((flight, index) => {
    const label = `Flight ${index + 1}`;
    if (!isValidCityName(flight.origin) || !isValidCityName(flight.destination)) {
      pushIssue(`${label}: suspicious city identifier detected.`);
    }
    if (!isValidDate(flight.date)) {
      pushIssue(`${label}: invalid date signature.`);
    }
    if (!isValidTime(flight.departureTime) || !isValidTime(flight.arrivalTime)) {
      pushIssue(`${label}: time anomaly flagged.`);
    }
    if (
      Number.isNaN(flight.ticketPrice) ||
      flight.ticketPrice < 0 ||
      flight.ticketPrice > MAX_TICKET_PRICE
    ) {
      pushIssue(`${label}: ticket price out of policy.`);
    }
    if (!isSafeText(flight.airline)) {
      pushIssue(`${label}: airline field failed sanitization.`);
    }
  });

  reservations.forEach((reservation) => {
    if (!isSafeText(reservation.passenger)) {
      pushIssue(`Reservation ${reservation.id}: passenger name requires review.`);
    }
    if (!['BOOKED', 'CANCELLED'].includes(reservation.status)) {
      pushIssue(`Reservation ${reservation.id}: status mismatch detected.`);
    }
    if (!reservation.journey || !Array.isArray(reservation.journey.flights)) {
      pushIssue(`Reservation ${reservation.id}: journey payload incomplete.`);
    }
  });

  return {
    score,
    issues,
    totalFlights: flights.length,
    totalReservations: reservations.length,
    token,
    threat: getThreatLevel(score),
  };
};

initData();

const addFlightForm = document.getElementById('addFlightForm');
const addFlightMsg = document.getElementById('addFlightMsg');
const searchFlightForm = document.getElementById('searchFlightForm');
const searchResult = document.getElementById('searchResult');
const bookForm = document.getElementById('bookForm');
const bookMsg = document.getElementById('bookMsg');
const bookResult = document.getElementById('bookResult');
const cancelForm = document.getElementById('cancelForm');
const cancelMsg = document.getElementById('cancelMsg');
const viewFlightsBtn = document.getElementById('viewFlightsBtn');
const viewReservationsBtn = document.getElementById('viewReservationsBtn');
const records = document.getElementById('records');
const modeSelect = document.getElementById('search-mode');
const modeFields = document.querySelectorAll('[data-modes]');
const cyberScanBtn = document.getElementById('cyberScanBtn');
const cyberModeBtn = document.getElementById('cyberModeBtn');
const cyberThreat = document.getElementById('cyberThreat');
const cyberToken = document.getElementById('cyberToken');
const cyberIntegrity = document.getElementById('cyberIntegrity');
const cyberScore = document.getElementById('cyberScore');
const cyberMeterBar = document.getElementById('cyberMeterBar');
const cyberLog = document.getElementById('cyberLog');

const updateModeFields = () => {
  const mode = modeSelect.value;
  modeFields.forEach((field) => {
    const modes = field.dataset.modes.split(',').map((val) => val.trim());
    field.classList.toggle('hidden', !modes.includes(mode));
  });
};

updateModeFields();
modeSelect.addEventListener('change', updateModeFields);

const renderSecurityLog = (report) => {
  if (!cyberLog) return;
  cyberLog.replaceChildren();
  const summary = document.createElement('div');
  summary.textContent = `Scan complete: ${report.issues.length} alerts across ${report.totalFlights} flights and ${report.totalReservations} reservations.`;
  cyberLog.appendChild(summary);
  if (!report.issues.length) {
    const ok = document.createElement('div');
    ok.textContent = '✅ Systems nominal.';
    cyberLog.appendChild(ok);
    return;
  }
  report.issues.slice(0, MAX_DISPLAYED_ISSUES).forEach((issue) => {
    const item = document.createElement('div');
    item.textContent = `⚠️ ${issue}`;
    cyberLog.appendChild(item);
  });
  if (report.issues.length > MAX_DISPLAYED_ISSUES) {
    const extra = document.createElement('div');
    extra.textContent = `+${report.issues.length - MAX_DISPLAYED_ISSUES} more alerts logged.`;
    cyberLog.appendChild(extra);
  }
};

const updateSecurityUI = (report) => {
  if (cyberThreat) {
    cyberThreat.textContent = report.threat;
    cyberThreat.style.color = threatColorMap[report.threat] || '';
  }
  if (cyberToken) {
    cyberToken.textContent = report.token;
  }
  if (cyberIntegrity) {
    cyberIntegrity.textContent = report.issues.length ? 'Watchlist' : 'Verified';
  }
  if (cyberScore) {
    cyberScore.textContent = `${report.score}%`;
  }
  if (cyberMeterBar) {
    cyberMeterBar.style.width = `${report.score}%`;
  }
  renderSecurityLog(report);
};

if (cyberScanBtn) {
  cyberScanBtn.addEventListener('click', () => {
    updateSecurityUI(runSecurityScan());
  });
  updateSecurityUI(runSecurityScan());
}

if (cyberModeBtn) {
  cyberModeBtn.addEventListener('click', () => {
    document.body.classList.toggle('secure-mode');
    cyberModeBtn.textContent = document.body.classList.contains('secure-mode')
      ? 'Disable Secure Mode'
      : 'Activate Secure Mode';
  });
}

addFlightForm.addEventListener('submit', (event) => {
  event.preventDefault();
  const formData = Object.fromEntries(new FormData(event.target));
  if (!validateCityPair(formData.origin, formData.destination, addFlightMsg)) {
    return;
  }
  if (!validateDateInput(formData.date, addFlightMsg)) {
    return;
  }
  if (!isValidTime(formData.departureTime) || !isValidTime(formData.arrivalTime)) {
    setMessage(addFlightMsg, 'Invalid time format. Use HH:MM.', true);
    return;
  }

  const flights = getFlights();
  const record = {
    origin: normalizeCityName(formData.origin),
    destination: normalizeCityName(formData.destination),
    date: formData.date,
    departureTime: formData.departureTime,
    arrivalTime: formData.arrivalTime,
    ticketPrice: formData.ticketPrice ? Number(formData.ticketPrice) : 0,
    airline: formData.airline.trim(),
  };

  if (Number.isNaN(record.ticketPrice) || record.ticketPrice < 0) {
    setMessage(addFlightMsg, 'Ticket price must be a positive number.', true);
    return;
  }

  if (isDuplicateFlight(flights, record)) {
    setMessage(addFlightMsg, 'Duplicate flight rejected.', true);
    return;
  }
  flights.push(record);
  saveFlights(flights);
  setMessage(addFlightMsg, 'Flight added successfully.');
  event.target.reset();
});

searchFlightForm.addEventListener('submit', (event) => {
  event.preventDefault();
  const formData = Object.fromEntries(new FormData(event.target));
  if (!validateCityPair(formData.origin, formData.destination, searchResult)) {
    return;
  }
  if (!validateDateInput(formData.date, searchResult)) {
    return;
  }
  const origin = normalizeCityName(formData.origin);
  const destination = normalizeCityName(formData.destination);
  const date = formData.date;

  let output = '';
  if (formData.mode === 'direct') {
    const flights = queryDirectFlightsOnly(origin, destination, date);
    output = renderFlightsTable(flights);
  } else if (formData.mode === 'by-airline') {
    if (!formData.airline) {
      setMessage(searchResult, 'Airline is required for this scenario.', true);
      return;
    }
    const journeys = queryDirectFlightsSpecificAirline(
      origin,
      destination,
      date,
      formData.airline.trim(),
    );
    output = renderJourneys(journeys);
  } else if (formData.mode === 'min-time') {
    const journeys = queryMinimalTravelTime(origin, destination, date);
    output = renderJourneys(journeys);
  } else if (formData.mode === 'with-transit') {
    if (!formData.transit || !isValidCityName(formData.transit)) {
      setMessage(searchResult, 'Valid transit city is required.', true);
      return;
    }
    const journeys = queryConnectingWithTransit(
      origin,
      destination,
      date,
      normalizeCityName(formData.transit),
    );
    output = renderJourneys(journeys);
  } else if (formData.mode === 'transit-range') {
    if (!formData.transit || !isValidCityName(formData.transit)) {
      setMessage(searchResult, 'Valid transit city is required.', true);
      return;
    }
    if (formData.minTransit === '' || formData.maxTransit === '') {
      setMessage(searchResult, 'Minimum and maximum transit hours are required.', true);
      return;
    }
    const minHours = Number(formData.minTransit);
    const maxHours = Number(formData.maxTransit);
    if (Number.isNaN(minHours) || Number.isNaN(maxHours)) {
      setMessage(searchResult, 'Transit hours must be numeric.', true);
      return;
    }
    const journeys = queryJourneysWithTransit(
      origin,
      destination,
      date,
      getCityCount(),
      normalizeCityName(formData.transit),
      minHours,
      maxHours,
    );
    sortJourneysByTravelTime(journeys);
    output = renderJourneys(journeys);
  } else if (formData.mode === 'budget') {
    const maxCost = Number(formData.maxCost);
    if (formData.maxCost === '' || Number.isNaN(maxCost) || maxCost < 0) {
      setMessage(searchResult, 'Valid max total cost is required.', true);
      return;
    }
    const journeys = queryJourneysWithinBudget(origin, destination, date, getCityCount(), maxCost);
    output = renderJourneys(journeys);
  } else if (formData.mode === 'combined') {
    const airline = formData.airline ? formData.airline.trim() : '';
    const rawTransit = formData.transit ? formData.transit.trim() : '';
    const transit = rawTransit ? normalizeCityName(rawTransit) : '';
    const minHours = formData.minTransit ? Number(formData.minTransit) : NO_TRANSIT_LIMIT;
    const maxHours = formData.maxTransit ? Number(formData.maxTransit) : NO_TRANSIT_LIMIT;
    if (rawTransit && !isValidCityName(rawTransit)) {
      setMessage(searchResult, 'Valid transit city is required.', true);
      return;
    }
    const journeys = queryJourneysCombined(
      origin,
      destination,
      date,
      getCityCount(),
      airline,
      transit,
      minHours,
      maxHours,
      formData.sortBy === 'cost',
    );
    output = renderJourneys(journeys);
  }

  searchResult.style.color = '';
  searchResult.innerHTML = output;
});

bookForm.addEventListener('submit', (event) => {
  event.preventDefault();
  const formData = Object.fromEntries(new FormData(event.target));
  if (!validateCityPair(formData.origin, formData.destination, bookMsg)) {
    return;
  }
  if (!validateDateInput(formData.date, bookMsg)) {
    return;
  }
  const journeys = queryJourneys(
    normalizeCityName(formData.origin),
    normalizeCityName(formData.destination),
    formData.date,
    getCityCount(),
  );
  sortJourneysByCost(journeys);
  if (!journeys.length) {
    setMessage(bookMsg, 'No itinerary found for booking.', true);
    bookResult.innerHTML = '';
    return;
  }
  const reservations = getReservations();
  const id = `RSV-${Date.now()}`;
  reservations.push({
    id,
    passenger: formData.passenger.trim(),
    status: 'BOOKED',
    journey: journeys[0],
    createdAt: new Date().toISOString(),
  });
  saveReservations(reservations);
  setMessage(bookMsg, `Reservation confirmed. ID: ${id}`);
  bookResult.innerHTML = renderJourneys([journeys[0]]);
  event.target.reset();
});

cancelForm.addEventListener('submit', (event) => {
  event.preventDefault();
  const formData = Object.fromEntries(new FormData(event.target));
  const reservations = getReservations();
  const reservation = reservations.find((res) => res.id === formData.reservationId);
  if (!reservation) {
    setMessage(cancelMsg, 'Reservation not found.', true);
    return;
  }
  if (reservation.status === 'CANCELLED') {
    setMessage(cancelMsg, 'Reservation already cancelled.', true);
    return;
  }
  reservation.status = 'CANCELLED';
  saveReservations(reservations);
  setMessage(cancelMsg, 'Reservation cancelled successfully.');
  event.target.reset();
});

viewFlightsBtn.addEventListener('click', () => {
  records.innerHTML = renderFlightsTable(getFlights());
});

viewReservationsBtn.addEventListener('click', () => {
  records.innerHTML = renderReservationsTable(getReservations());
});
