// #include "../queries.h"
// #include "../queries/query3ADT.h"
// #include "../queries/query4ADT.h"
// #include "../front.h"

// void testingQ1() {
//     Entry data = {"movie", "m1", 2021, 2022, NULL, 10.1, 100, 10000};
//     Entry data2 = {"tvSerie", "m2", 2021, 2022, NULL, 10.1, 150, 10000};
//     Entry data3 = {"movie", "m3", 1999, 2022, NULL, 10.1, 135, 10000};
//     Entry data4 = {"tvSerie", "m4", 1999, 2022, NULL, 10.1, 222, 10000};
//     Entry data5 = {"movie", "m5", 2021, 2022, NULL, 10.1, 103, 10000};
//     Entry data6 = {"tvSerie", "m6", 1999, 2022, NULL, 10.1, 225, 10000};

//     ERROR_CODE err = NO_ERROR;
//     query1ADT q = newQuery1(&err);

//     insertQ1(q, &data, &err);
//     insertQ1(q, &data2, &err);
//     insertQ1(q, &data3, &err);
//     insertQ1(q, &data4, &err);
//     insertQ1(q, &data5, &err);
//     insertQ1(q, &data6, &err);

//     size_t size = countQ1(q);
//     DataQ1* vec = finalVecQ1(q, &err);
//     FILE* q1 = fopen("query1.csv", "w");

//     writeQueryLoop(vec, (ERROR_CODE (*) (char*, FILE *))writeQ1, (void (*)(void*, int))freeFinalVecQ1, q1, sizeof(DataQ1), size);
    
//     free(vec);
//     freeQueryQ1(q);
// }

// void testingQ3() {
//     Entry data = {"movie", "m1", 2021, 2022, NULL, 10.1, 100, 10000};
//     Entry data2 = {"tvSerie", "m2", 2021, 2022, NULL, 10.1, 150, 10000};
//     Entry data3 = {"movie", "m3", 1999, 2022, NULL, 10.1, 135, 10000};
//     Entry data4 = {"tvSerie", "m4", 1999, 2022, NULL, 10.1, 222, 10000};
//     Entry data5 = {"movie", "m5", 2021, 2022, NULL, 10.1, 103, 10000};
//     Entry data6 = {"tvSerie", "m6", 1999, 2022, NULL, 10.1, 225, 10000};

//     ERROR_CODE err = NO_ERROR;
//     query3ADT q = newQuery3(&err);

//     insertQ3(q, &data, &err);
//     insertQ3(q, &data2, &err);
//     insertQ3(q, &data3, &err);
//     insertQ3(q, &data4, &err);
//     insertQ3(q, &data5, &err);
//     insertQ3(q, &data6, &err);

//     size_t size = q3Size(q);
//     DataQ3 * vec = finalVecQ3(q, &err);
//     FILE* q3 = fopen("query3.csv", "w");
    
//     writeQueryLoop(vec, (ERROR_CODE (*) (char*, FILE *))writeQ3, (void (*)(void*, int))freeFinalVecQ3, q3, sizeof(DataQ3), size);

//     freeFinalVecQ3(vec, size);
//     freeQueryQ3(q);
// }

// void testingQ4() {
//     ERROR_CODE err = NO_ERROR;
//     query4ADT q = newQuery4(&err);

//     for (int i = 0; i <120; i += 1) {
//         Entry data2 = {"movie", "Marcelo", 2021, 2022, NULL, i / 10.0, 1000001, 10000};
//         insertQ4(q, &data2, &err);
//     }

//     size_t top = topCount(q);
//     DataQ4* vec = finalVecQ4(q, &err);
//     FILE* q4 = fopen("query4.csv", "w");
//     writeQueryLoop(vec, (ERROR_CODE (*) (char*, FILE *))writeQ4, (void (*)(void*, int))freeFinalVecQ4, q4, sizeof(DataQ4), top);
    
//     fclose(q4);
//     free(vec);
//     freeQueryQ4(q);
// }


// void testingQ2() {
//     String genero1[] = {"Drama", "Thriller", NULL};
//     String genero3[] = {"Romance" , NULL};
//     String genero5[] = {"Terror" , NULL};
//     Entry data = {"movie", "m1", 2021, 2022, genero1, 10.1, 100, 10000};
//     Entry data3 = {"movie", "m3", 1999, 2022, genero3, 10.1, 135, 10000};
//     Entry data5 = {"movie", "m5", 2021, 2022, genero5, 10.1, 103, 10000};
//     Entry data6 = {"movie", "m5", 2021, 2022, genero1, 10.1, 103, 10000};

//     ERROR_CODE err = NO_ERROR;
//     query2ADT q = newQuery2(&err);

//     insertQ2(q, &data, &err);
//     insertQ2(q, &data3, &err);
//     insertQ2(q, &data5, &err);
//     insertQ2(q, &data6, &err);

//     size_t size = countQ2(q);
//     DataQ2 * vec = finalVecQ2(q, &err);
//     FILE* q2 = fopen("query2.csv", "w");
    
//     writeQueryLoop(vec, (ERROR_CODE (*) (char*, FILE *))writeQ2, (void (*)(void*, int))freeFinalVecQ2, q2, sizeof(DataQ2), size);

//     freeFinalVecQ2(vec, size);
//     freeQueryQ2(q);
// }
