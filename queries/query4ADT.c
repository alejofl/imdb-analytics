#include "./query4ADT.h"

#define MAX 100
#define DELTA 0.01
#define CUTOFF 100000

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


static void freeRecording(Recording *rec);

query4ADT newQuery4(ERROR_CODE *err)
{
    errno = 0;
    query4ADT aux = calloc(1, sizeof(query4CDT));
    if (errno == ENOMEM)
    {
        *err = MEM_ERROR;
    }
    return aux;
}

// Entry* es un pointer, para que el traspaso entre funciones no pase una copia del struct
static Recording *insertRecQ4(Recording *rec, Entry *movie, ERROR_CODE *err)
{
    float c;
    if (rec == NULL || (c = rec->rating - movie->averageRating) > DELTA || ( fabs(c) <= DELTA && rec->votes >= movie->numVotes))
    {
        errno = 0;
        Recording *new = malloc(sizeof(Recording));
        String copy = copyStr(movie->primaryTitle);
        if (errno == ENOMEM)
        {
            *err = MEM_ERROR;
            return rec;
        }
        new->next = rec;
        new->rating = movie->averageRating;
        new->startYear = movie->startYear;
        new->title = copy;
        new->votes = movie->numVotes;
        return new;
    }
    rec->next = insertRecQ4(rec->next, movie, err);
    return rec;
}

// Guarda los 100 mejores, guardando de menor a mayor. Si llega a los 100, solo guarda los que sean mayores al mas bajo.
void insertQ4(query4ADT q, Entry *m, ERROR_CODE *err)
{
    if (strcasecmp(m->titleType, "movie") != 0 || m->numVotes < CUTOFF)
        return;

    if (q->count == MAX)
    {
        float c = q->movies->rating - m->averageRating;
        if (c > DELTA || ( fabs(c) <= DELTA && q->movies->votes > m->numVotes)) // Si la pelicula m no es de mayor rating que el mas bajo, no hacer nada.
            return;
        Recording *aux = q->movies;
        q->movies = aux->next;
        freeRecording(aux); // Elimina la pelicula de mas bajo rating
    }
    q->movies = insertRecQ4(q->movies, m, err);
    if (*err == MEM_ERROR)
        return;
    if (q->count < MAX)
        q->count += 1;
}

// Devuelve el vector para cargar al csv
DataQ4 *finalVecQ4(const query4ADT q, ERROR_CODE *err)
{
    errno = 0;
    DataQ4 *vec = malloc(sizeof(DataQ4) * q->count);
    if (errno == ENOMEM)
    {
        *err = MEM_ERROR;
        return NULL;
    }

    Recording *curr = q->movies;
    for (int i = q->count - 1; i >= 0; i -= 1)
    {
        String title = copyStr(curr->title);
        if (title == NULL) {
            *err = MEM_ERROR;
            return NULL;
        }
        vec[i] = (DataQ4){title, curr->votes, curr->rating, curr->startYear};
        curr = curr->next;
    }
    return vec;
}

static void freeRecording(Recording *rec)
{
    free(rec->title);
    free(rec);
}

static void freeRecQ4(Recording *rec)
{
    if (rec != NULL)
    {
        freeRecQ4(rec->next);
        freeRecording(rec);
    }
}

void freeFinalVecQ4(DataQ4 * vec, size_t dim) {
    for (int i = 0; i < dim; i += 1) {
        free(vec[i].title);
    }
    free(vec);
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
