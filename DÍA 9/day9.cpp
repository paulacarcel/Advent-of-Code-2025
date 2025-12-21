
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <string>

using ll = long long;

struct Arista {
    ll x1, y1, x2, y2;
};

// ===================== Lectura =====================
bool leer_puntos(const std::string& archivo, std::vector<std::pair<ll,ll>>& puntos) {
    std::ifstream in(archivo);
    if (!in) {
        std::cerr << "No se pudo abrir " << archivo << "\n";
        return false;
    }
    ll x, y; 
    char coma;
    while (in >> x >> coma >> y) {
        if (coma != ',') {
            std::cerr << "Formato inválido (esperaba coma entre x,y)\n";
            return false;
        }
        puntos.emplace_back(x, y);
    }
    return true;
}

// ===================== Geometría básica =====================
static inline bool en_segmento(double px, double py, ll x1, ll y1, ll x2, ll y2) {
    const double EPS = 1e-9;
    if (x1 == x2) { // vertical
        if (std::fabs(px - (double)x1) < EPS) {
            ll lo = std::min(y1, y2);
            ll hi = std::max(y1, y2);
            return (double)lo - EPS <= py && py <= (double)hi + EPS;
        }
    } else if (y1 == y2) { // horizontal
        if (std::fabs(py - (double)y1) < EPS) {
            ll lo = std::min(x1, x2);
            ll hi = std::max(x1, x2);
            return (double)lo - EPS <= px && px <= (double)hi + EPS;
        }
    }
    return false;
}

// Ray casting hacia +∞ en X; si está en el borde, cuenta como dentro.
bool punto_dentro_o_borde(double px, double py,
                          const std::vector<Arista>& aristas,
                          const std::vector<Arista>& verticales) {
    // ¿En el borde?
    for (const auto& a : aristas) {
        if (en_segmento(px, py, a.x1, a.y1, a.x2, a.y2)) return true;
    }
    // Cruces con verticales: contar si y1 <= py < y2 y la intersección está a la derecha
    int cruces = 0;
    for (const auto& v : verticales) {
        ll x = v.x1;
        ll y1 = v.y1, y2 = v.y2;
        if (y1 > y2) std::swap(y1, y2);
        if ((double)y1 <= py && py < (double)y2 && (double)x > px) cruces++;
    }
    return (cruces & 1);
}

// ¿Alguna arista atraviesa el INTERIOR del rectángulo (xmin,xmax)×(ymin,ymax)?
bool tiene_cruce_interior(ll xmin, ll xmax, ll ymin, ll ymax,
                          const std::vector<Arista>& verticales,
                          const std::vector<Arista>& horizontales) {
    if (xmin < xmax) {
        // Verticales: x dentro (excluyendo bordes), solape ESTRICTO en y
        for (const auto& v : verticales) {
            ll x = v.x1;
            if (!(xmin < x && x < xmax)) continue;
            ll y1 = v.y1, y2 = v.y2;
            if (y1 > y2) std::swap(y1, y2);
            if (y1 < ymax && y2 > ymin) {
                // Descarta solapes que solo tocan el borde
                if (!(y1 >= ymax || y2 <= ymin)) return true;
            }
        }
    }
    if (ymin < ymax) {
        // Horizontales: y dentro (excluyendo bordes), solape ESTRICTO en x
        for (const auto& h : horizontales) {
            ll y = h.y1;
            if (!(ymin < y && y < ymax)) continue;
            ll x1 = h.x1, x2 = h.x2;
            if (x1 > x2) std::swap(x1, x2);
            if (x1 < xmax && x2 > xmin) {
                if (!(x1 >= xmax || x2 <= xmin)) return true;
            }
        }
    }
    return false;
}

// ===================== Construcción del polígono =====================
void construir_aristas(const std::vector<std::pair<ll,ll>>& puntos,
                       std::vector<Arista>& aristas,
                       std::vector<Arista>& verticales,
                       std::vector<Arista>& horizontales) {
    const int n = (int)puntos.size();
    aristas.reserve(n);
    verticales.reserve(n);
    horizontales.reserve(n);

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        ll x1 = puntos[i].first;
        ll y1 = puntos[i].second;
        ll x2 = puntos[j].first;
        ll y2 = puntos[j].second;
        Arista a{x1,y1,x2,y2};
        aristas.push_back(a);
        if (x1 == x2)      verticales.push_back(a);
        else if (y1 == y2) horizontales.push_back(a);
        else {
            // En tu práctica: "siempre comparten fila o columna".
            // Si no se cumple, se podría avisar o normalizar.
        }
    }
}

// ===================== Búsqueda de mejor área =====================
ll calcular_mejor_area(const std::vector<std::pair<ll,ll>>& puntos,
                       const std::vector<Arista>& aristas,
                       const std::vector<Arista>& verticales,
                       const std::vector<Arista>& horizontales) {
    const int n = (int)puntos.size();
    ll mejor = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ll xi = puntos[i].first, yi = puntos[i].second;
            ll xj = puntos[j].first, yj = puntos[j].second;

            ll dx = std::llabs(xi - xj);
            ll dy = std::llabs(yi - yj);
            ll area = (dx + 1) * (dy + 1);   // igual a tu versión en C
            if (area <= mejor) continue;     // poda simple

            ll xmin = std::min(xi, xj);
            ll xmax = std::max(xi, xj);
            ll ymin = std::min(yi, yj);
            ll ymax = std::max(yi, yj);

            // Centro del rectángulo
            double cx = (xmin + xmax) / 2.0;
            double cy = (ymin + ymax) / 2.0;

            // 1) Centro dentro o en el borde
            if (!punto_dentro_o_borde(cx, cy, aristas, verticales)) continue;
            // 2) Sin aristas atravesando el INTERIOR
            if (tiene_cruce_interior(xmin, xmax, ymin, ymax, verticales, horizontales)) continue;

            mejor = area;
        }
    }
    return mejor;
}

// ===================== Programa principal =====================
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " input.txt\n";
        return 1;
    }

    std::vector<std::pair<ll,ll>> puntos;
    if (!leer_puntos(argv[1], puntos)) return 1;
    if (puntos.size() < 2) { std::cout << "0\n"; return 0; }

    std::vector<Arista> aristas, verticales, horizontales;
    construir_aristas(puntos, aristas, verticales, horizontales);

    ll area_maxima = calcular_mejor_area(puntos, aristas, verticales, horizontales);
    std::cout << "Área máxima: " << area_maxima << "\n";
    return 0;
}
