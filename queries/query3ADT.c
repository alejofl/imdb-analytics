#include "./query3ADT.h"

typedef struct Recording
{
    String title;
    size_t votes;
    float rating;
} Recording;

typedef struct year
{
    size_t year;
    Recording maxMovie;
    Recording maxSerie;
    struct year * next;
} Year;

typedef struct query3CDT
{
    size_t size;
    Year * years;
} query3CDT;

query3ADT newQuery3(ERROR_CODE * err) {
    errno = 0;
    query3ADT q = calloc(1, sizeof(struct query3CDT));
    if (errno == ENOMEM) {
        *err = MEM_ERROR;
        return NULL;
    }
    *err = NO_ERROR;
    return q;
}

void insertQ3(query3ADT q, Entry * m, ERROR_CODE * err) {
    int flag = 0;
    q->years
}

DataQ3 * finalVecQ3(query3ADT q, ERROR_CODE * err);       // Devuelve un vector de estructuras de DataQ3

void freeQueryQ3(query3ADT q);