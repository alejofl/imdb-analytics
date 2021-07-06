#include "../queries.h"

#ifndef __Q2ADT_H__

#define __Q2ADT_H__

typedef struct dataQ2
{
    size_t year;
    String genre;
    size_t count;
} DataQ2;

typedef struct query2CDT * query2ADT;

query2ADT newQuery2(ERROR_CODE *error);

void insertQ2(query2ADT q, Entry*  m, ERROR_CODE *error);

DataQ2 * finalVecQ2(const query2ADT q, ERROR_CODE *error);       // Devuelve un vector de estructuras de DataQ2

void freeQueryQ2(query2ADT q);

#endif
