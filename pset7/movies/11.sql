SELECT movies.title FROM movies
INNER JOIN ratings ON movies.id = ratings.movie_id
INNER JOIN stars on movies.id = stars.movie_id
INNER JOIN people on stars.person_id = people.id
WHERE people.name = "Chadwick Boseman"
ORDER BY ratings.rating desc LIMIT 5