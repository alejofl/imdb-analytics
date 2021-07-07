#ifndef __Q123ADT_H__

#define __Q123ADT_H__

#include "../queries.h"

typedef struct query123CDT * query123ADT;

typedef struct dataQ1
{
    size_t year;
    size_t movies;
    size_t series;
} DataQ1;

typedef struct dataQ2
{
    size_t year;
    String genre;
    size_t count;
} DataQ2;

typedef struct dataQ3{
    size_t year;
    String movieTitle;
    size_t movieVotes;
    float movieRating;
    String serieTitle;
    size_t serieVotes;
    float serieRating;
} DataQ3;

void insertQ123(query123ADT q, Entry * m, ERROR_CODE *error);
size_t yearCount(const query123ADT q);
size_t genresCount(const query123ADT q);
void freeQuery123(query123ADT q);

// ------------------------------------------------ Query 1 -------------------------------------------------------
static void insertQ1(Year *year, Entry* entry, ERROR_CODE *err);


/*
        Crea el vector con todos los elementos del csv principal ya agregados al TAD
        @param q: La instancia de query1
        @param status: Setea el flag con algun valor del enum ERROR_CODE en caso de error en ejecucion
        @return: El vector ordenado por año de manera descendiente
 */
DataQ1 * finalVecQ1(const query123ADT q, ERROR_CODE * status);

/*
        Libera los recursos del vector final del heap
        @param vec: El vector obtenido en finalVecQ1
 */
void freeFinalVecQ1(DataQ1 * vec);

// ------------------------------------------------ Query 2 ------------------------------------------------------
static void insertQ2(Year *year, Entry* entry, ERROR_CODE *err, int *addedGenre);
DataQ2 * finalVecQ2(const query123ADT q, ERROR_CODE *error);       // Devuelve un vector de estructuras de DataQ2
void freeFinalVecQ2(DataQ2 * vec, size_t dim);


// ------------------------------------------------ Query 3 ------------------------------------------------------
static void insertQ3(Year *year, Entry* entry, ERROR_CODE *err);
DataQ3 * finalVecQ3(const query123ADT q, ERROR_CODE * err);       // Devuelve un vector de estructuras de DataQ3
void freeFinalVecQ3(DataQ3 * vec, size_t dim);

#endif
