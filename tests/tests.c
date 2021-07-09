#include <time.h>
#include "tests.h"

void timing_test(FILE* csv) {

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
    writeQueryLoop(vec, (ERROR_CODE (*) (char*, FILE *))writeQ4, (void (*)(void*, int))freeFinalVecQ4, q4, sizeof(DataQ4), top);
    
    fclose(q4);
    free(vec);
    freeQueryQ4(q);
}
