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

typedef struct {
    query1ADT q1;
    query2ADT q2;
    query3ADT q3;
    query4ADT q4;
} Queries;

void handleMemoryError(ERROR_CODE k);
ERROR_CODE getlines(FILE * file, Queries * queries); // Función usada para parsear el archivo
ERROR_CODE writeQ4(DataQ4* data, FILE *f); // Función usada para escribir el archivo. Abrir con APPEND

#endif
