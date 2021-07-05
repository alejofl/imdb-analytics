#include <string.h>
typedef char *String;

/*
titleType: si corresponde a una película, serie de televisión, etc
primaryTitle: Título original
startYear: si es una película, el año. Si es una serie, en qué año comenzó a emitirse
endYear: si es una serie de televisión, en qué año finalizó. 
genres: Lista de géneros separados por coma
averageRating: un número entre 0 y 10, con un decimal
numVotes: cantidad de votos que obtuvo
runtimeMinutes: número entero, indica la duración en minutos. 
*/
typedef struct query1CDT *query1ADT;
typedef struct query2CDT *query2ADT;
typedef struct query3CDT *query3ADT;
typedef struct query4CDT *query4ADT;

typedef struct
{
    String titleType;
    String primaryTitle;
    size_t startYear;
    size_t endYear; // 0 es falta de ano de finalizacion
    String *genres;
    float averageRating;
    size_t numVotes;
    size_t runtimeMinutes;
} Movie;
