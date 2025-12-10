#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Representa una línea de la "lista de rangos frescos" de la base de datos.
// Ejemplo: "3-5" significa que los ingredientes 3, 4 y 5 son válidos para la cena.
struct Interval {
    long long start;
    long long end;
};

// Una "sección organizativa" para poner orden en el complicado nuevo sistema de gestión.
// Ayuda a los Elfos a no tener que leer toda la lista cada vez que miran un ingrediente.
struct Node {
    long long center;               // El ID de ingrediente que usamos como referencia para dividir el trabajo.
    vector<Interval> overlapping;   // Rangos de frescura que pasan justo por este punto central.
    Node *left = nullptr;           // Referencia a los rangos de IDs más bajos (a la izquierda del almacén).
    Node *right = nullptr;          // Referencia a los rangos de IDs más altos (a la derecha del almacén).

    // Cuando terminamos de clasificar la comida, cerramos esta sección del sistema.
    ~Node() {
        delete left;
        delete right;
    }
};

// Función donde los Elfos organizan la base de datos caótica en algo navegable.
// Toman la lista masiva de rangos frescos y la estructuran para consultas rápidas.
Node* buildTree(const vector<Interval> &intervals) {
    if (intervals.empty()) return nullptr;

    // 1. Miramos el ID más bajo y el más alto para entender la magnitud del inventario.
    long long min_val = intervals[0].start;
    long long max_val = intervals[0].end;

    for (const Interval& range : intervals) {
        if (range.start < min_val) min_val = range.start;
        if (range.end > max_val) max_val = range.end;
    }

    // Elegimos un "punto medio" en el inventario para dividir la pila de datos en dos.
    long long center = min_val + (max_val - min_val) / 2;

    Node* node = new Node();
    node->center = center;

    // Listas temporales para separar los papeles de la base de datos.
    vector<Interval> left_intervals;
    vector<Interval> right_intervals;

    // 2. Clasificamos cada regla de frescura respecto a nuestro punto medio.
    for (const Interval& range : intervals) {
        if (range.end < center) {
            // Este rango de ingredientes frescos está en la sección de números bajos.
            left_intervals.push_back(range);
        } else if (range.start > center) {
            // Este rango de ingredientes frescos está en la sección de números altos.
            right_intervals.push_back(range);
        } else {
            // Este rango cruza justo por el medio, lo guardamos aquí para tenerlo a mano.
            // (Ejemplo: el rango 12-18 cruza por el 15).
            node->overlapping.push_back(range);
        }
    }

    // 3. Los Elfos siguen organizando recursivamente las pilas de la izquierda y la derecha hasta que todo el sistema de inventario está ordenado.
    node->left = buildTree(left_intervals);
    node->right = buildTree(right_intervals);

    return node;
}

// Un Elfo toma un ingrediente (ID) y verifica si está fresco.
bool isFresh(Node* node, long long id) {
    if (node == nullptr) return false; // Si llegamos aquí y no hay reglas, asumimos que está podrido.

    // 1. Revisamos las reglas de frescura que tenemos a mano en esta sección (las que se solapan).
    for (const Interval& range : node->overlapping) {
        // ¿El ID del ingrediente cae dentro de este rango válido?
        // Ejemplo: Si tengo el ingrediente 17 y el rango es 16-20.
        if (id >= range.start && id <= range.end) {
            return true; // ¡Es fresco! Podemos usarlo para la cena.
        }
    }

    // 2. Si no hay suerte, decidimos hacia qué lado del archivo seguir buscando.
    if (id < node->center) {
        // El ID es bajo, consultamos las reglas archivadas a la izquierda.
        return isFresh(node->left, id);
    } else {
        // El ID es alto, consultamos las reglas archivadas a la derecha.
        return isFresh(node->right, id);
    }
}

int main() {
    // Apertura fichero.
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error: No encontramos la base de datos de la cocina." << endl;
        return 1;
    }

    vector<Interval> freshRanges;        // La lista de reglas sobre qué rangos son frescos.
    vector<long long> availableIngredients; // Los ingredientes físicos que tenemos en la cocina.
    string line;
    bool parsingRanges = true; // Empezamos leyendo las reglas (parte superior del archivo).

    // --- LECTURA DEL INPUT ---
    while (getline(file, line)) {
        if (line.empty()) {
            parsingRanges = false; // La línea en blanco separa las reglas del inventario.
            continue;
        }

        if (parsingRanges) {
            // Leyendo rangos frescos.
            // Desde el ID 'start' hasta el 'end' son seguros para comer.
            size_t guion = line.find('-');
            long long start = stoll(line.substr(0, guion));
            long long end = stoll(line.substr(guion + 1));
            freshRanges.push_back({start, end}); // Nuevo intervalo al final de freshRanges.
        } else {
            // Lee el inventario.
            availableIngredients.push_back(stoll(line));
        }
    }
    file.close();

    cout << "Informe leido: " << freshRanges.size() << " reglas de frescura, " 
         << availableIngredients.size() << " ingredientes para revisar." << endl;
    
    
    
        // --- PROCESAMIENTO INVENTARIO ---
    
    // 1. Los Elfos organizan las reglas para no tardar una eternidad buscando.
    Node* root = buildTree(freshRanges);

    // 2. Revisamos cada ingrediente disponible en la cocina uno por uno.
    int freshCount = 0;
    for (long long id : availableIngredients) {
        // Consultamos al sistema ordenado si este ingrediente específico es bueno.
        if (isFresh(root, id)) {
            freshCount++; // Uno más
        }
        // Si no es fresco, es un ingrediente podrido y lo descartamos (no incrementamos el contador).
    }

    cout << "Cantidad de ingredientes frescos: " << freshCount << endl;


    delete root;

    return 0;
}