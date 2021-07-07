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

/*
ERROR_CODE getlines(FILE * file, Queries * queries) {
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
            Entry * recording = malloc(sizeof(Entry));
            token = strtok(s, separator);
            while (token != NULL) {
                if (!heading) {
                    //TODO aca falta chequear lo que devuelva copyStr cuando se arregle
                    switch (column) {
                        case 1:
                            recording->titleType = copyStr(token);
                            if (recording->titleType == NULL) {
                                return MEM_ERROR;
                            }
                            column++;
                            break;
                        case 2:
                            recording->primaryTitle = copyStr(token);
                            if (recording->primaryTitle == NULL) {
                                return MEM_ERROR;
                            }
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
//                            insertQueries(recording, queries);
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
*/

// Libera los strings que se almacena en una variable de tipo Entry
void freeRecordingStrings(Entry * recording){
    free(recording->titleType);
    free(recording->primaryTitle);
    // Debo liberar todos los generos guardados (cada uno de ellos es un string)
    for(size_t i = 0; recording->genres[i] != NULL; i++) {
        free(recording->genres[i]);
    }
    free(recording->genres);
}

ERROR_CODE getlines(FILE * file, Queries * queries) {
    Entry recording;
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
            if(heading == 1){
                heading = 0;
            } else {
                char * token;
                char separator[2] = ";";
                int column = 1;
                ERROR_CODE err;
                token = strtok(s, separator);
                while (token != NULL) {
                    //TODO aca falta chequear lo que devuelva copyStr cuando se arregle
                    switch (column) {
                        case 1:
                            recording.titleType = copyStr(token);
                            if (recording.titleType == NULL) {
                                return MEM_ERROR;
                            }
                            break;
                        case 2:
                            recording.primaryTitle = copyStr(token);
                            if (recording.primaryTitle == NULL) {
                                return MEM_ERROR;
                            }
                            break;
                        case 3:
                            recording.startYear = atol(token);
                            break;
                        case 4:
                            if (strcmp(token, "\\N") == 0) {
                                recording.endYear = 0;
                            } else {
                                recording.endYear = atol(token);
                            }
                            break;
                        case 5:
                            // Estas llaves son usadas para poder declarar variables en este case.
                            {
                                String * genres = makeGenresVector(token, &err);
                                if (err == MEM_ERROR) {
                                    return MEM_ERROR;
                                }
                                recording.genres = genres;
                            }
                            break;
                        case 6:
                            recording.averageRating = atof(token);
                            break;
                        case 7:
                            recording.numVotes = atol(token);
                            break;
                        case 8:
                            if (strcmp(token, "\\N") == 0) {
                                recording.runtimeMinutes = 0;
                            } else {
                                recording.runtimeMinutes = atol(token);
                            }
                            // TODO falta hacer esta función y despues también hacer lo del MEM_ERROR.
                            // insertQueries(&recording, queries);
                            break;
                        default:
                            break;
                    }
                    column++;
                    token = strtok(NULL, separator);
                }
                // Libera los strings guardados en la estructura del recording para poder reutilizar la variable
                freeRecordingStrings(&recording);
            }
        }
    }
    return NO_ERROR;
}


void handleMemoryError(ERROR_CODE k) {
    if (k == MEM_ERROR) {
        fprintf(stderr, BHRED "Something's went wrong." HRED " There's not enough memory for this request.\n" reset);
        exit(MEM_ERROR);
    }
}

// use pointers for struct communication between functions
ERROR_CODE writeQ4(DataQ4* data, FILE *f) {
    int res = fprintf(f, "%lu;%s;%lu;%.1f\n", data->startYear, data->title, data->votes, data->rating);
    if (res < 0) {
        return FILE_ERROR;
    }
    return NO_ERROR;
}
