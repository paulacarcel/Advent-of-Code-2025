
# ADVENT OF CODE 2025 - DÍA 7, PARTE 2

En la segunda parte de este día se plantea que, tras encontrar un Splitter ('^'), se pueden tomar a partir de esta posición dos líneas temporales (izquierda o derecha). Así pues, la finalidad es contar el número "timelines" (caminos distintos) que salen del mapa por los laterales o por la parte inferior.

## Justificación de la elección:

Hemos elegido este problema porque permite utilizar grafos de una forma muy interesante, combinándolos con programación dinámica, generando así "grafos dirigidos". Esto nos permite transformar una simulación compleja de múltiples bifurcaciones en un problema de conteo de caminos.

---

##  Técnicas y estructuras de datos utilizadas

###  1. Grafo dirigido acíclico (conocido como DAG) 
No se construye un grafo de manera explícita, pero sí siguiendo su estructura básica:
- Cada celda `(r,c)` es un nodo.
- Desde cada nodo solo se puede ir a la fila siguiente (`r+1`).
- Transiciones:
  - Si el carácter es `'^'` → dos aristas (`c-1` y `c+1`).
  - Si no es `'^'` → una arista recta (`c`).

###  2. Programación Dinámica por capas
Se usan dos arrays:
- `ways[c]` → nº de caminos que llegan a la columna `c` en la fila actual.
- `next_ways[c]` → nº de caminos que llegarán a la fila siguiente.

Esta separación evita recomputaciones y nos permite procesar el grafo fila a fila.

### 3. Arrays estáticos
Para eficiencia y sobre todo simplicidad, se usa:
- `string mapa[MAXR]` para almacenar el mapa.
- Arrays de tamaño fijo para DP (`ways` y `next_ways`).

---

##  Explicación de la solución paso a paso MODIFICAR!!

1. **Lectura del mapa** desde `input.txt`. Cada línea se interpreta como una fila.
2. **Búsqueda de la posición 'S'**, el punto de inicio del haz.  
   - Todo el flujo parte desde la columna `sc` justo debajo de `S`.
3. **Inicializamos la DP**:
   - `ways[sc] = 1` (tenemos un camino inicial).
4. **Procesamos el mapa fila a fila**:
   - Si `mapa[r][c] == '^'` → el camino se **bifurca**:
     - Va a `c-1` y a `c+1`.
     - Si alguna salida está fuera del mapa → se suma a `cronog`.
   - Si no hay `'^'` → el camino **sigue recto** (`c`).
5. **Actualizamos los arrays** (`ways = next_ways`) y seguimos a la siguiente fila.
6. **Al llegar al final del mapa**, cualquier camino que quede se considera como “salido por abajo” → se suma a `cronog`.
7. **El resultado final** es el número total de timelines que han salido del mapa.

---

##  Alternativas probadas o descartadas

###  Construir el grafo explícitamente
A pesar de que en un primer momento se pudo plantear la idea de implementar un grafo explícito (sin uso de memoria), la idea fue reconsiderada pues:
- Aumenta memoria innecesariamente.
- El grafo es muy regular (transiciones siempre a fila siguiente).
- El enfoque por capas es más eficiente y limpio.
  
---

##  Valoración personal y aprendizaje

Este problema nos ha permitido:

- Entender cómo convertir una **rejilla en un grafo dirigido** sin necesidad de estructuras complejas.
- Aplicar **programación dinámica** para conteo de caminos en un DAG.
- Comprender la ventaja de separar **estado actual** y **estado siguiente**.
- Trabajar con modelos que aparecen en problemas reales de propagación, caminos y simulaciones.

Ha sido especialmente útil para reforzar:
- El pensamiento por capas.
- La optimización del espacio.
- El razonamiento sobre flujos y bifurcaciones.

---

##  Cómo compilar y ejecutar ## 

### **Compilar**
Desde la terminal de Ubuntu:
g++ Dia7_P2.cpp -o Dia7P2
./Dia7P2



