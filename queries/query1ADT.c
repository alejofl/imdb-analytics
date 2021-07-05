typedef struct year
{
    size_t year;
    size_t movies;
    size_t series;
    struct year *next;
} Year;

struct query1CDT
{
    Year *years;
};
