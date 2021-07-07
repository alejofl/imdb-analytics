#include "query123ADT.h"

typedef struct Recording {
    String title;
    size_t votes;
    float rating;
} Recording;

typedef struct genre
{
    String genre; //el genero
    size_t count; //cantidad de películas con ese genero
    struct genre * next; //tail al siguiente genero
} Genre;

typedef struct year
{
    size_t year;        // Almacena el año
    size_t movies;      // Almacena la cantidad de pelis en un año
    size_t series;      // Almacena la cantidad de series en un año

    Recording maxMovie; // Datos de la pelicula mas votada
    Recording maxSerie; // Datos de la serie mas votada

    Genre * genre;
    struct year * next; // Apunta al siguiente nodo
} Year;

typedef struct query123CDT
{
    size_t cantYears;   // Indica la cantidad de años registrados en el csv
    size_t cantGenres;  // Indica la cantidad de generos en todos los años registrados en el csv
    Year * years;       // Una lista donde cada nodo reperesenta un año
} query123CDT;


static void insertAll(Year *year, Entry* m, ERROR_CODE *error, int *addedGenre) {
    insertQ1(year, m, error);
    if (*error != NO_ERROR) {
        return;
    }
    insertQ2(year, m, error, addedGenre);
    if (*error != NO_ERROR) {
        return;
    }
    insertQ3(year, m, error);
    if (*error != NO_ERROR) {
        return;
    }
}

static Year * insertYearRec(Year * year, Entry * m, ERROR_CODE *error, char *addedYear, int *addedGenre){
    if (year == NULL || year->year < m->startYear){
        //pongo el flag para ver si hay 
        errno = 0;
        Year * new = calloc(1, sizeof(Year));
        if(errno == ENOMEM){
            *error = MEM_ERROR;
            return year;
        }
        new->year = m->startYear;
        new->next = year;
        *addedYear = 1;

        insertAll(new, m, error, addedGenre);
        return new;
    }
    if (year->year == m->startYear){
        insertAll(year, m, error, addedGenre);
        return year;
    }
    //sigo buscando el año
    year->next = insertYearRec(year->next, m, error, addedYear, addedGenre);
    return year;
}

void insertQ123(query123ADT q, Entry * m, ERROR_CODE *error) {
    //Me fijo si se hizo un nuevo genero
    int addedGenre = 0;
    char addedYear = 0;

    q->years = insertYearRec(q->years, m, error, &addedYear, &addedGenre);
    //Aumento la cantidad de generos totales
    q->cantGenres += addedGenre;
}


// ------------------------------------------------ Query 1 -------------------------------------------------------
static void insertQ1(Year *year, Entry* entry, ERROR_CODE *err) {

}





// ------------------------------------------------ Query 2 ------------------------------------------------------
static void insertQ2(Year *year, Entry* entry, ERROR_CODE *err, int *addedGenre) {

}




// ------------------------------------------------ Query 3 ------------------------------------------------------
static void insertQ3(Year *year, Entry* entry, ERROR_CODE *err) {

}
