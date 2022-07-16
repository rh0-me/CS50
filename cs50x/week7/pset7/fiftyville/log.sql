-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT *
FROM crime_scene_reports
WHERE year = 2021
    AND MONTH = 7
    AND DAY = 28;
-- | 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
SELECT *
FROM interviews
WHERE year = 2021
    AND MONTH = 7
    AND DAY >= 28;
/*
 | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
 | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
 | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
 */
SELECT *
FROM bakery_security_logs
WHERE year = 2021
    AND MONTH = 7
    AND DAY = 28
    AND HOUR BETWEEN 10 AND 11
    AND MINUTE BETWEEN 15 AND 25;
/*
 +-----+------+-------+-----+------+--------+----------+---------------+
 | id  | year | month | day | hour | minute | activity | license_plate |
 +-----+------+-------+-----+------+--------+----------+---------------+
 | 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
 | 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
 | 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
 | 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
 | 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
 | 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
 | 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
 | 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
 +-----+------+-------+-----+------+--------+----------+---------------+
 */
-- get people corresponding to the license plates
SELECT *
FROM people
WHERE license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
            AND MONTH = 7
            AND DAY = 28
            AND HOUR BETWEEN 10 AND 11
            AND MINUTE BETWEEN 15 AND 25
    );
-- potential suspects1
/*
 +--------+---------+----------------+-----------------+---------------+
 |   id   |  name   |  phone_number  | passport_number | license_plate |
 +--------+---------+----------------+-----------------+---------------+
 | 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
 | 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
 | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
 | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
 | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
 | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
 | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
 | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
 +--------+---------+----------------+-----------------+---------------+
 */
-- check atm transactions
SELECT *
FROM atm_transactions
WHERE year = 2021
    AND MONTH = 7
    AND DAY = 28
    AND transaction_type = "withdraw"
    AND atm_location = "Leggett Street";
-- suspects accounts
/*
 +-----+----------------+------+-------+-----+----------------+------------------+--------+
 | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
 +-----+----------------+------+-------+-----+----------------+------------------+--------+
 | 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
 | 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
 | 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
 | 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
 | 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
 | 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
 | 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
 | 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
 +-----+----------------+------+-------+-----+----------------+------------------+--------+
 */
-- persons corresponding to their account_number
SELECT *
FROM people
WHERE id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
                SELECT account_number
                FROM atm_transactions
                WHERE year = 2021
                    AND MONTH = 7
                    AND DAY = 28
                    AND transaction_type = "withdraw"
                    AND atm_location = "Leggett Street"
            )
    );
-- potential suspects2
/*
 +--------+---------+----------------+-----------------+---------------+
 |   id   |  name   |  phone_number  | passport_number | license_plate |
 +--------+---------+----------------+-----------------+---------------+
 | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
 | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
 | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
 | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
 | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
 | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
 | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
 | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
 +--------+---------+----------------+-----------------+---------------+
 */
-- intersect with suspects1 and suspects2
SELECT *
FROM people
WHERE license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
            AND MONTH = 7
            AND DAY = 28
            AND HOUR BETWEEN 10 AND 11
            AND MINUTE BETWEEN 15 AND 25
    )
INTERSECT
SELECT *
FROM people
WHERE id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
                SELECT account_number
                FROM atm_transactions
                WHERE year = 2021
                    AND MONTH = 7
                    AND DAY = 28
                    AND transaction_type = "withdraw"
                    AND atm_location = "Leggett Street"
            )
    );
/*
 +--------+-------+----------------+-----------------+---------------+
 |   id   | name  |  phone_number  | passport_number | license_plate |
 +--------+-------+----------------+-----------------+---------------+
 | 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
 | 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
 | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
 | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
 +--------+-------+----------------+-----------------+---------------+
 */
-- still too many suspects, check third interview
SELECT *
FROM phone_calls
WHERE year = 2021
    AND MONTH = 7
    AND DAY = 28
    AND duration <= 60;
/*
 +-----+----------------+----------------+------+-------+-----+----------+
 | id  |     caller     |    receiver    | year | month | day | duration |
 +-----+----------------+----------------+------+-------+-----+----------+
 | 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
 | 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
 | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
 | 234 | (609) 555-5876 | (389) 555-5198 | 2021 | 7     | 28  | 60       |
 | 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
 | 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
 | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
 | 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
 | 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
 | 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
 +-----+----------------+----------------+------+-------+-----+----------+
 */
