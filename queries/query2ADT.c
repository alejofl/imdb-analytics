typedef struct genre
{
    String genre;
    size_t count;
    struct genre *next;
} Genre;

typedef struct year
{
    size_t year;
    Genre *genre;
    struct year *next;
} Year;

struct query2CDT
{
    Year *years;
};
