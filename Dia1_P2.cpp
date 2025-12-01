
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("d01.txt"); //Comprobamos la existencia del fichero
    if (!file) {
        cerr << "No se pudo abrir d01.txt\n";
        return 1;
    }

    int pos = 50;              //Posición inicial
    int countZero = 0;   
    string linea;

    while (file >> linea) {
        char letra = linea[0];  //L o R
        int num = 0;

        //Convierte el resto en número 
        for (size_t i = 1; i < linea.size(); i++) {
            if (linea[i] >= '0' && linea[i] <= '9') {
                num = num * 10 + (linea[i] - '0');
            }
        }

        //Cuenta el número de "clicks" que caen en 0 durante ESTA rotación
        if (letra == 'R') { //Sumará el número al que acompañe
            //Primer click que cae en 0
            int first = (100 - pos) % 100;

            if (first == 0) first = 100;
            if (num >= first) {
                countZero += 1 + (num - first) / 100;
            }
            pos = (pos + num) % 100;
        } else if (letra == 'L') { //Restará el número al que acompañe
            int first = pos % 100;

            if (first == 0) first = 100;
            if (num >= first) {
                countZero += 1 + (num - first) / 100;
            }
            pos = (pos - num) % 100;
            if (pos < 0) pos += 100; //Por si el resto da negativo
        }
       
    }

    cout << "Password: " << countZero << "\n";
    return 0;
}
