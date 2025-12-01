
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("d01.txt");
    if (!file) {
        cerr << "No se pudo abrir d01.txt\n";	//Detecta si existe el fichero 
        return 1;
    }

    int pos = 50;        // Posición inicial
    int countZero = 0;   // Cuántas veces termina en 0 que será la contraseña
    string linea;

    while (file >> linea) {
        char letra = linea[0];  // L o R
        int num = 0;

        // Convertir el resto de la cadena en número
        for (size_t i = 1; i < linea.size(); i++) {
            if (linea[i] >= '0' && linea[i] <= '9') {
                num = num * 10 + (linea[i] - '0');
            }
        }

        // Aplicar movimiento
        if (letra == 'L') { 	//L resta el valor numérico
            pos = (pos - num) % 100;
            if (pos < 0) pos += 100; // Corregir negativos
        } else if (letra == 'R') { //R suma el valor numérico
            pos = (pos + num) % 100;
        }

        // Contar si está en 0
        if (pos == 0) {
            countZero++; //Actualiza el valor, finalmente su valor será la contraseña
        }
    }

    cout << "Password: " << countZero << "\n";
    return 0;
}

