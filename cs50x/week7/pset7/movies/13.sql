SELECT p.name FROM people AS p
JOIN stars AS s ON p.id = s.person_id JOIN movies AS m ON s.movie_id = m.id
WHERE m.id IN (SELECT m.id FROM movies AS m JOIN stars AS s ON m.id = s.movie_id JOIN people AS p ON s.person_id = p.id WHERE p.name = "Kevin Bacon" AND p.birth = 1958)
AND p.name != "Kevin Bacon";