#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Estructura para guardar los datos
struct Intervalo {
    long long inicio;
    long long fin;
};

/*************** CLASE PRINCIPAL DEL ÁRBOL DE INTERVALOS *****************/
class ArbolDeIntervalos {
private:
    struct Nodo {
        long long centro;   // Valor pivote para dividir el árbol
        vector<Intervalo> solapados;    // Intervalos que pasan justo por el centro
        Nodo* izquierdo;
        Nodo* derecho;


        Nodo(long long c) {
            centro = c;
            izquierdo = nullptr;
            derecho = nullptr;
        }
    };

    Nodo* raiz;

    /***************** Función para construir el árbol *****************/
    Nodo* construirArbol(const vector<Intervalo>& listaIntervalos) {
        // Caso base: si no hay intervalos, no hay nodo
        if (listaIntervalos.empty()) {
            return nullptr;
        }

        // Buscamos el mínimo y máximo para encontrar el centro
        long long min_val = listaIntervalos[0].inicio;
        long long max_val = listaIntervalos[0].fin;

        for (size_t i = 1; i < listaIntervalos.size(); i++) {
            if (listaIntervalos[i].inicio < min_val) min_val = listaIntervalos[i].inicio;
            if (listaIntervalos[i].fin > max_val) max_val = listaIntervalos[i].fin;
        }

        long long centro = min_val + (max_val - min_val) / 2;

        // Creación del nodo centro
        Nodo* nuevoNodo = new Nodo(centro);

        // Separamos los intervalos en 3 grupos
        vector<Intervalo> izq, der;

        for (size_t i = 0; i < listaIntervalos.size(); i++) {
            Intervalo inter = listaIntervalos[i];
            if (inter.fin < centro) {
                izq.push_back(inter); // Va totalmente a la izquierda
            } else if (inter.inicio > centro) {
                der.push_back(inter); // Va totalmente a la derecha
            } else {
                nuevoNodo->solapados.push_back(inter); // Pasa por el centro
            }
        }

        // Construimos los hijos
        nuevoNodo->izquierdo = construirArbol(izq);
        nuevoNodo->derecho = construirArbol(der);

        return nuevoNodo;
    }

    /***************** Función de búsqueda *******************/
    bool buscarRecursivo(Nodo* nodo, long long id) {
        // Caso base: si el nodo está vacío, no hemos encontrado nada
        if (nodo == nullptr) return false;

        // Mirar si el ID está en los intervalos de ESTE nodo
        for (size_t i = 0; i < nodo->solapados.size(); i++) {
            if (id >= nodo->solapados[i].inicio && id <= nodo->solapados[i].fin) {
                return true; // Encontrado, está fresco
            }
        }

        // Si no está, decidimos si bajar a la izquierda o derecha
        if (id < nodo->centro) {
            return buscarRecursivo(nodo->izquierdo, id);
        } else {
            return buscarRecursivo(nodo->derecho, id);
        }
    }

    /***************** Función para liberar memoria *******************/
    void borrarArbol(Nodo* nodo) {
        if (nodo == nullptr) return;
        
        borrarArbol(nodo->izquierdo);
        borrarArbol(nodo->derecho);
        
        delete nodo; // Importante para evitar memory leaks
    }

public:
    // Constructor
    ArbolDeIntervalos() {
        raiz = nullptr;
    }

    // Destructor
    ~ArbolDeIntervalos() {
        borrarArbol(raiz);
    }

    // Método público para cargar datos
    void cargarDatos(const vector<Intervalo>& reglas) {
        raiz = construirArbol(reglas);
    }

    // Método público para consultar
    bool ingredienteFresco(long long id) {
        return buscarRecursivo(raiz, id);
    }
};



int main() {
    ifstream archivo("input.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el fichero" << endl;
        return 1;
    }

    vector<Intervalo> reglas;
    vector<long long> inventario;
    string linea;
    bool leyendoReglas = true;

    // Lectura del fichero
    while (getline(archivo, linea)) {
        if (linea.empty()) {
            leyendoReglas = false;
            continue;
        }

        if (leyendoReglas) {
            // Buscamos el guión para separar inicio y fin
            size_t guion = linea.find('-');
            long long inicio = stoll(linea.substr(0, guion));
            long long fin = stoll(linea.substr(guion + 1));
            reglas.push_back({inicio, fin});
        } else {
            inventario.push_back(stoll(linea));
        }
    }
    archivo.close();

    // Instanciamos nuestra estructura de datos 
    ArbolDeIntervalos gestorFrescura;
    
    // Construcción del árbol
    gestorFrescura.cargarDatos(reglas);

    // Procesamos el inventario y contamos frescos
    int contadorFrescos = 0;
    for (size_t i = 0; i < inventario.size(); i++) {
        long long ingrediente = inventario[i];
        
        // Llamada a la función de consulta
        if (gestorFrescura.ingredienteFresco(ingrediente)) {
            contadorFrescos++;
        }
    }

    cout << "Resultado final: " << contadorFrescos << " ingredientes frescos." << endl;

    return 0;

}