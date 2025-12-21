
// -------------------------------------------------
//  PARTE 2: TIMELINES (GRAFO + PROGRMACIÓN DINÁMICA)
// -------------------------------------------------

//El objetivo es contar el número de caminos que salen del mapa desde el punto 'S', siguiendo las reglas dadas por los caracteres del mapa.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAXR = 2000; //Máximo de filas
const int MAXC = 2000; //Máximo de columnas

string mapa[MAXR];                 //Interpretamos el mapa como un array de strings
long long ways[MAXC], next_ways[MAXC]; //Definimos estas variables para el conteo de caminos con programación dinámica

int main() {
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Error al abrir input.txt\n";
        return 1;
    }

    //Leemos todas las filas del mapa del archivo de entrada antes de cerrarlo
    int R = 0;
    while (infile >> mapa[R]) R++;
    infile.close();

    //Comprobamos si hay filas, si no las hay, no hay caminos
    if (R == 0) { 
        cout << 0 << "\n"; 
        return 0; 
    }
    int C = (int)mapa[0].size(); //Número de columnas

    //Buscamos 'S'en el mapa, que será el punto de partida por donde buscaremos los "haces", el nodo inicial desde el que salen todos los caminos

    int sr = -1, sc = -1; //posición de 'S'(Sfila, Scolumna)
    for (int r = 0; r < R && sr == -1; r++) { //r será la fila actual, debe ser menor que R y no haberse encontrado 'S' aún
        //Verificamos que todas las filas tengan el mismo ancho, para evitar errores
        if ((int)mapa[r].size() != C) { 
            cerr << "Filas de distinta longitud.\n"; 
            return 1; 
        }
        //Buscamos 'S' en la fila r
        for (int c = 0; c < C; c++) {
            if (mapa[r][c] == 'S') { //Guardamos la posición de 'S' en las variables sr y sc
                sr = r; 
                sc = c; 
                break; 
            }
        }
    }
    //Si no se encontró 'S', terminar con "error"
    if (sr == -1) { 
        cerr << "No se encontró S\n"; 
        return 1; 
    }

    //Si 'S' está en la última fila, la partícula “sale” por abajo en 1 camino
    if (sr + 1 >= R) { 
        cout << 1 << "\n"; 
        return 0; 
    }

    //Usamos programación dinámica para contar los caminos que salen del mapa
    // ways[c] será el número de caminos que llegan a la columna c (índice de columna) en la fila actual
    // next_ways[c] será el número de caminos que llegarán posteriormente a la columna c, desde el punto actual en el que nos encontramos 

    for (int c = 0; c < C; c++){ //Inicializar a 0 los caminos en todas las columnas
        ways[c] = 0; 
    }
    ways[sc] = 1; //Debajo de 'S' entra un único camino por la misma columna, ya que es el punto de partida

    long long cronog = 0; //Acumula el nº total de caminos que salen del mapa

    //Recorrido por niveles (fila a fila), para ver cómo se distribuyen los caminos desde la fila de 'S' hasta la última fila
    for (int r = sr + 1; r < R; r++) {
        //Limpiar acumulación de la siguiente fila, para empezar de cero en cada fila
        for (int c = 0; c < C; c++) next_ways[c] = 0;

        //Transición de caminos según el contenido de (r, c)
        for (int c = 0; c < C; c++) {
            long long w = ways[c]; //Guardamos el número de caminos que llegan al punto en el que estamos
            if (w == 0) continue;  //Si no llega ninguno, saltamos al siguiente

            if (mapa[r][c] == '^') { //Si hay '^' en (r, c), entonces el camino se bifurca, pues tenemos dos opciones, ir a la izquierda (c-1) o derecha (c+1)
                //Hacia c-1 y cabe en el mapa, sumamos w caminos allí
                if (c - 1 >= 0) next_ways[c - 1] += w;
                //Si se sale del mapa por la izquierda, le sumamos esos caminos a cronog, ya que cuentan como salidos
                else cronog = cronog + w;
                //Misma lógica para la derecha
                //Hacia c+1 y cabe en el mapa, sumamos w caminos allí
                if (c + 1 < C) next_ways[c + 1] += w;
                //Si se sale del mapa por la derecha, le sumamos esos caminos a cronog
                else cronog = cronog + w;

            } else {
                //Si no hay '^', no hay bifurcación: el camino sigue recto por la misma columna, buscando una posición en la que sí que haya '^' o hasta salir por abajo
                next_ways[c] = next_ways[c] + w;
            }
        }

        //Al avanzar a la siguiente fila: actualizamos ways
        for (int c = 0; c < C; c++){
            ways[c] = next_ways[c];
        }
    }

    //Al terminar, todo lo que queda en la última fila "sale por abajo",es decir, se suma a cronog pues son caminos que han salido del mapa
    for (int c = 0; c < C; c++){
        cronog += ways[c];
    }
    //Imprimir el total de caminos que han salido del mapa, cronog
    cout << cronog << "\n";
    return 0;
}
