#include "queries.h"
#include "colors.h"
#include "front.h"

void testingQ4();

int main(int argc, char *argv[]) {
    #ifndef DEBUG
        printf(HYEL "██╗███╗   ███╗██████╗ ██████╗      █████╗ ███╗   ██╗ █████╗ ██╗  ██╗   ██╗███████╗██╗███████╗\n"
           "██║████╗ ████║██╔══██╗██╔══██╗    ██╔══██╗████╗  ██║██╔══██╗██║  ╚██╗ ██╔╝██╔════╝██║██╔════╝\n"
           "██║██╔████╔██║██║  ██║██████╔╝    ███████║██╔██╗ ██║███████║██║   ╚████╔╝ ███████╗██║███████╗\n"
           "██║██║╚██╔╝██║██║  ██║██╔══██╗    ██╔══██║██║╚██╗██║██╔══██║██║    ╚██╔╝  ╚════██║██║╚════██║\n"
           "██║██║ ╚═╝ ██║██████╔╝██████╔╝    ██║  ██║██║ ╚████║██║  ██║███████╗██║   ███████║██║███████║\n"
           "╚═╝╚═╝     ╚═╝╚═════╝ ╚═════╝     ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚═╝   ╚══════╝╚═╝╚══════╝\n\n" reset);

    if (argc != 2) {
        fprintf(stderr, BHRED "Something's not right." HRED " A path to a file must be supplied as argument.\n" reset);
        return ARG_ERROR;
    }

    printf(HGRN "Analysing data...\n" reset);

    FILE * csv;
    csv = fopen(argv[1], "r");
    if (csv == NULL) {
        handleErrors(FILE_ERROR, NULL);
    }

    ERROR_CODE k = NO_ERROR;

    // Crea el objeto de queries para ser loadeado
    Queries queries;
    k = loadAllQueries(&queries);
    handleErrors(k, &queries);
    
    k = parseAndInsert(csv, &queries);
    handleErrors(k, &queries);

    k = writeAllQueries(&queries);
    handleErrors(k, &queries);

    printf("FINISHED!");
    #endif

    #ifdef DEBUG
    testingQ4();
    #endif
}

void testingQ4() {
    Entry data = {"movie", "hola123", 2021, 2022, NULL, 10.1, 1000000, 10000};
    Entry data2 = {"movie", "Marcelo", 2021, 2022, NULL, 10.1, 1000001, 10000};
    ERROR_CODE err = NO_ERROR;
    query4ADT q = newQuery4(&err);

    insertQ4(q, &data, &err);
    insertQ4(q, &data2, &err);
    size_t top = topCount(q);
    DataQ4* vec = finalVecQ4(q, &err);

    FILE* q4 = fopen("query4.csv", "w");
    for (int i = 0; i < top; i += 1) {
        writeQ4(&vec[i], q4);
    }
    fclose(q4);
    free(vec);
    freeQueryQ4(q);
}