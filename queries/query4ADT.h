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

/* 
    Crea el ADT de las top 100 mejores peliculas
    @param err Parametro de salida del codigo de error
    @return query4ADT
*/
query4ADT newQuery4(ERROR_CODE *err);

/*
    Inserta una pelicula en el ADT. Solo mantiene las top 100
    @param q la instancia del query4
    @param m pointer a la estructura de una pelicula/serie
    @param err Parametro de salida del codigo de error
*/
void insertQ4(query4ADT q, Entry *m, ERROR_CODE *err);

/*
    Devuelve un vector de las top 100 mejores peliculas
    @param q la instancia de query4
    @param err parametro de salida del codigo de error
    @return DataQ4* el tamaño de DataQ4 esta dada por topCount
*/
DataQ4 *finalVecQ4(const query4ADT q, ERROR_CODE *err);

/*
    Limpia el query4
    @param q la instancia de query4
*/
void freeQueryQ4(query4ADT q);

/*
    Obtiene la cantidad de peliculas en el top
    @param vec vector de DataQ4
    @param dim tamaño del vec
*/
void freeFinalVecQ4(DataQ4 * vec, int dim);

/*
    Obtiene la cantidad de peliculas en el top
    @param q la instancia de query4
    @return size_t cantidad de peliculas en query4 guardadas
*/
size_t topCount(const query4ADT q);

#endif
