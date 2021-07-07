//
// Created by Alejo Flores on 06/07/2021.
//

#ifndef __FRONT_H__
#define __FRONT_H__

#include "queries.h"
#include "colors.h"
#include "queries/query1ADT.h"
#include "queries/query2ADT.h"
#include "queries/query3ADT.h"
#include "queries/query4ADT.h"

#define MAX_LINE 360    // titleType: 25, primaryTitle: 100, startYear: 4, endYear: 4,
                        // genres: 200, averageRating: 3, numVotes: 9, runtimeMinutes: 6

typedef struct {
    query1ADT q1;
    query2ADT q2;
    query3ADT q3;
    query4ADT q4;
} Queries;

void handleErrors(ERROR_CODE k, Queries * q);
ERROR_CODE parseAndInsert(FILE * file, Queries * queries); // Función usada para parsear el archivo
ERROR_CODE insertQueries(Entry * recording, Queries * queries); //Función que llama a cada insert de los ADTs según corresponda
void freeAllQueries(Queries * queries);
ERROR_CODE writeQ4(DataQ4* data, FILE *f); // Función usada para escribir el archivo de query4.
ERROR_CODE writeQ2(DataQ2* data, FILE *f); //IDEM anterior pero para query2
ERROR_CODE writeQ1(DataQ1* data, FILE *f); //IDEM anterior pero para query1
ERROR_CODE writeQ3(DataQ3* data, FILE *f); //IDEM anterior pero para query3
ERROR_CODE writeAllQueries(Queries *q);
ERROR_CODE loadAllQueries(Queries *q);
ERROR_CODE writeQueryLoop(void* vec, ERROR_CODE (*write)(char*, FILE*), void (*freeVec)(void*, int), FILE* file, int size, int dim);

void freeFinalVecQ1(DataQ1 *v, int dim);
#endif
