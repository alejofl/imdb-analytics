#include "../queries.h"

typedef struct dataQ4{
    String title;
    size_t votes;
    float rating;
    size_t startYear;
} DataQ4; 

typedef struct query4CDT * query4ADT;

query4ADT newQuery4(void);

void insertQ4(query4ADT q, Movie m);

DataQ4 * finalVecQ4(query4ADT q);       // Devuelve un vector de estructuras de DataQ4

void freeQueryQ4(query4ADT q);
    