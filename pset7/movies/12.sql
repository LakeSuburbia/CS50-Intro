
SELECT movies.title FROM movies
INNER JOIN stars ON stars.movie_id = movies.id
INNER JOIN people on people.id = stars.person_id
where people.name = "Helena Bonham Carter"
INTERSECT
SELECT movies.title FROM movies
INNER JOIN stars ON stars.movie_id = movies.id
INNER JOIN people on people.id = stars.person_id
where people.name = "Johnny Depp" 