SELECT DISTINCT people.name FROM people
INNER JOIN stars on people.id=stars.person_id
INNER JOIN movies on movies.id=stars.movie_id
WHERE movies.year = 2004
order by people.birth