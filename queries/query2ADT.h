#include "../queries.h"

typedef struct dataQ2
{
    size_t year;
    String genre;
    size_t count;
} DataQ2;

typedef struct query2CDT * query2ADT;

query2ADT newQuery2(void);

void insertQ2(query2ADT q, Movie m);

DataQ2 * finalVecQ2(query2ADT q);       // Devuelve un vector de estructuras de DataQ2

void freeQueryQ2(query2ADT q);