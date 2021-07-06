//
// Created by Alejo Flores on 06/07/2021.
//

#include "front.h"

int getlines(FILE * file) {
    errno = 0;
    char * s = malloc(MAX_LINE);
    if (errno == ENOMEM) {
        return MEM_ERROR;
    }
    int c, i = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c != '\n') {
            s[i] = c;
            i++;
        } else {
            s[i] = '\0';
            i = 0;

            char * token;
            char separator[2] = ";";
            int heading = 1, column = 1;
            Movie * recording = malloc(sizeof(Movie));
            token = strtok(s, separator);
            while (token != NULL) {
                if (!heading) {
                    switch (column) {
                        case 1:
                            recording->titleType =
                    }
                }

                token = strtok(NULL, separator);
            }
        }
    }
}
