-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND day = 28 AND month = 7 AND street = 'Humphrey Street';
-- Finds reports that happened during the day and location of the incident
SELECT * FROM interviews
WHERE year = 2021 AND day = 28 AND month = 7 AND transcript LIKE '%bakery%';
-- Finds transcripts of the interviews where the crime is described


| 161 | Ruth    | 2021 | 7     | 28  |
"Sometime within ten minutes of the theft, I saw the thief get into a car in
the bakery parking lot and drive away. If you have security footage from the bakery parking lot,
you might want to look for cars that left the parking lot in that time frame."
| 162 | Eugene  | 2021 | 7     | 28  |
"I don't know the thief's name, but it was someone I recognized. Earlier this morning,
before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street
and saw the thief there withdrawing some money."
| 163 | Raymond | 2021 | 7     | 28  |
"As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville
tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket."

SELECT * FROM phone_calls WHERE year = 2021 AND day = 28 AND month = 7 AND duration < 60;

Select name FROM people WHERE phone_number in
(SELECT receiver FROM phone_calls WHERE year = 2021 AND day = 28 AND month = 7 AND duration < 60)
AND passport_number in (SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE year = 2021 AND day = 29 AND month = 7 ORDER BY hour LIMIT 1));

Select name FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE year = 2021 AND day = 28 AND month = 7 AND duration < 60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE year = 2021 AND day = 29 AND month = 7 ORDER BY hour LIMIT 1))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 7 AND activity = 'exit')
AND id IN(SELECT person_id FROM bank_accounts WHERE account_number in
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND day = 28 AND month = 7 AND transaction_type = 'withdraw' and atm_location = 'Leggett Street'));

SELECT activity FROM bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 7;