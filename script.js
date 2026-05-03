const FLIGHTS_KEY = 'ars_flights_v1';
const RES_KEY = 'ars_reservations_v1';
const CITIES_KEY = 'ars_cities_v1';

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

const norm = s => (s || '').trim().toLowerCase();
const t2m = t => { const [h,m]=t.split(':').map(Number); return h*60+m; };
const addDays = (d,delta)=>{ const [day,mon,yr]=d.split('/').map(Number); const x=new Date(Date.UTC(yr,mon-1,day)); x.setUTCDate(x.getUTCDate()+delta); return `${x.getUTCDate()}/${x.getUTCMonth()+1}/${x.getUTCFullYear()}`; };
const inRange=(target,base)=>[addDays(base,-1),base,addDays(base,1)].includes(target);
const flightDuration=(dep,arr)=>{let a=t2m(arr),d=t2m(dep); if(a<d)a+=1440; return a-d;};
const transitMinutes=(f1,f2)=>{const a=t2m(f1.arrivalTime),d=t2m(f2.departureTime); if(f2.date===f1.date) return d-a; if(f2.date===addDays(f1.date,1)) return (1440-a)+d; return -1;};
const hotelCharge=(hours,perDay)=>hours>12?(hours/24)*perDay:0;

function initData(){
  if(!localStorage.getItem(FLIGHTS_KEY)){
    const flights=[]; flightsSeed.split('\n').forEach(line=>{const p=line.trim().split(/\s+/); if(p.length>=7 && !isNaN(Number(p[5]))) flights.push({origin:norm(p[0]),destination:norm(p[1]),date:p[2],departureTime:p[3],arrivalTime:p[4],ticketPrice:Number(p[5]),airline:p.slice(6).join(' ')});});
    localStorage.setItem(FLIGHTS_KEY,JSON.stringify(flights));
  }
  if(!localStorage.getItem(CITIES_KEY)){
    const cities={}; citySeed.split('\n').forEach(l=>{const p=l.trim().split(/\s+/); if(p.length===2) cities[norm(p[0])]=Number(p[1]);});
    localStorage.setItem(CITIES_KEY,JSON.stringify(cities));
  }
  if(!localStorage.getItem(RES_KEY)) localStorage.setItem(RES_KEY,'[]');
}
const getFlights=()=>JSON.parse(localStorage.getItem(FLIGHTS_KEY)||'[]');
const getCities=()=>JSON.parse(localStorage.getItem(CITIES_KEY)||'{}');
const saveFlights=f=>localStorage.setItem(FLIGHTS_KEY,JSON.stringify(f));
const getRes=()=>JSON.parse(localStorage.getItem(RES_KEY)||'[]');
const saveRes=r=>localStorage.setItem(RES_KEY,JSON.stringify(r));

function queryJourneys(origin,destination,date,{airline='',transit=''}={}){/* ... */
const flights=getFlights(), cities=getCities(), results=[]; const visited=new Set([origin]); const hasOnDate=flights.some(f=>f.origin===origin&&f.date===date); const allowRange=!hasOnDate;
function dfs(city,path,cost,flightMin,transitMin,transitSatisfied){ if(city===destination&&path.length){if(transit&&!transitSatisfied)return;results.push({flights:[...path],totalCost:cost,totalTransitTime:transitMin,totalTravelTime:flightMin+transitMin});return;}
for(const f of flights.filter(x=>x.origin===city)){ if(airline&&f.airline!==airline)continue; if(visited.has(f.destination))continue; let addTransit=0,nextTS=transitSatisfied; if(path.length===0){ if(allowRange?!inRange(f.date,date):f.date!==date)continue; } else { addTransit=transitMinutes(path[path.length-1],f); if(addTransit<0)continue; if(transit&&city===transit)nextTS=true; } const hours=Math.ceil(addTransit/60); const hCharge=addTransit>0?hotelCharge(hours,cities[city]||0):0; visited.add(f.destination); path.push(f); dfs(f.destination,path,cost+f.ticketPrice+hCharge,flightMin+flightDuration(f.departureTime,f.arrivalTime),transitMin+addTransit,nextTS); path.pop(); visited.delete(f.destination); } }
dfs(origin,[],0,0,0,false); return results; }

