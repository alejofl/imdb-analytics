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

/*
        Crea un nuevo TAD del tipo de query1
        @param status: Setea el flag con algun valor del enum ERROR_CODE en caso de error en ejecucion
        @return query1ADT
 */
query1ADT newQueryQ1(ERROR_CODE * status);


/*
        Inserta una nueva pelicula o serie al TAD
        @param q: La instancia de query1
        @param m: Puntero a la estructura de una pelicula/serie
        @param status: Setea el flag con algun valor del enum ERROR_CODE en caso de error en ejecucion
 */
void insertQ1(query1ADT q, Entry * m, ERROR_CODE * status);


/*
        Crea el vector con todos los elementos del csv principal ya agregados al TAD
        @param q: La instancia de query1
        @param status: Setea el flag con algun valor del enum ERROR_CODE en caso de error en ejecucion
 */
DataQ1 * finalVecQ1(const query1ADT q, ERROR_CODE * status);


/*
       Libera los recursos del TAD
       @param q: La instancia de query1
 */
void freeQueryQ1(query1ADT q);

#endif
