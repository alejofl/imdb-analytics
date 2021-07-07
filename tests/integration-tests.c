#include "../queries.h"
#include "../queries/query1ADT.h"
#include "../queries/query2ADT.h"
#include "../queries/query3ADT.h"
#include "../queries/query4ADT.h"
#include "../front.h"

// Libera los strings que se almacena en una variable de tipo Entry
void freeRecordingStrings(Entry * recording);
String * makeGenresVector(String s, ERROR_CODE * err);

ERROR_CODE insertWrapQ1(Entry* ent, query1ADT* q) {
if  (ent->startYear != 0 && (strcasecmp("movie", ent->titleType) == 0 || strcasecmp("tvseries", ent->titleType) == 0)){
        ERROR_CODE err1 = NO_ERROR;
        insertQ1(q, ent, &err1);

        if (err1 == MEM_ERROR) {
            return MEM_ERROR;
        }
    }
    return NO_ERROR;
}

ERROR_CODE insertWrapQ2(Entry* ent, query2ADT* q) {
if  (ent->startYear != 0 && (strcasecmp("movie", ent->titleType) == 0 || strcasecmp("tvseries", ent->titleType) == 0)){
        ERROR_CODE err1 = NO_ERROR;
        if (strcasecmp("movie", ent->titleType) == 0) {
            insertQ2(*q, ent, &err1);
        }
        if (err1 == MEM_ERROR) {
            return MEM_ERROR;
        }
    }
    return NO_ERROR;
}

ERROR_CODE insertWrapQ4(Entry* ent, query4ADT* q) {
if  (ent->startYear != 0 && (strcasecmp("movie", ent->titleType) == 0 || strcasecmp("tvseries", ent->titleType) == 0)){
        ERROR_CODE err1 = NO_ERROR;
        if (strcasecmp("movie", ent->titleType) == 0) {
            insertQ4(*q, ent, &err1);
        }
        if (err1 == MEM_ERROR) {
            return MEM_ERROR;
        }
    }
    return NO_ERROR;
}

ERROR_CODE insertWrapQ3(Entry* ent, query3ADT* q) {
if  (ent->startYear != 0 && (strcasecmp("movie", ent->titleType) == 0 || strcasecmp("tvseries", ent->titleType) == 0)){
        ERROR_CODE err1 = NO_ERROR;
        insertQ3(*q, ent, &err1);

        if (err1 == MEM_ERROR) {
            return MEM_ERROR;
        }
    }
    return NO_ERROR;
}

ERROR_CODE parseAndInsertQuery(FILE * file, void* query, ERROR_CODE (*insert)(Entry*, void*)) {
    Entry recording;
    errno = 0;
    char s[MAX_LINE];
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
                                free(recording.titleType);
                                return MEM_ERROR;
                            }
                            break;
                        case 3:
                            if(strcmp(token, "\\N") == 0){
                                recording.startYear = 0;
                            } else {
                                recording.startYear = atol(token);
                            }
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
                                    freeRecordingStrings(&recording);
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

                            ERROR_CODE k = insert(&recording, query);
                            if (k == MEM_ERROR) {
                                freeRecordingStrings(&recording);
                                return MEM_ERROR;
                            }
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

void integrationTestQ1(const char* f) {
    ERROR_CODE k = NO_ERROR;
    query1ADT q = newQuery1(&k);

    printf(HGRN "Analysing data...\n" reset);

    FILE * csv;
    csv = fopen(f, "r");
    if (csv == NULL) {
        handleErrors(FILE_ERROR, NULL);
    }
    parseAndInsertQuery(csv, q, (ERROR_CODE (*)(Entry*, void*))insertWrapQ1);

    DataQ1* vec1 = finalVecQ1(q, &k);
    if (k != NO_ERROR) return;
    size_t dim = countQ1(q);
    FILE* file = fopen("query1.csv", "w");
    if (file == NULL) {
        free(vec1);
        return ;
    }
    fprintf(file, "year;films;series\n");
    k = writeQueryLoop(vec1, (ERROR_CODE (*) (char*, FILE *))writeQ1, (void (*)(void*, int))freeFinalVecQ1, file, sizeof(DataQ1), dim);
    free(vec1);
    int c = fclose(file);
    if (c != 0) return ;

    freeQueryQ1(q);
    printf(HGRN "FINISHED! query1.\n" reset);
}