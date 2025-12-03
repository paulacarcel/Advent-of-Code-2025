
#include <iostream>
#include <string>

using namespace std;

int main() {
    const int K = 12;
    string line;
    unsigned long long tot = 0;

    while (cin >> line) {
        int n = (int)line.size();

        string digits;
        digits.reserve(K);

        int first = 0;
        int restantes = K;

        while (restantes > 0) {
            int end = n - (restantes - 1); // límite para empezar a buscar porque detrás quedan menos de 12 dígitos

            // busca el mayor dígito entre first y end
            char best = '0';
            int pos = first;
            for (int i = first; i < end; ++i) {
                if (line[i] > best) {
                    best = line[i];
                    pos = i;
                }
            }

            digits.push_back(best); //añade el elemento al final de la lista digits
            first = pos + 1; 
            restantes--;
        }

        unsigned long long value = 0;
        for (char c : digits) {
            value = value * 10 + (c - '0');
        }
        tot += value;
    }

    cout << "tot : " << tot << "\n";
    return 0;
}
