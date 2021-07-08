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
    //Aumento la cantidad de generos y años totales
    q->cantGenres += addedGenre;
    q->cantYears += addedYear;
}


// ------------------------------------------------ Query 1 -------------------------------------------------------
static void insertQ1(Year *year, Entry* entry, ERROR_CODE *err) {

}





// ------------------------------------------------ Query 2 ------------------------------------------------------
static void insertQ2(Year *year, Entry* entry, ERROR_CODE *err, int *addedGenre) {

}




// ------------------------------------------------ Query 3 ------------------------------------------------------
static void insertQ3(Year * year, Entry * entry, ERROR_CODE * err) {
    if (strcasecmp("movie", entry->titleType) == 0) {
        if (year->maxMovie.title != NULL) {
            free(year->maxMovie.title);
        }
        year->maxMovie.title = copyStr(entry->primaryTitle);
        if (year->maxMovie.title == NULL) {
            *err = MEM_ERROR;
            return;
        }
        year->maxMovie.rating = entry->averageRating;
        year->maxMovie.votes = entry->numVotes;
    } else {
        if (year->maxSerie.title != NULL) {
            free(year->maxSerie.title);
        }
        year->maxSerie.title = copyStr(entry->primaryTitle);
        if (year->maxSerie.title == NULL) {
            *err = MEM_ERROR;
            return;
        }
        year->maxSerie.rating = entry->averageRating;
        year->maxSerie.votes = entry->numVotes;
    }
}

void freeFinalVecQ3(DataQ3 * vec, size_t dim) {
    for (int i = 0; i < dim; i++) {
        free(vec[i].serieTitle);
        free(vec[i].movieTitle);
    }
    free(vec);
}

DataQ3 * finalVecQ3(query123ADT q, ERROR_CODE * err) {
    errno = 0;
    DataQ3 * vec = malloc(q->cantYears * sizeof(DataQ3));
    if (errno == ENOMEM) {
        *err = MEM_ERROR;
        return NULL;
    }
    Year * auxList = q->years;
    for (int i = 0; i < q->cantYears; i++) {
        vec[i].year = auxList->year;
        vec[i].movieRating = auxList->maxMovie.rating;
        vec[i].movieVotes = auxList->maxMovie.votes;
        vec[i].serieRating = auxList->maxSerie.rating;
        vec[i].serieVotes = auxList->maxSerie.votes;
        if (auxList->maxMovie.title == NULL) {
            vec[i].movieTitle = copyStr("\\N");
        } else {
            vec[i].movieTitle = copyStr(auxList->maxMovie.title);
        }
        if (vec[i].movieTitle == NULL) {
            *err = MEM_ERROR;
            freeFinalVecQ3(vec, i-1);
            return NULL;
        }
        if (auxList->maxSerie.title == NULL) {
            vec[i].serieTitle = copyStr("\\N");
        } else {
            vec[i].serieTitle = copyStr(auxList->maxSerie.title);
        }
        if (vec[i].serieTitle == NULL) {
            *err = MEM_ERROR;
            freeFinalVecQ3(vec, i-1);
            return NULL;
        }
        auxList = auxList->next;
    }
    return vec;
}
// ---------------------------------------------------------------------------------------------------------------

query123ADT newQuery123(ERROR_CODE *error)  {
    errno = 0;
    query123ADT q = calloc(1, sizeof(query123CDT));
    if (errno == ENOMEM) {
        *error = MEM_ERROR;
        return NULL;
    }
    return q;
}

size_t yearCount(const query123ADT q) {
    return q->cantYears;
}

size_t genresCount(const query123ADT q) {
    return q->cantGenres;
}

static void freeGenreRec(Genre * firstG){
    if (firstG == NULL)
        return;
    //Libero el string que dice el género
    free(firstG->genre);
    //Llamo recursivamente al genero
    freeGenreRec(firstG->next);
    //libero el genero
    free(firstG);
}

static void freeYearRec(Year * year){
    if (year == NULL) {
        return;
    }
    freeGenreRec(year->genre);
    free(year->maxMovie.title);
    free(year->maxSerie.title);
    freeYearRec(year->next);
    free(year);
}

void freeQuery123(query123ADT q) {
    freeYearRec(q->years);
    free(q);
}
