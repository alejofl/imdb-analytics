typedef struct Recording
{
    String title;
    size_t votes;
    float rating;
} Recording;

typedef struct year
{
    size_t year;
    Recording maxMovie;
    Recording maxSerie;
    struct year *next;
} Year;

struct query2CDT
{
    Year *years;
};
