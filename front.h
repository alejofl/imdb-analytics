//
// Created by Alejo Flores on 06/07/2021.
//

#ifndef __FRONT_H__
#define __FRONT_H__

#include "queries.h"
#include "queries/query1ADT.h"
#include "queries/query2ADT.h"
#include "queries/query3ADT.h"
#include "queries/query4ADT.h"

ERROR_CODE getlines(FILE * file); // Función usada para parsear el archivo
ERROR_CODE writeQ4(DataQ4* data, FILE *f); // Función usada para escribir el archivo. Abrir con APPEND

#endif
