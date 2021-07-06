#include "./query4ADT.h"

typedef struct recording
{
    String title;
    size_t votes;
    float rating;
    size_t startYear;
    struct recording * next;
} Recording;

typedef struct query4CDT
{
    Recording * movies;
} query4CDT;
