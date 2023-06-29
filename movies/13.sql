SELECT name
FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE stars.movie_id IN
(SELECT movies.id
FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id=people.id
WHERE people.name='Kevin Bacon' and people.birth=1958)
AND people.name !='Kevin Bacon';