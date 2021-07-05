#include "./query1ADT.h"

typedef struct year
{
    size_t year;
    size_t movies;
    size_t series;
    struct year * next;
} Year;

typedef struct query1CDT
{
    Year * years;
} query1CDT;
