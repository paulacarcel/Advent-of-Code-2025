
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("d01.txt"); // ajusta el nombre si tu archivo es d01.txt
    if (!file) {
        cerr << "No se pudo abrir d01.txt\n";
        return 1;
    }

    int pos = 50;              // posición inicial
    long long countZero = 0;   // puede ser grande
    string linea;

    while (file >> linea) {
        char letra = linea[0];  // L o R
        int num = 0;

        // Convierte el resto en número (manteniendo tu estilo)
        for (size_t i = 1; i < linea.size(); i++) {
            if (linea[i] >= '0' && linea[i] <= '9') {
                num = num * 10 + (linea[i] - '0');
            }
        }

        // Cuenta clicks que caen en 0 durante ESTA rotación
        if (letra == 'R') {
            // primer click que cae en 0
            int first = (100 - pos) % 100;
            if (first == 0) first = 100;
            if (num >= first) {
                countZero += 1 + (num - first) / 100;
            }
            pos = (pos + num) % 100;
        } else if (letra == 'L') {
            int first = pos % 100;
            if (first == 0) first = 100;
            if (num >= first) {
                countZero += 1 + (num - first) / 100;
            }
            pos = (pos - num) % 100;
            if (pos < 0) pos += 100; // por si el % da negativo
        }
        // IMPORTANTE: ya NO sumamos otra vez si pos == 0
    }

    cout << "Password: " << countZero << "\n";
    return 0;
}

