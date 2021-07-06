#ifndef __QUERIES_H__

#define __QUERIES_H__

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define STR_BLOCK 5

// TEST 0 is for production
#define TEST 1
#if TEST == 1
#include <assert.h>
#endif

typedef char *String;

// add corresponding error codes when time is correct
typedef enum
{
    NO_ERROR = 0,
    MEM_ERROR = 1
} ERROR_CODE;

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
typedef struct
{
    String titleType;
    String primaryTitle;
    size_t startYear;
    size_t endYear; // 0 es falta de anio de finalizacion
    String *genres;
    float averageRating;
    size_t numVotes;
    size_t runtimeMinutes;
} Movie;

// please check this function CONSIDER MOVING TO ANOTHER header file
// if return value is NULL its because malloc and realloc failed
// dont pass NULL to from
String copyStr(const String from);

#endif
