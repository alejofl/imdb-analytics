#include "./query4ADT.h"

// organized from lowest to highest, since there is more chance of it being lower rating than higher
// when it reaches 100 movies, all the movies that are lower rating are not added
// if it has to be added, removes the lowest rating
typedef struct recording
{
    String title;
    size_t votes;
    float rating;
    size_t startYear;
    struct recording *next;
} Recording;

typedef struct query4CDT
{
    Recording *movies;
    size_t count;
} query4CDT;

query4ADT newQuery4(void)
{
    return calloc(1, sizeof(query4CDT));
}

// it receives a pointer to the movie object so its more efficient while passing arguments between functions
static Recording *insertRecQ4(Recording *rec, Movie *movie, ERROR_CODE *err)
{
    int c = rec->rating - movie->averageRating;
    if (rec == NULL || c > 0 || (c == 0 && rec->votes > movie->numVotes))
    {
        Recording *new = malloc(sizeof(Recording));
        if (new == NULL)
        {
            *err = MEM_ERROR;
            return rec;
        }
        new->next = rec;
        new->rating = movie->averageRating;
        new->startYear = movie->startYear;
        new->title = copyStr(movie->primaryTitle);
        new->votes = movie->numVotes;
        return new;
    }
    rec->next = insertRecQ4(rec->next, movie, err);
    return rec;
}

static void freeRecording(Recording *rec)
{
    free(rec->title);
    free(rec);
}

ERROR_CODE insertQ4(query4ADT q, Movie *m)
{
    if (strcasecmp(m->titleType, "movie") != 0)
        return;

    ERROR_CODE err = NO_ERROR;
    if (q->count == 100)
    {
        int c = q->movies->rating - m->averageRating;
        if (c > 0 || (c == 0 && q->movies->votes > m->numVotes)) // dont add if its lower than the lowest movie
        {
            return NO_ERROR;
        }
        Recording *aux = q->movies;
        q->movies = aux->next;
        freeRecording(aux); // because the rating of movie is higher, remove the first movie
    }

    q->movies = insertRecQ4(q->movies, m, &err);
    if (err == MEM_ERROR)
        return MEM_ERROR;
    if (q->count < 100)
        q->count += 1;
    return NO_ERROR;
}

DataQ4 *finalVecQ4(query4ADT q); // Devuelve un vector de estructuras de DataQ4

void freeQueryQ4(query4ADT q);