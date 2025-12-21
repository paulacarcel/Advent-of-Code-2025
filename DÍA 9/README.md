

# Advent of Code 2025 — Día 9

Hecho por Mar Real Osca.

---

## Descripción del problema
Se busca el **rectángulo de mayor área** usando dos baldosas **rojas** como esquinas opuestas.

- **Parte 1**: área máxima entre dos rojas (coordenadas **incluyentes**).
- **Parte 2**: el rectángulo solo puede contener baldosas **rojas o verdes** (las verdes conectan rojas y rellenan el interior del bucle).

---

## Justificación de la elección
Este reto nos permite aplicar ideas prácticas:

- Comprobar si un rectángulo está dentro del contorno formado por las baldosas.
- Evitar soluciones lentas usando técnicas como **ray casting** (para saber si un punto está dentro) y comprobación de aristas.
- Añadir una **tabla hash propia** para buscar baldosas rojas de forma rápida.

---

## Estructuras usadas
- **`HashSetPair` (tabla hash propia)**: guarda todas las baldosas **rojas** como pares `(x,y)` y permite consultar su posición de forma rápida.
- **`vector<pair<ll,ll>> puntos`**: lista dinámica con todas las coordenadas rojas leídas del `input.txt`.
- **`struct Arista { x1, y1, x2, y2 }`**: representa un segmento del borde (vertical u horizontal).
- **`vector<Arista> aristas / verticales / horizontales`**:
  - `aristas`: todas las aristas del borde (incluye el cierre).
  - `verticales`: solo segmentos verticales.
  - `horizontales`: solo segmentos horizontales.

---

## Explicación de la solución
1. **Leer los puntos** del fichero y guardarlos en:
   - Una lista con todas las coordenadas.
   - Una tabla hash propia para búsquedas rápidas.

2. **Construir el contorno** del polígono separando las aristas en:
   - Verticales.
   - Horizontales.

### Parte 1
- Probar todas las parejas de baldosas rojas.
- Calcular el área con la fórmula:  
  `(|x1 - x2| + 1) * (|y1 - y2| + 1)`.
- Si el área no mejora la mejor encontrada, se descarta.

### Parte 2
- Comprobar que el **centro del rectángulo** está dentro del contorno (o en el borde) usando **ray casting**.
- Verificar que **ninguna arista atraviesa el interior** del rectángulo (tocar el borde sí está permitido).

Finalmente, **actualizar el área máxima** cuando el rectángulo pasa todas las comprobaciones.

---

**Funciones principales **
- `leer_puntos`, `construir_aristas`
- `punto_dentro_o_borde` 
- `tiene_cruce_interior` 
- `calcular_mejor_area`
-  `HashSetPair::insert`
-  `HashSetPair::contains`

---

## Complejidad y eficiencia
- Comparar todas las parejas: `O(n²)`.
- Comprobaciones por rectángulo: dependen del número de aristas.
- Mejoras aplicadas:
  - **Poda por área** (si el área no mejora, se descarta).
  - **Separación de aristas** verticales y horizontales.
  - **Uso de tabla hash propia** para búsquedas rápidas.

---

## Alternativas consideradas y por qué se descartaron
- **Fuerza bruta por celdas**: recorrer toda la cuadrícula para comprobar cada rectángulo.  
  *Descartada porque el coste sería enorme en entradas grandes (muy ineficiente).*

- **Flood fill (BFS/DFS) para marcar interior**: rellenar el área verde y luego validar rectángulos.  
  *Descartada porque añade complejidad y tiempo; el contorno y el ray casting ya resuelven el problema de forma más directa.*

- **Intersección general de segmentos**: usar algoritmos genéricos para comprobar cruces.  
  *Descartada porque las aristas son ortogonales, lo que permite simplificar mucho las comprobaciones.*

---

## Valoración personal y aprendizaje
Este reto nos enseñó a:
- Aplicar técnicas simples como **ray casting** para resolver problemas complejos sin recurrir a fuerza bruta.
- Ver cómo una **tabla hash propia** mejora la eficiencia y mantiene el código claro.
- La importancia de separar responsabilidades en funciones pequeñas
  
---

## Soluciones 

Input proporcionado en el Advent of Code (`dia09/input.txt`)**
- Parte 1: `Área máxima: 4769758290`
- Parte 2: `Área máxima: 1588990708`

---


