-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT street, description
FROM crime_scene_reports
WHERE year =2021 and day = 28 and month = 7;

SELECT name, transcript
FROM interviews
WHERE year =2021 and day = 28 and month = 7 and transcript LIKE '%bakery%';

SELECT hour, minute, activity, license_plate
FROM bakery_security_logs
WHERE year =2021 and day = 28 and month = 7 and HOUR>9;

SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE license_plate = '5P2BI95'OR license_plate = '94KL13X' OR license_plate = '6P58WS2';

SELECT people.name, account_number
FROM bank_accounts
JOIN people ON people.id=bank_accounts.person_id
ORDER BY people.name;

SELECT account_number, amount
FROM atm_transactions
WHERE year =2021 and day = 28 and month = 7 and atm_location = 'Leggett Street';

SELECT caller, receiver, duration
FROM phone_calls
WHERE year =2021 and day = 28 and month = 7 and caller='(367) 555-5533';

SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE phone_number='(375) 555-8161';

SELECT people.name, account_number
FROM bank_accounts
JOIN people ON people.id=bank_accounts.person_id
WHERE people.name= 'Robin';

SELECT city, full_name, abbreviation, airports.id
FROM airports
ORDER BY airports.id;

SELECT hour, minute, origin_airport_id, destination_airport_id, flights.id
FROM flights
WHERE year =2021 and day = 29 and month = 7 and origin_airport_id=8
ORDER BY hour;

SELECT passport_number, seat
FROM passengers
WHERE flight_id=36;