function renderFlightsTable(f){ return f.length?`<table><tr><th>Origin</th><th>Destination</th><th>Date</th><th>Dep</th><th>Arr</th><th>Price</th><th>Airline</th></tr>${f.map(x=>`<tr><td>${x.origin}</td><td>${x.destination}</td><td>${x.date}</td><td>${x.departureTime}</td><td>${x.arrivalTime}</td><td>${x.ticketPrice}</td><td>${x.airline}</td></tr>`).join('')}</table>`:'No records'; }
function renderJourneys(j){return j.length?j.map((x,i)=>`<div class='journey'><b>Journey ${i+1}</b> | Cost ${x.totalCost.toFixed(2)} | Travel ${x.totalTravelTime} mins | Transit ${x.totalTransitTime} mins${renderFlightsTable(x.flights)}</div>`).join(''):'No journeys';}

initData();
// handlers
addFlightForm.onsubmit=e=>{e.preventDefault(); const fd=Object.fromEntries(new FormData(e.target)); const flights=getFlights(); const rec={origin:norm(fd.origin),destination:norm(fd.destination),date:fd.date,departureTime:fd.departureTime,arrivalTime:fd.arrivalTime,ticketPrice:Number(fd.ticketPrice),airline:fd.airline}; const dup=flights.some(f=>JSON.stringify(f)===JSON.stringify(rec)); if(dup) return addFlightMsg.textContent='Duplicate flight rejected.'; flights.push(rec); saveFlights(flights); addFlightMsg.textContent='Flight added.'; e.target.reset();};
searchFlightForm.onsubmit=e=>{e.preventDefault(); const fd=Object.fromEntries(new FormData(e.target)); const o=norm(fd.origin), d=norm(fd.destination), date=fd.date; let html=''; if(fd.mode==='direct'){ const flights=getFlights().filter(f=>f.origin===o&&f.destination===d&&(f.date===date||f.date===addDays(date,-1)||f.date===addDays(date,1))); html=renderFlightsTable(flights);} else if(fd.mode==='min-time'){ const j=queryJourneys(o,d,date); j.sort((a,b)=>a.totalTravelTime-b.totalTravelTime); html=renderJourneys(j);} else if(fd.mode==='by-airline'){ const j=queryJourneys(o,d,date,{airline:fd.airline}); j.sort((a,b)=>a.totalCost-b.totalCost); html=renderJourneys(j);} else { const j=queryJourneys(o,d,date,{transit:norm(fd.transit)}); html=renderJourneys(j);} searchResult.innerHTML=html; };
bookForm.onsubmit=e=>{e.preventDefault(); const fd=Object.fromEntries(new FormData(e.target)); const j=queryJourneys(norm(fd.origin),norm(fd.destination),fd.date); j.sort((a,b)=>a.totalCost-b.totalCost); if(!j.length){bookMsg.textContent='No itinerary found.';return;} const res=getRes(); const id='RSV-'+Date.now(); res.push({id,passenger:fd.passenger,status:'BOOKED',journey:j[0],createdAt:new Date().toISOString()}); saveRes(res); bookMsg.textContent=`Booked. Reservation ID: ${id}`; e.target.reset(); };
cancelForm.onsubmit=e=>{e.preventDefault(); const fd=Object.fromEntries(new FormData(e.target)); const res=getRes(); const r=res.find(x=>x.id===fd.reservationId); if(!r){cancelMsg.textContent='Reservation not found.';return;} r.status='CANCELLED'; saveRes(res); cancelMsg.textContent='Reservation cancelled.'; };
viewFlightsBtn.onclick=()=>records.innerHTML=renderFlightsTable(getFlights());
viewReservationsBtn.onclick=()=>{const rows=getRes().map(r=>`<tr><td>${r.id}</td><td>${r.passenger}</td><td>${r.status}</td><td>${r.journey.totalCost.toFixed(2)}</td><td>${r.journey.totalTravelTime}</td></tr>`).join(''); records.innerHTML=`<table><tr><th>ID</th><th>Passenger</th><th>Status</th><th>Cost</th><th>Travel Time</th></tr>${rows}</table>`;};
