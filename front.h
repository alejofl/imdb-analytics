//
// Created by Alejo Flores on 06/07/2021.
//

#ifndef __FRONT_H__
#define __FRONT_H__

#include "queries.h"
#include "colors.h"
#include "queries/query123ADT.h"
#include "queries/query4ADT.h"

#define MAX_LINE 360    // titleType: 25, primaryTitle: 100, startYear: 4, endYear: 4,
                        // genres: 200, averageRating: 3, numVotes: 9, runtimeMinutes: 6

typedef struct {
    query123ADT q1;
    query4ADT q4;
} Queries;

void handleErrors(ERROR_CODE k, Queries * q);
ERROR_CODE parseAndInsert(FILE * file, Queries * queries); // Función usada para parsear el archivo
ERROR_CODE insertQueries(Entry * recording, Queries * queries); // Función que llama a cada insert de los ADTs según corresponda
void freeAllQueries(Queries * queries); // Función encargada de llamar a los free de los TADs
ERROR_CODE writeQ1(DataQ1* data, FILE *f); // Función usada para escribir el archivo de query1
ERROR_CODE writeQ2(DataQ2* data, FILE *f); // IDEM anterior pero para query2
ERROR_CODE writeQ3(DataQ3* data, FILE *f); // IDEM anterior pero para query3
ERROR_CODE writeQ4(DataQ4* data, FILE *f); // IDEM anterior pero para query4
ERROR_CODE writeAllQueries(Queries *q); // Función encargada de escribir las cuatro queries pedidas
ERROR_CODE loadAllQueries(Queries *q); // Función encargada de crear los ADTs

/*
 *
 * @param vec: vector genérico DataQ-
 * @param write: función genérica de escritura en el CSV
 * @param freeVec: función genérica de liberación del vector genérico vec
 * @param file: archivo donde se aplica write
 * @param size: sizeof(dataQ-)
 * @param dim: cantidad de elementos de vec
 * @return: código de error para manejo de errores
 */
ERROR_CODE writeQueryLoop(void* vec, ERROR_CODE (*write)(char*, FILE*), void (*freeVec)(void*, size_t), FILE* file, int size, size_t dim);

#endif
