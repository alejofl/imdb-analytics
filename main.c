#include "queries.h"
#include "colors.h"
#include "front.h"

void testingQ3();
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

    freeAllQueries(&queries);
    printf(HGRN "FINISHED! Four CSV files were saved.\n" reset);
    #endif

    #ifdef DEBUG
    testingQ3();
    testingQ4();
    #endif
}

void testingQ3() {
    Entry data = {"movie", "m1", 2021, 2022, NULL, 10.1, 100, 10000};
    Entry data2 = {"tvSerie", "m2", 2021, 2022, NULL, 10.1, 150, 10000};
    Entry data3 = {"movie", "m3", 1999, 2022, NULL, 10.1, 135, 10000};
    Entry data4 = {"tvSerie", "m4", 1999, 2022, NULL, 10.1, 222, 10000};
    Entry data5 = {"movie", "m5", 2021, 2022, NULL, 10.1, 103, 10000};
    Entry data6 = {"tvSerie", "m6", 1999, 2022, NULL, 10.1, 225, 10000};

    ERROR_CODE err = NO_ERROR;
    query3ADT q = newQuery3(&err);

    insertQ3(q, &data, &err);
    insertQ3(q, &data2, &err);
    insertQ3(q, &data3, &err);
    insertQ3(q, &data4, &err);
    insertQ3(q, &data5, &err);
    insertQ3(q, &data6, &err);

    size_t size = q3Size(q);
    DataQ3 * vec = finalVecQ3(q, &err);


    freeFinalVecQ3(vec, size);
    freeQueryQ3(q);
}

void testingQ4() {
    ERROR_CODE err = NO_ERROR;
    query4ADT q = newQuery4(&err);

    for (int i = 0; i <120; i += 1) {
        Entry data2 = {"movie", "Marcelo", 2021, 2022, NULL, i / 10.0, 1000001, 10000};
        insertQ4(q, &data2, &err);
    }

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
