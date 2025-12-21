# Advent of Code 2025 - Día 5

## 1. Justificación y Elección del Problema

Se ha seleccionado el reto del día 5 debido a su idoneidad para aplicar estructuras de datos dinámicas, específicamente estructuras de **Árboles**. El problema plantea la gestión de un conjunto masivo de rangos numéricos y la validación de la frescura del inventario, un escenario donde las estructuras estáticas o lineales resultan ineficientes. Anteriormente, los problemas planteados se podían resolver mediante fuerza bruta y su coste no hubiera variado significativamente; este problema es perfecto para implementar un **Árbol Binario de Búsqueda**.

Mientras que un vector convencional ofrece operaciones de búsqueda con coste lineal `O(n)`, el volumen de datos de este problema requiere una aproximación que permita operaciones en tiempo logarítmico `O(log n)`. Por tanto, este reto justifica plenamente la implementación de una estructura jerárquica para organizar la información y optimizar las consultas.

En conclusión, mientras que otros problemas del Advent of Code se pueden resolver eficientemente con Tablas Hash o Matrices, el día 5 presenta una combinación de rangos continuos y valores masivos que inutiliza esas estructuras. Es el único problema de la primera semana que exige una organización jerárquica de los datos (**divide y vencerás**) para ser resuelto en un tiempo razonable, lo que lo convierte en el ejemplo perfecto para implementar un Árbol Binario.

## 2. Descripción Técnica

Para la resolución se ha diseñado la clase `ArbolDeIntervalos`, implementando manualmente la estructura de nodos y punteros según el modelo de referencia para árboles binarios.

Se ha definido una estructura `Nodo` que contiene el valor informativo (centro y rangos solapados) y dos punteros (`izquierdo` y `derecho`) para enlazar con los subárboles. La construcción del árbol emplea recursividad:

1.  Se determina un punto medio (pivote) del rango de datos actual.
2.  Se clasifican los intervalos en tres subconjuntos (izquierda, derecha y centro).
3.  Se generan recursivamente los subárboles hijos, enlazándolos al nodo raíz.

La lógica de consulta se asemeja a la de un Árbol Binario de Búsqueda. Para verificar la frescura de un ingrediente, el algoritmo decide el camino a seguir comparando el identificador con el valor central del nodo:

* Si el valor buscado es menor que el centro, se desciende por la rama izquierda.
* Si es mayor, se desciende por la derecha.
* Si coincide con el rango actual, se valida inmediatamente.

Esto permite descartar mitades completas del árbol en cada paso, acercando la eficiencia a `O(log n)`.

### Dificultades Encontradas y Soluciones

* **Gestión de intervalos solapados**
    * **Problema:** En un Árbol Binario de Búsqueda estándar, un valor es menor o mayor que el nodo, pero nunca ambas cosas. Sin embargo, al trabajar con intervalos, surgía la duda de qué hacer con un rango (ej: 10-20) si el centro del nodo era 15. El intervalo cruzaba el pivote y no podía enviarse ni totalmente a la izquierda ni a la derecha.
    * **Solución:** Se decidió modificar la estructura del nodo para incluir un contenedor específico (`vector<Intervalo> solapados`). De esta forma, los intervalos que cruzan el centro se almacenan en el propio nodo y no descienden más en la jerarquía. Esto simplificó la lógica de búsqueda y evitó tener que fragmentar los intervalos en dos partes.

* **Fugas de memoria**
    * **Problema:** Al trabajar con punteros y memoria dinámica (`new`), el programa funcionaba correctamente pero no liberaba la memoria RAM al finalizar.
    * **Solución:** Se implementó un destructor en la clase `ArbolDeIntervalos`. Para borrar correctamente, se tuvo que aplicar un recorrido en **post-orden** (primero se eliminan los hijos izquierdo y derecho, y finalmente el propio nodo). Esto asegura que no se pierdan las referencias a los subárboles antes de poder borrarlos.

## 3. Análisis de Alternativas

Durante el diseño de la solución se descartaron las siguientes técnicas de resolución:

* **Vectores / Listas Enlazadas (Fuerza Bruta):**
    Las estructuras lineales implican recorridos completos para la búsqueda, con un coste computacional de `O(n)` o incluso `O(n^2)` si no están ordenadas. Con la entrada masiva de datos del problema, el tiempo de ejecución resultaba inviable.

* **Tablas Hash (Arrays estáticos):**
    Aunque ofrecen acceso cercano a `O(1)`, requieren reservar espacio contiguo en memoria. Dado que los IDs son del tipo `long long`, una estructura estática sobredimensionada excedería la memoria RAM disponible.

## 4. Valoración Personal

La resolución de este problema ha permitido consolidar los conceptos teóricos sobre árboles.

Se ha comprobado la diferencia de rendimiento entre una búsqueda lineal y una búsqueda jerárquica. Se ha aprendido que la eficiencia algorítmica no es un concepto abstracto: pasar de una solución lineal `O(n)` a una logarítmica `O(log n)` mediante el Árbol de Intervalos ha supuesto la diferencia entre un programa que no termina y uno que responde instantáneamente.

Además, debido a los problemas surgidos durante el desarrollo, la resolución de los mismos ha aportado nuevos aprendizajes:

* La necesidad de solucionar las fugas de memoria ha obligado a entender el ciclo de vida de los punteros y la importancia del recorrido en **postorden** para la destrucción segura de estructuras enlazadas, tal como se detalla en el temario.
* Resolver el problema de los intervalos solapados implicó adaptar la recursividad estándar. No siempre se debe descender hasta las hojas: los intervalos solapados deben detenerse en el nodo intermedio. Además, se ha reforzado la importancia de definir bien el caso base para evitar errores de memoria o bucles infinitos al dividir los datos.
* Los errores de desbordamiento han servido para recordar que se debe asegurar que los contenedores de datos (`long long` / `int`) sean adecuados para la magnitud del problema.

## 5. Compilación

Asegúrate de tener el archivo `input.txt` en la misma carpeta.

g++ -o day5 day5.cpp
./day5
