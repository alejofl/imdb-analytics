#include "../queries.h"

#ifndef __Q1ADT_H__

#define __Q1ADT_H__

typedef struct dataQ1
{
    size_t year;
    size_t movies;
    size_t series;
} DataQ1;

typedef struct query1CDT * query1ADT;

// Aclaracion: ERROR_CODE * status sirve para indicar si hubo un error al alojar espacio en el heap

// Creo un nuevo TAD del tipo de query1
query1ADT newQuery1(ERROR_CODE * status);

// Inserta una nueva pelicula o serie al TAD
void insertQ1(query1ADT q, Movie * m, ERROR_CODE * status);

// Crea el vector con todos los elementos del csv principal ya agregados al TAD
DataQ1 * finalVecQ1(query1ADT q, ERROR_CODE * status);

// Libera los recursos del TAD
void freeQueryQ1(query1ADT q);

#endif
