#include "query123ADT.h"

typedef struct Recording {
    String title;
    size_t votes;
    float rating;
} Recording;

typedef struct genre
{
    String genre;           // El genero
    size_t count;           // Cantidad de películas con ese genero
    struct genre * next;    // Tail al siguiente genero
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


// Se encarga de llamar a las funciones para incluir los datos que cada query necesita del entry recibido
static void insertAll(Year * year, Entry * entry, ERROR_CODE * error, int * addedGenre) {
    insertQ1(year, entry);
    if (*error != NO_ERROR) {
        return;
    }
    insertQ2(year, entry, error, addedGenre);
    if (*error != NO_ERROR) {
        return;
    }
    insertQ3(year, entry, error);
    if (*error != NO_ERROR) {
        return;
    }
}

// Verifica si el año ya existe en la lista; si no es asi, lo agrega y luego incluye los datos de la pelicula/serie
static Year * insertYearRec(Year * year, Entry * entry, ERROR_CODE * error, char * addedYear, int * addedGenre){
    if (year == NULL || year->year < entry->startYear){
        //pongo el flag para ver si hay 
        errno = 0;
        Year * new = calloc(1, sizeof(Year));
        if(errno == ENOMEM){
            *error = MEM_ERROR;
            return year;
        }
        new->year = entry->startYear;
        new->next = year;
        *addedYear = 1;

        insertAll(new, entry, error, addedGenre);
        return new;
    }
    if (year->year == entry->startYear){
        insertAll(year, entry, error, addedGenre);
        return year;
    }
    // Sigo buscando el año
    year->next = insertYearRec(year->next, entry, error, addedYear, addedGenre);
    return year;
}

// Se encarga de agregar la pelicula/serie pasada por parametro al TAD para que luego sea utilizada por cada query
void insertQ123(query123ADT q, Entry * entry, ERROR_CODE * error) {
    //Me fijo si se hizo un nuevo genero
    int addedGenre = 0;
    char addedYear = 0;

    q->years = insertYearRec(q->years, entry, error, &addedYear, &addedGenre);
    //Aumento la cantidad de generos y años totales
    q->cantGenres += addedGenre;
    q->cantYears += addedYear;
}


// ------------------------------------------------ Query 1 -------------------------------------------------------
// Agrega los datos de la pelicula/serie a los campos utilizados por el query 1
static void insertQ1(Year * year, Entry * entry) {
    // Si me pasan una pelicula, incremento el contador de movies
    // En caso contrario (al ya estar validado que es una pelicula o una serie), incremento el contador de series
    if(strcasecmp(m->titleType, "movie") == 0){
        year->movies++;
    } else {
        year->series++;
    }
}

// Crea el vector para el query 1 con todos los elementos del csv principal ya agregados
DataQ1 * finalVecQ1(const query123ADT q, ERROR_CODE * error){
    errno = 0;
    // Creo un vector de los datos a guardar en el archivo query1.csv y la cantidad de elementos es
    // equivalente a la cantidad de nodos (años) creados en la lista
    DataQ1 * vec = malloc(q->cantYears * sizeof(DataQ1));
    // Si no fue capaz de reservar espacio, indico en el flag que hubo un error de memoria y devuelvo NULL
    if(errno == ENOMEM){
        *status = MEM_ERROR;
        return NULL;
    }
    // Asigno los datos de los nodos al vector de manera iterativa empezando por el primer elemento de la lista,
    // o sea, del año más reciente al más viejo
    Year * aux = q->years;
    size_t i = 0;
    while(aux != NULL){
        // Paso los datos del nodo a su correspondiente posicion en el vector
        vec[i] = (DataQ1) {
                .year = aux->year,
                .movies = aux->movies,
                .series = aux->series
        };
        // Paso a la siguiente posicion del vector y al siguiente nodo de la lista
        i++;
        aux = aux->next;
    }
    // Si no hubo problema, mando por el flag que todo salio bien y devuelvo el vector
    *status = NO_ERROR;
    return vec;
}

// Libera los recursos del vector final del query 1 del heap
void freeFinalVecQ1(DataQ1 * vec){
    free(vec);
}



// ------------------------------------------------ Query 2 ------------------------------------------------------
// Se encarga de contabilizar los generos de la pelicula/serie. Si el genero aún no existia, lo agrega
static Genre * insertGenreRec(Genre * first, Entry * entry, ERROR_CODE * error, int * addedGenre, int idx){
    //creo una variable c para no hacer el strcasecmp varias veces
    int c;
    //Si estaba vacío o si ya tenía que estar y no está lo agrego
    if(first == NULL || (c = strcasecmp(first->genre, entry->genres[idx])) > 0){
        errno = 0;
        Genre * new = malloc(sizeof(Genre));
        //Hago las validaciones a ver si no hubo ningun problema con la memoria
        if(errno == ENOMEM){
            *error = MEM_ERROR;
            return first;
        }
        new->genre = copyStr(entry->genres[idx]);
        if(new->genre == NULL){
            *error = MEM_ERROR;
            return first;
        }
        new->next = first;
        new->count = 1;
        *addedGenre += 1;
        return new;
    }
    if( c == 0){
        //si el género ya esta solo sumo 1 al count y addedgenre no lo toco
        //porque lo inicialicé en 0
        first->count++;
        return first;
    }
    //sigo buscando
    first->next = insertGenreRec(first->next, entry, addedGenre, error, idx);
    return first;
}

// Agrega los datos de la pelicula/serie a los campos utilizados por el query 2
static void insertQ2(Year * year, Entry * entry, ERROR_CODE * err, int * addedGenre) {
    int i = 0;
    while(entry->genres[i] !=  NULL){
            year->genre = insertGenreRec(year->genre, entry, err, addedGenre, i);
    }
}

// Crea el vector para el query 2 con todos los elementos del csv principal ya agregados
DataQ2 * finalVecQ2(const query123ADT q, ERROR_CODE * error){
   //le asigno la cantidad de memoria que va a ocupar el vector final
    //la cantidad de indices que va a tener va a ser la cantidad de generos totales
    errno = 0;
    DataQ2 * final = malloc(sizeof(DataQ2) * q->cantGenres);
    if (errno == ENOMEM){
        *error = MEM_ERROR;
        return NULL;
    }
    //Creo un aux para ir recorriendo los años
    Year * aux = q->years;
    size_t i = 0;
    //con el while de afuera recorro los años
    while( aux != NULL){
        //auxiliar para ir recorriendo los generos por año
        Genre * auxG = aux->genre;
        //con este while recorro los generos
        while (auxG != NULL){
            final[i].year = aux->year;
            final[i].count = auxG->count;
            final[i].genre = copyStr(auxG->genre);
            if (final[i].genre ==  NULL){
                freeFinalVecQ2(final, i-1);
                *error = MEM_ERROR;
                return NULL;
            }
            i++;
            auxG = auxG->next;
        }
        aux = aux->next;
    }
    *error = NO_ERROR;
    return final;
}

// Libera los recursos del vector final del query 2 del heap
void freeFinalVecQ2(DataQ2 * vec, size_t dim) {
    for (int i = 0; i < dim; i += 1) {
        free(vec[i].genre);
    }
    free(vec);
}


// ------------------------------------------------ Query 3 ------------------------------------------------------
// Agrega los datos de la pelicula/serie a los campos utilizados por el query 1
static void insertQ3(Year * year, Entry * entry, ERROR_CODE * error) {
    if (strcasecmp("movie", entry->titleType) == 0) {
        if (year->maxMovie.title != NULL) {
            free(year->maxMovie.title);
        }
        year->maxMovie.title = copyStr(entry->primaryTitle);
        if (year->maxMovie.title == NULL) {
            *error = MEM_ERROR;
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
            *error = MEM_ERROR;
            return;
        }
        year->maxSerie.rating = entry->averageRating;
        year->maxSerie.votes = entry->numVotes;
    }
}

// Crea el vector para el query 3 con todos los elementos del csv principal ya agregados
DataQ3 * finalVecQ3(query123ADT q, ERROR_CODE * error) {
    errno = 0;
    DataQ3 * vec = malloc(q->cantYears * sizeof(DataQ3));
    if (errno == ENOMEM) {
        *error = MEM_ERROR;
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
            *error = MEM_ERROR;
            freeFinalVecQ3(vec, i-1);
            return NULL;
        }
        if (auxList->maxSerie.title == NULL) {
            vec[i].serieTitle = copyStr("\\N");
        } else {
            vec[i].serieTitle = copyStr(auxList->maxSerie.title);
        }
        if (vec[i].serieTitle == NULL) {
            *error = MEM_ERROR;
            freeFinalVecQ3(vec, i-1);
            return NULL;
        }
        auxList = auxList->next;
    }
    return vec;
}

// Libera los recursos del vector final del query 2 del heap
void freeFinalVecQ3(DataQ3 * vec, size_t dim) {
    for (int i = 0; i < dim; i++) {
        free(vec[i].serieTitle);
        free(vec[i].movieTitle);
    }
    free(vec);
}

// ---------------------------------------------------------------------------------------------------------------

// Crea una nuevo TAD de los tres primeros queries
query123ADT newQuery123(ERROR_CODE *error)  {
    errno = 0;
    query123ADT q = calloc(1, sizeof(query123CDT));
    if (errno == ENOMEM) {
        *error = MEM_ERROR;
        return NULL;
    }
    return q;
}

// Devuelve la cantidad de años diferentes que contenian las peliculas/series agregadas al TAD
size_t yearCount(const query123ADT q) {
    return q->cantYears;
}

// Devuelve la cantidad de generos en todos los años que contenian las peliculas/series agregadas al TAD
size_t genresCount(const query123ADT q) {
    return q->cantGenres;
}

// Libera los char * que contienen los generos del heap
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

// Libera la lista de los años y sus recursos internos del heap
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

// Libera todos los recursos del TAD
void freeQuery123(query123ADT q) {
    freeYearRec(q->years);
    free(q);
}
