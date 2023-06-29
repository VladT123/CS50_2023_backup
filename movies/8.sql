SELECT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies on movies.id = stars.movie_id
WHERE movies.title = 'Toy Story';