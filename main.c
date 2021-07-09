#include "front.h"
#include "./tests/tests.h"

int main(int argc, char *argv[]) {
    #ifndef DEBUG
    printf("\n");
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
    
    int c = fclose(csv);
    if (c != 0) {
        k = FILE_ERROR;
        handleErrors(k, &queries);
    }

    k = writeAllQueries(&queries);
    handleErrors(k, &queries);

    freeAllQueries(&queries);
    printf(HGRN "FINISHED! Four CSV files were saved.\n\n" reset);
    #endif

    #ifdef DEBUG
    FILE * csv;
    csv = fopen(argv[1], "r");
    if (csv == NULL) {
        handleErrors(FILE_ERROR, NULL);
    }
    timing_test(csv);
    #endif
}
