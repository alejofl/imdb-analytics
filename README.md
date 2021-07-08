# Trabajo Práctico Final - Julio 2021 - Programación Imperativa

## Integrantes

| Legajo | Nombre y Apellido | Usuario de Github | Nombre en Github |
|--------|-------------------|-------------------|------------------|
| 62293  | Federico Shih     | Federico-Shih     | sh1ft            |
| 62317  | Mariano Agopian   | marianoagopian    | Mariano Agopian  |
| 62618  | Axel Preiti Tasat | AxelPreitiT       | Axel Preiti Tasat|
| 62622  | Alejo Flores Lucey | alejoforeslucey  | Alejo Flores Lucey |

## Compilar

Para compilar el programa se debe contar con GCC.

1. Clonar o descargar el repositorio.
2. Abrir una ventana de terminal en la carpeta del repositorio.
3. Compilar el proyecto con el siguiente comando:

```asm
make all
```

## Ejecutar el programa

Se debe contar con un archivo CSV con datos de filmografías con la siguiente estructura:

* **titleType**: si corresponde a una película, serie de televisión, etc 
* **primaryTitle**: Título original 
* **startYear**: si es una película, el año. Si es una serie, en qué año comenzó a emitirse
* **endYear**: si es una serie de televisión, en qué año finalizó.
* **genres**: Lista de géneros separados por coma
* **averageRating**: un número entre 0 y 10, con un decimal
* **numVotes**: cantidad de votos que obtuvo
* **runtimeMinutes**: número entero, indica la duración en minutos. 

Para ejecutar el programa, ejecutar el siguiente comando en la terminal:

```asm
./imdb <path_to_csv_file>
```

El programa creará (y en caso de existir, soobrescribirá) cuatro archivos CSV con los resultados de las queries:

1. **query1.csv**: Cantidad de películas y series por año, con la estructura `year;films;series`

2. **query2.csv**: Cantidad de películas por año y género, con la estructura `year;genre;films`

3. **query3.csv**: La película y serie con más votos de cada año, con la estructura `startYear;film;votesFilm;ratingFilm;serie;votesSerie;ratingSerie`

4. **query4.csv**: Las 100 películas con mejor calificación, con la estructura `startYear;primaryTitle;numVotes;averageRating`

Los cuatro archivos serán guardados en el mismo directorio que el ejecutable.
