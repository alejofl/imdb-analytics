#ifndef __Q123ADT_H__

#define __Q123ADT_H__

#include "../queries.h"

typedef struct query123CDT * query123ADT;

// Datos que contiene el vector de query 1
typedef struct dataQ1
{
    size_t year;
    size_t movies;
    size_t series;
} DataQ1;

// Datos que contiene el vector de query 2
typedef struct dataQ2
{
    size_t year;
    String genre;
    size_t count;
} DataQ2;

// Datos que contiene el vector de query 3
typedef struct dataQ3{
    size_t year;
    String movieTitle;
    size_t movieVotes;
    float movieRating;
    String serieTitle;
    size_t serieVotes;
    float serieRating;
} DataQ3;


/*
        Crea una nuevo TAD de los tres primeros queries
        @param error: Setea el flag con algun valor del enum ERROR_CODE en caso de error en ejecucion
        @return query123ADT
 */
query123ADT newQuery123(ERROR_CODE * error);

/*
        Se encarga de agregar la pelicula/serie pasada por parametro al TAD para que luego sea utilizada por cada query
        @param q: La instancia de query123ADT
        @param entry: Puntero a la estructura de una pelicula/serie
        @param error: Setea el flag con algun valor del enum ERROR_CODE en caso de error en ejecucion
 */
void insertQ123(query123ADT q, Entry * entry, ERROR_CODE * error);

/*
        Devuelve la cantidad de años diferentes que contenian las peliculas/series agregadas al TAD
        @param q: La instancia de query123ADT
        @return cant. de años
 */
size_t yearCount(const query123ADT q);

/*
        Devuelve la cantidad de generos en todos los años que contenian las peliculas/series agregadas al TAD
        @param q: La instancia de query123ADT
        @return cant. de generos totales
 */
size_t genresCount(const query123ADT q);

/*
        Libera todos los recursos del TAD
        @param q: La instancia de query123ADT
 */
void freeQuery123(query123ADT q);

// ------------------------------------------------ Query 1 -------------------------------------------------------
/*
        Crea el vector para el query 1 con todos los elementos del csv principal ya agregados
        @param q: La instancia de query123ADT
        @param error: Setea el flag con algun valor del enum ERROR_CODE en caso de error en ejecucion
        @return: El vector ordenado por año de manera descendiente
 */
DataQ1 * finalVecQ1(const query123ADT q, ERROR_CODE * error);

/*
        Libera los recursos del vector final del query 1 del heap
        @param vec: El vector obtenido en finalVecQ1
 */
void freeFinalVecQ1(DataQ1 * vec);

// ------------------------------------------------ Query 2 ------------------------------------------------------
/*
        Crea el vector para el query 2 con todos los elementos del csv principal ya agregados
        @param q: La instancia de query123ADT
        @param error: Setea el flag con algun valor del enum ERROR_CODE en caso de error en ejecucion
        @return: El vector ordenado por año de manera descendiente y ordenado por género alfabeticamente
 */
DataQ2 * finalVecQ2(const query123ADT q, ERROR_CODE * error);

/*
        Libera los recursos del vector final del query 2 del heap
        @param vec: El vector obtenido en finalVecQ2
 */
void freeFinalVecQ2(DataQ2 * vec, size_t dim);


// ------------------------------------------------ Query 3 ------------------------------------------------------
/*
        Crea el vector para el query 3 con todos los elementos del csv principal ya agregados
        @param q: La instancia de query123ADT
        @param error: Setea el flag con algun valor del enum ERROR_CODE en caso de error en ejecucion
        @return: El vector ordenado por año de manera descendiente
 */
DataQ3 * finalVecQ3(const query123ADT q, ERROR_CODE * error);

/*
        Libera los recursos del vector final del query 3 del heap
        @param vec: El vector obtenido en finalVecQ3
 */
void freeFinalVecQ3(DataQ3 * vec, size_t dim);

#endif
