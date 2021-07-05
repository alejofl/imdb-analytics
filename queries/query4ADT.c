typedef struct recording
{
    String title;
    size_t votes;
    float rating;
    size_t startYear;
    struct recording *next;
} Recording;

struct query2CDT
{
    Recording *movies;
};
