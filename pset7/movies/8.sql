SELECT people.name
FROM people INNER JOIN  stars
On people.id=stars.person_id
INNER JOIN movies
ON stars.movie_id IS movies.id
WHERE movies.title IS "Toy Story"