-- culprit must match with the phonenumber, i wish i could save sql-queries in variables
SELECT *
FROM (
        SELECT *
        FROM people
        WHERE license_plate IN (
                SELECT license_plate
                FROM bakery_security_logs
                WHERE year = 2021
                    AND MONTH = 7
                    AND DAY = 28
                    AND HOUR BETWEEN 10 AND 11
                    AND MINUTE BETWEEN 15 AND 25
            )
        INTERSECT
        SELECT *
        FROM people
        WHERE id IN (
                SELECT person_id
                FROM bank_accounts
                WHERE account_number IN (
                        SELECT account_number
                        FROM atm_transactions
                        WHERE year = 2021
                            AND MONTH = 7
                            AND DAY = 28
                            AND transaction_type = "withdraw"
                            AND atm_location = "Leggett Street"
                    )
            )
    )
WHERE phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year = 2021
            AND MONTH = 7
            AND DAY = 28
            AND duration <= 60
    );
/*
 +--------+-------+----------------+-----------------+---------------+
 |   id   | name  |  phone_number  | passport_number | license_plate |
 +--------+-------+----------------+-----------------+---------------+
 | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
 | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
 +--------+-------+----------------+-----------------+---------------+
 */
-- no way, still to many suspects. guess i have to check the flights
SELECT *
FROM flights
WHERE year = 2021
    AND MONTH = 7
    AND DAY = 29
ORDER BY HOUR;
/*
 +----+-------------------+------------------------+------+-------+-----+------+--------+
 | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
 +----+-------------------+------------------------+------+-------+-----+------+--------+
 | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
 | 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
 | 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
 | 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
 | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
 +----+-------------------+------------------------+------+-------+-----+------+--------+
 */
-- take first flight: id = 36, compare passengerlist to suspectlist
SELECT *
FROM (
        SELECT *
        FROM (
                SELECT *
                FROM people
                WHERE license_plate IN (
                        SELECT license_plate
                        FROM bakery_security_logs
                        WHERE year = 2021
                            AND MONTH = 7
                            AND DAY = 28
                            AND HOUR BETWEEN 10 AND 11
                            AND MINUTE BETWEEN 15 AND 25
                    )
                INTERSECT
                SELECT *
                FROM people
                WHERE id IN (
                        SELECT person_id
                        FROM bank_accounts
                        WHERE account_number IN (
                                SELECT account_number
                                FROM atm_transactions
                                WHERE year = 2021
                                    AND MONTH = 7
                                    AND DAY = 28
                                    AND transaction_type = "withdraw"
                                    AND atm_location = "Leggett Street"
                            )
                    )
            )
        WHERE phone_number IN (
                SELECT caller
                FROM phone_calls
                WHERE year = 2021
                    AND MONTH = 7
                    AND DAY = 28
                    AND duration <= 60
            )
    )
WHERE passport_number IN (
        SELECT passport_number
        FROM passengers
        WHERE flight_id = 36
    );
/*
 +--------+-------+----------------+-----------------+---------------+
 |   id   | name  |  phone_number  | passport_number | license_plate |
 +--------+-------+----------------+-----------------+---------------+
 | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
 +--------+-------+----------------+-----------------+---------------+
 */
-- it's BRUCE!!!!
-- ok where is flight 36 heading to?
SELECT destination_airport_id
FROM flights
WHERE year = 2021
    AND MONTH = 7
    AND DAY = 29
ORDER BY HOUR
LIMIT 1;
SELECT city
FROM airports
WHERE id = (
        SELECT destination_airport_id
        FROM flights
        WHERE year = 2021
            AND MONTH = 7
            AND DAY = 29
        ORDER BY HOUR
        LIMIT 1
    );
/*
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
 */
-- on the way to LaGuardia
-- who did he talked to in the morning? Bruce id = 686048, phone number = (367) 555-5533
SELECT *
FROM people
    JOIN phone_calls ON people.phone_number = receiver
    AND year = 2021
    AND MONTH = 7
    AND DAY = 28
    AND caller = '(367) 555-5533'
    AND duration < 60;
/*
 +--------+-------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+
 |   id   | name  |  phone_number  | passport_number | license_plate | id  |     caller     |    receiver    | year | month | day | duration |
 +--------+-------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+
 | 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
 +--------+-------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+
 */
 -- and Robin is the accomplice, i knew it all along