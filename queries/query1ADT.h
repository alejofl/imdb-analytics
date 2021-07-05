#include "../queries.h"

typedef struct dataQ1
{
    size_t year;
    size_t movies;
    size_t series;
} DataQ1;

typedef struct query1CDT * query1ADT;

query1ADT newQuery1(void);

void insertQ1(query1ADT q, Movie m);

DataQ1 * finalVecQ1(query1ADT q);

void freeQueryQ1(query1ADT q);