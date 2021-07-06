#include "../queries.h"

#ifndef __Q3ADT_H__

#define __Q3ADT_H__

typedef struct dataQ3{
    size_t year;
    String movieTitle;
    size_t movieVotes;
    float movieRating;
    String serieTitle;
    size_t serieVotes;
    float serieRating;
} DataQ3;

typedef struct query3CDT * query3ADT;

query3ADT newQuery3(void);

void insertQ3(query3ADT q, Movie m);

DataQ3 * finalVecQ3(query3ADT q);       // Devuelve un vector de estructuras de DataQ3

void freeQueryQ3(query3ADT q);

#endif
