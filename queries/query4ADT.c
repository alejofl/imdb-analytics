#include "./query4ADT.h"

#define MAX 100
#define CUTOFF 100000

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

query4ADT newQuery4(ERROR_CODE *err)
{
    query4ADT aux = calloc(1, sizeof(query4CDT));
    if (errno == ENOMEM)
    {
        *err = MEM_ERROR;
    }
    return aux;
}

// it receives a pointer to the movie object so its more efficient while passing arguments between functions
static Recording *insertRecQ4(Recording *rec, Movie *movie, ERROR_CODE *err)
{
    int c = rec->rating - movie->averageRating;
    if (rec == NULL || c > 0 || (c == 0 && rec->votes > movie->numVotes))
    {
        Recording *new = malloc(sizeof(Recording));
        if (errno == ENOMEM)
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

// receives a movie struct and inserts it in the query ranking the top 100 highest rankings
// when it gets to 100, it removes the last one from the ranking
void insertQ4(query4ADT q, Movie *m, ERROR_CODE *err)
{
    if (strcasecmp(m->titleType, "movie") != 0 || m->numVotes < CUTOFF)
        return;

    if (q->count == MAX)
    {
        int c = q->movies->rating - m->averageRating;
        if (c > 0 || (c == 0 && q->movies->votes > m->numVotes)) // dont add if its lower than the lowest movie
            return;
        Recording *aux = q->movies;
        q->movies = aux->next;
        freeRecording(aux); // because the rating of movie is higher, remove the first movie
    }

    q->movies = insertRecQ4(q->movies, m, err);
    if (*err == MEM_ERROR)
        return;
    if (q->count < MAX)
        q->count += 1;
}

DataQ4 *finalVecQ4(const query4ADT q, ERROR_CODE *err)
{
    DataQ4 *vec = malloc(sizeof(DataQ4) * q->count);
    if (errno == ENOMEM)
    {
        *err = MEM_ERROR;
        return NULL;
    }

    Recording *curr = q->movies;
    for (int i = q->count - 1; i >= 0; i -= 1)
    {
        vec[i] = (DataQ4){curr->title, curr->votes, curr->rating, curr->startYear};
        curr = curr->next;
    }
    return vec;
}

static void freeRecQ4(Recording *rec)
{
    if (rec != NULL)
    {
        freeRecQ4(rec->next);
        freeRecording(rec);
    }
}

void freeQueryQ4(query4ADT q)
{
    freeRecQ4(q->movies);
    free(q);
}

size_t topCount(const query4ADT q)
{
    return q->count;
}