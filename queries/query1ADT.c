#include "./query1ADT.h"

typedef struct year
{
    size_t year;        // Almacena el año
    size_t movies;      // Almacena la cantidad de pelis en un año
    size_t series;      // Almacena la cantidad de series en un año
    struct year * next; // Apunta al siguiente nodo
} Year;

typedef struct query1CDT
{
    size_t size;        // Indica la cantidad de años registrados en el csv
    Year * years;       // Una lista donde cada nodo reperesenta un año con su respectiva cantidad de peliculas
                        // y series
} query1CDT;

// Creo un nuevo TAD del tipo de query1
query1ADT newQuery1(ERROR_CODE * status){
    errno = 0;
    // Alojo espacio en el espacio para el TAD
    query1ADT q1 = calloc(1, sizeof(query1CDT));
    // Si no fue capaz de reservar espacio, indico en el flag que hubo un error de memoria y devuelvo NULL
    if(errno == ENOMEM){
        *status = MEM_ERROR;
        return NULL;
    }
    // Si no hubo problema, mando por el flag que todo salio bien y devuelvo el TAD
    *status = NO_ERROR;
    return q1;
}

// Agrega de manera recursiva una pelicula o serie a su respectivo año
static Year * insertQ1Rec(Year * first, Movie * m, ERROR_CODE * status, size_t * newYear){
    // Si llegue al final de la lista o si el año de la pelicula o serie es mas reciente al del nodo actual,
    // quiere decir que aun no se agrego nada al año correspondiente a m por lo que tengo que crear el nodo
    // de dicho año
    if(first == NULL || first->year < m->startYear){
        errno = 0;
        // Alojo espacio en el heap para el nuevo nodo
        Year * aux = malloc(sizeof(Year));
        // Si no fue capaz de reservar espacio, indico en el flag que hubo un error de memoria y devuelvo
        // la lista como estaba
        if(errno == ENOMEM){
            *status = MEM_ERROR;
            return first;
        }
        // Si no hubo problema, completo el nodo con el año
        aux->year = m->startYear;
        // Si m es una pelicula, seteo campo movie del nodo en 1 y de series en 0
        // Si m es una serie, sera al reves
        if(strcasecmp(m->titleType, "movie") == 0){
            aux->movies = 1;
            aux->series = 0;
        } else {
            aux->movies = 0;
            aux->series = 1;
        }
        // Luego, asigno al tail del nuevo nodo lo que quedaba en la lista (si era el ultimo, sera NULL; sino
        // sera algún año anterior al de m->startYear)
        aux->next = first;
        // Actualizo el flag de que se agrego un nuevo año a la lista
        *newYear = 1;
        // Indico que no hubo problema con la memoria
        *status = NO_ERROR;
        // Devuelvo el nuevo nodo con el resto de la lista
        return aux;
    }
    // Si el año del nodo actual es igual al de la pelicula o serie que quiero agregar, entonces solo tengo
    // que actualizar el contador de movies o series, respectivamente
    if(first->year == m->startYear){
        if(strcasecmp(m->titleType, "movie") == 0){
            first->movies++;
        } else {
            first->series++;
        }
        // Indico que no hubo problema con la memoria
        *status = NO_ERROR;
        // Devuelvo el nodo actualizado
        return first;
    }
    // Si llegue a este punto, quiere decir que el año del nodo actual es mas reciente al de m por lo que
    // tengo que seguir pasando por la lista
    first->next = insertQ1Rec(first->next, m, status, newYear);
    // Devuelvo la lista como haya quedado luego de haber llegado al punto de m
    return first;
}

// Inserta una nueva pelicula o serie al TAD
void insertQ1(query1ADT q, Movie * m, ERROR_CODE * status){
    // Creo un flag que me va a indicar si se agrego un nuevo año
    size_t newYear = 0;
    // Luego, llamo a una funcion recursiva para que agregue al contador del año correspondiente a m
    q->years = insertQ1Rec(q->years, m, status, &newYear);
    // Actualizo el contador del TAD si se agrego una pelicula o serie de un nuevo año
    q->size += newYear;
}

// Crea el vector con todos los elementos del csv principal ya agregados al TAD
DataQ1 * finalVecQ1(query1ADT q, ERROR_CODE * status);

// Libera los recursos del TAD
void freeQueryQ1(query1ADT q);