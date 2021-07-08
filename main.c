#include "front.h"

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
    #include <time.h>
    if (argc != 2) {
        return ARG_ERROR;
    }

    FILE * csv;
    csv = fopen(argv[1], "r");
    if (csv == NULL) {
        handleErrors(FILE_ERROR, NULL);
    }

    ERROR_CODE k = NO_ERROR;

    // Crea el objeto de queries para ser loadeado
    Queries queries;
    time_t s1End, s1Start = clock();
    k = loadAllQueries(&queries);
    handleErrors(k, &queries);
    s1End = clock();

    time_t s2End, s2Start = clock();
    k = parseAndInsert(csv, &queries);
    handleErrors(k, &queries);
    s2End = clock();

    int c = fclose(csv);
    if (c != 0) {
        k = FILE_ERROR;
        handleErrors(k, &queries);
    }

    time_t s3End, s3Start = clock();
    k = writeAllQueries(&queries);
    handleErrors(k, &queries);
    s3End = clock();

    time_t s4End, s4Start = clock();
    freeAllQueries(&queries);
    s4End = clock();

    printf("%-8s|%-8s|%-8s|%-8s\n", "Load", "Insert", "Write", "Free");
    printf("%-8f|%-8f|%-8f|%-8f", (double)(s1End - s1Start)/CLOCKS_PER_SEC, (double)(s2End - s2Start)/CLOCKS_PER_SEC, (double)(s3End - s3Start)/CLOCKS_PER_SEC, (double)(s4End - s4Start)/CLOCKS_PER_SEC);

    #endif
}
