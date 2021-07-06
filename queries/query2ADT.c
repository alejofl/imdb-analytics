#include "./query2ADT.h"

typedef struct genre
{
    String genre; //el genero
    size_t count; //cantidad de películas con ese genero
    struct genre * next; //tail al siguiente genero
} Genre;

typedef struct year
{
    size_t year; //El año en el que estoy
    Genre * genre; //una lista donde cada nodo es una estructura que posee el genero y la cantidad de peliculas con ese genero
    struct year * next; //tail al siguiente año
} Year;

typedef struct query2CDT
{
    size_t cantGenres; //para saber la cantidad total de generos, para luego hacer el vector que devolvemos con mas facilidad
    Year * years; /*Una lista donde el nodo contiene el año, una lista con los generos
                    y la tail al siguiente*/
} query2CDT;

//Creo el tad para hacer el query2
query2ADT newQuery2(ERROR_CODE *error){
    //hago un flag para ver si cuando hago el calloc me tira un error o no
    errno = 0;
    //asigno la meemoria para la nueva query
    query2ADT new = calloc(1, sizeof(query2CDT));
    //checkeo a ver si el flag me tiro error, si lo hace devuelvo null y devuelvo como parametro que hubo error
    if(errno == ENOMEM){
        *error = MEM_ERROR;
        return NULL;
    }
    //en el puntero pongo que no hubo error y retorno el nuevo tad
    *error = NO_ERROR;
    return new;
}


static Genre * insertGenreRec(Genre * first, Movie * m, char *addedGenre, ERROR_CODE *error, int * idx){
    //creo una variable c para no hacer el strcasecmp varias veces
    int c;
    //Si estaba vacío o si ya tenía que estar y no está lo agrego
    if(first == NULL || (c = strcasecmp(first->genre, m->genres[*idx])) > 0){
        errno = 0;
        Genre * new = malloc(sizeof(Genre));
        //Hago las validaciones a ver si no hubo ningun problema con la memoria
        if(errno == ENOMEM){
            *error = MEM_ERROR;
            return first;
        }
        //Hago el malloc con el strlen asi le guardo la memoria justa para el nombre del género
        new->genre = malloc(strlen(m->genres[*idx]) + 1);
        //Valido nuevamente pero esta vez para el string
        if(errno == ENOMEM){
            *error = MEM_ERROR;
            return first;
        }
        //copio el string de género, pongo el tail hacia el first
        //Inicio el count en 1 ya que por lo menos tengo una película y pongo el flag
        //added genre en 1 para ya saber que lo agregué
        strcpy(new->genre, m->genres[*idx]);
        new->next = first;
        new->count = 1;
        *addedGenre = 1;
        return new;
    }
    if( c == 0){
        //si el género ya esta solo sumo 1 al count y addedgenre no lo toco
        //porque lo inicialicé en 0
        first->count++;
        return first;
    }
    //sigo buscando
    first->next = insertGenreRec(first->next, m, addedGenre, error);
    return first;
}

static Year * insertYearRec(Year * year, Movie * m, char *addedGenre, ERROR_CODE *error){
    if (year == NULL || year->year < m->startYear){
        //pongo el flag para ver si hay 
        errno = 0;
        Year * new = malloc(sizeof(Year));
        if(errno == ENOMEM){
            *error = MEM_ERROR;
            return year;
        }
        // inserto el nuevo año y luego le agrego el género
        new->year = m->startYear;
        new->next = year;
        //Como cada película puede tener varios generos y en el final del vector se pone un NULL voy recorriendo hasta que sea NULL
        int i = 0;
        while (m->genres[i] != NULL)
        {
            new->genre =  insertGenreRec(year->genre, m, addedGenre, error, &i);
            i++;
        }
        return new;
    }
    if (year->year == m->startYear){
        //Si el año ya está pongo directo el/los géneros
        int i = 0;
        while (m->genres[i] != NULL)
        {
            new->genre =  insertGenreRec(year->genre, m, addedGenre, error, &i);
            i++;
        }
        return year;
    }
    //sigo buscando el año
    year->next = insertYearRec(year->next, m, addedGenre, error);
    return year;
}

void insertQ2(query2ADT q, Movie * m, ERROR_CODE *error){
    //Me fijo si se hizo un nuevo genero
    char addedGenre = 0;
    //Meto el nuevo año
    q->years = insertYearRec(q->years, m, &addedGenre, error);
    //Aumento la cantidad de generos totales
    q->cantGenres += addedGenre;
}

DataQ2 * finalVecQ2(const query2ADT q, ERROR_CODE * error){
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
            final[i] = (DataQ2) {
                aux->year,
                auxG->genre,
                auxG->count
            };
            i++;
            auxG = auxG->next;
        }
        aux = aux->next;
    }
}


static void freeGenreRec(Genre * firstG){
    if (firstG == NULL)
        return;
    //Libero el string que dice el género
    free(firstG->genre);
    //Llamo recursivamente al genero
    free(firstG->next);
    //libero el genero
    free(firstG);
}

static void freeYearRec(Year * first){
    if(first == NULL)
        return;
    //libero los generos de ese año
    freeGenreRec(first->genre);
    //llamo recursivamente al proximo año
    freeYearRec(first->next);
    //libero el año
    free(first);
}

void freeQueryQ2(query2ADT q){
    //freeYearRec lo que hace es ir liberando los años
    freeYearRec(q->years);
    //libero el tad
    free(q);
}