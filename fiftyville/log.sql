-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND day = 28 AND month = 7 AND street = 'Humphrey Street';
-- Finds reports that happened during the day and location of the incident
SELECT * FROM interviews
WHERE year = 2021 AND day = 28 AND month = 7 AND transcript LIKE '%bakery%';
-- Finds transcripts of the interviews where the crime is described

SELECT * FROM phone_calls WHERE year = 2021 AND day = 28 AND month = 7 AND duration < 60;
-- Lists all calls that happened during the day of the theft that were less than 60 seconds.

Select name FROM people WHERE phone_number in
(SELECT receiver FROM phone_calls WHERE year = 2021 AND day = 28 AND month = 7 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name = 'Bruce'));
-- Gives accomplice by seeing who got a call during the theft from the theif

Select name FROM people WHERE phone_number IN
    (SELECT caller FROM phone_calls WHERE year = 2021 AND day = 28 AND month = 7 AND duration < 60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN
    (SELECT id FROM flights WHERE year = 2021 AND day = 29 AND month = 7 AND destination_airport_id = 4 ORDER BY hour, minute ASC LIMIT 1))
AND license_plate IN
    (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 7 AND activity = 'exit' AND hour = 10 AND (minute > 15 AND minute < 30))
AND id IN
    (SELECT person_id FROM bank_accounts WHERE account_number in
        (SELECT account_number FROM atm_transactions WHERE year = 2021 AND day = 28 AND month = 7 AND transaction_type = 'withdraw' and atm_location = 'Leggett Street'));
-- Uses call information along with passport numbers of everyone on the earliest flight
-- along with the license plate of the car that left right after the theft along with atm withdrawls
-- to find the culprit.


SELECT city FROM airports WHERE id = 4;
-- Gives city name