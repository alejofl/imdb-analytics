#include "../queries.h"

#ifndef __Q4ADT_H__

#define __Q4ADT_H__

typedef struct dataQ4
{
    String title;
    size_t votes;
    float rating;
    size_t startYear;
} DataQ4;

typedef struct query4CDT *query4ADT;

query4ADT newQuery4(void);

ERROR_CODE insertQ4(query4ADT q, Movie *m); // Recibe un pointer a la estructura movie para ser mas eficiente. Devuelve 1 si se realizo la operacion correctamente y 0 si hubo error.

DataQ4 *finalVecQ4(query4ADT q); // Devuelve un vector de estructuras de DataQ4

void freeQueryQ4(query4ADT q);

#endif
