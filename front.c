//
// Created by Alejo Flores on 06/07/2021.
//

#include "front.h"

String * makeGenresVector(String s, ERROR_CODE * err) {
    String * rta = NULL;
    int i = 0, dim = 0, j;
    char aux[50];
    for (j = 0; s[i] != '\0'; i++) {
        if (s[i] != ',') {
            aux[j] = s[i];
            j++;
        } else {
            aux[j] = '\0';
            if (dim % STR_BLOCK == 0) {
                errno = 0;
                rta = realloc(rta, (dim + STR_BLOCK) * sizeof(String));
                if (errno == ENOMEM) {
                    *err = MEM_ERROR;
                    return NULL;
                }
            }
            errno = 0;
            rta[dim] = malloc(j+1);
            if (errno == ENOMEM) {
                *err = MEM_ERROR;
                return NULL;
            }
            strcpy(rta[dim], aux);
            j = 0;
            dim++;
        }
    }
    aux[j] = '\0';
    errno = 0;
    rta = realloc(rta, (dim + 2) * sizeof(String));
    if (errno == ENOMEM) {
        *err = MEM_ERROR;
        return NULL;
    }
    rta[dim] = malloc(j+1);
    if (errno == ENOMEM) {
        *err = MEM_ERROR;
        return NULL;
    }
    strcpy(rta[dim], aux);
    rta[dim + 1] = NULL;
    return rta;
}

ERROR_CODE getlines(FILE * file) {
    errno = 0;
    char * s = malloc(MAX_LINE);
    if (errno == ENOMEM) {
        return MEM_ERROR;
    }
    int c, heading = 1, i = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c != '\n') {
            s[i] = c;
            i++;
        } else {
            s[i] = '\0';
            i = 0;

            char * token;
            char separator[2] = ";";
            int column = 1;
            ERROR_CODE err;
            Movie * recording = malloc(sizeof(Movie));
            token = strtok(s, separator);
            while (token != NULL) {
                if (!heading) {
                    //TODO aca falta chequear lo que devuelva copyStr cuando se arregle
                    switch (column) {
                        case 1:
                            recording->titleType = copyStr(token);
                            column++;
                            break;
                        case 2:
                            recording->primaryTitle = copyStr(token);
                            column++;
                            break;
                        case 3:
                            recording->startYear = atol(token);
                            column++;
                            break;
                        case 4:
                            if (strcmp(token, "\\N") == 0) {
                                recording->endYear = 0;
                            } else {
                                recording->endYear = atol(token);
                            }
                            column++;
                            break;
                        case 5:
                            // Estas llaves son usadas para poder declarar variables en este case.
                            {
                                String * genres = makeGenresVector(token, &err);
                                if (err == MEM_ERROR) {
                                    return MEM_ERROR;
                                }
                                recording->genres = genres;
                                column++;
                             }
                            break;
                        case 6:
                            recording->averageRating = atof(token);
                            column++;
                            break;
                        case 7:
                            recording->numVotes = atol(token);
                            column++;
                            break;
                        case 8:
                            if (strcmp(token, "\\N") == 0) {
                                recording->runtimeMinutes = 0;
                            } else {
                                recording->runtimeMinutes = atol(token);
                            }
                            //TODO falta hacer esta función y despues también hacer lo del MEM_ERROR.
//                            insertQueries(recording);
                            puts("HOLAA8");
                            column = 1;
                            break;
                        default:
                            break;
                    }
                } else {
                    if (column < 8) {
                        column++;
                    } else {
                        heading = 0;
                    }
                }
                token = strtok(NULL, separator);
            }
        }
    }
    return NO_ERROR;
}

// use pointers for struct communication between functions
ERROR_CODE writeQ4(DataQ4* data, FILE *f) {
    int res = fprintf(f, "%lu;%s;%lu;%.1f\n", data->startYear, data->title, data->votes, data->rating);
    if (res < 0) {
        return FILE_ERROR;
    }
    return NO_ERROR;
}