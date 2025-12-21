
# Advent of Code 2025 - Día 7

Hecho por Paula Cárcel Vercher y Sara Beses Martínez.

---

En la segunda parte de este día se plantea que, tras encontrar un Splitter ('^'), se pueden tomar a partir de esta posición dos líneas temporales (izquierda o derecha). Así pues, la finalidad de este problema es contar el número "timelines" (caminos distintos) que salen del mapa por los laterales o por la parte inferior.

## Justificación de la elección:

Se ha elegido este problema porque permite utilizar grafos de una forma muy interesante, combinándolos con programación dinámica, generando así "grafos dirigidos". Esto nos permite transformar una simulación compleja de múltiples bifurcaciones en un problema de conteo de caminos.

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
- `ways[c]` → número de caminos que llegan a la columna `c` en la fila actual.
- `next_ways[c]` → número de caminos que llegarán a la fila siguiente.

Esta separación evita recomputaciones y nos permite procesar el grafo fila a fila.

### 3. Arrays estáticos
Para eficiencia y sobre todo buscando la mayor simplicidad, se usa:
- `string mapa[MAXR]` para almacenar el mapa.
- Arrays de tamaño fijo con relación a la memoria (`ways` y `next_ways`).

---

##  Explicación de la solución paso a paso 

1. **Lectura del mapa** desde `input.txt`.
   - Cada línea se interpreta como una fila, guardándose en la variable R.
   - Se verifica la existencia de filas, si no las hay no habrá caminos.
   - Se obtiene también el número de columnas, que se guradará en la variable C.

3. **Búsqueda de la posición 'S'**, el punto de inicio del haz.  
   - Todo el flujo parte desde (`sc`,`sr`), (Sfila, Scolumna), posición de S.
   - Se verifica que todas las filas tengan el mismo ancho, para evitar errores.
   - Mediante un for se busca el carácter S, guardando su posición en las variables mencionadas.
   - Si no se encuentra, se termina con un error.
     
4. **Inicialización la DP**:
   - El uso de programación dinámica servirá para contar los caminos que salen del mapa.
   - `ways[c]` será el número de caminos que llegan a la columna c (índice de columna) en la fila actual.
   - `next_ways[c]` será el número de caminos que llegarán posteriormente a la columna c, desde el punto actual.
     
5. **Procesamiento del mapa fila a fila**:
   - Si `mapa[r][c] == '^'` → el camino se **bifurca**, esto es imprescindible:
     - Va a `c-1` (izquierda) y a `c+1` (derecha).
     - Si alguna salida está fuera del mapa → se suma a la variable `cronog`.
   - Si no hay `'^'` → el camino **sigue recto** (`c`), hasta que encuentre algún haz.
     
6. **Actualización de los arrays** (`ways = next_ways`) siguiendo a la siguiente fila, para continuar con el conteo.
   
8. **Al llegar al final del mapa**, cualquier camino que quede se considera como “salido por abajo” → se suma a la variable `cronog`.
   
10. **El resultado final** es el número total de timelines que han salido del mapa.

---

##  Alternativas probadas o descartadas

###  Construir el grafo explícitamente
A pesar de que en un primer momento se pudo plantear la idea de implementar un grafo explícito (sin uso de memoria), la idea fue reconsiderada pues:
- Aumenta memoria innecesariamente.
- El grafo es muy regular (transiciones siempre a fila siguiente), facilitando el uso de memoria.
- El enfoque por capas es más eficiente y limpio.
  
---

##  Valoración personal y aprendizaje

Este problema nos ha ayudado a reforzar los conceptos vistos en clase, como el uso de grafos y de memoria. Al combinar estas dos ideas, hemos podido implementar un grafo dirigido y aplicar programación dinámica para contar caminos. Además, hemos podido comprobar la utilidad práctica de separar correctamente el estado actual del estado siguiente, lo que facilita la resolución del problema. En general, esta experiencia nos ha permitido entender que, usando bien las estructuras y técnicas aprendidas, es posible reducir considerablemente la complejidad de los problemas.

---

##  Cómo compilar y ejecutar ## 

### **Compilar**
Desde la terminal de Ubuntu:
g++ Dia7_P2.cpp -o Dia7P2
./Dia7P2

Debemos tener en cuenta que el archivo proporcionado "input.txt" debe encontrarse en el mismo directorio que el código.



