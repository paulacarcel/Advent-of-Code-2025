
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    unsigned long long tot = 0; //long long para evitar overflow, pueden ser números grandes

    while (cin >> line) {
        int n = line.size();

        int best = 0;
        for (int i = 0; i < n - 1; i++) {
            char first = line[i];
            char secondMax = '0';
            for (int j = i + 1; j < n; j++) {
                if (line[j] > secondMax) {
                    secondMax = line[j];
                }
            }
            int value = 10 * (first - '0') + (secondMax - '0'); //convierte el carácter en número (por ejemplo, '8' → 8)
            if (value > best) best = value;
        }

        tot += best;
    }

    cout << "tot : " << tot << "\n";
    return 0;
}
