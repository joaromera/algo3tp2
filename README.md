_DISCLAIMER_: this project is several years old. It was made with little knowledge of C++ and its best & common practices. Recent updates are made as an exercise of code reviewing my past self, just for fun.

# Trabajo Práctico #2 - Algoritmos y Estructuras de Datos III

## Yéndose por las ramas

Los archivos *hiperconectados.cpp* y *hiperauditados.cpp* son las rutinas principales que resuelven los problemas correspondientes del enunciado. A su vez los mismos dependen de los siguientes archivos (.cpp y .h) que utilizan como subrutinas:

- astar
- bellmanford
- dantzig
- dijkstra
- dijkstrapq
- floydwarshall
- kruskal
- kruskalpc
- prim

Además se cuenta con los siguientes programas para facilitar algunas tareas:

- *CommonTypes.h* incluye definiciones de tipos comunes a todos los algoritmos.

- *Generator.cpp* es un generador aleatorio de grafos.

- *EuclidianGraphs.cpp* es un generador aleatorio de grafos que respetan la distancia euclidiana.

- *grafos.sh* inluye rutinas para automatizar: la generación de grafos con llamadas a los generador y la ejecución de los programas con los grafos generados.

- *eucligrafos.sh* hace lo propio para generar grafos euclidianos automáticamente o para realizar llamadas automáticas a los programas principales.

- Para los *.sh* es necesario modificar las rutas de los ejecutables y crear las carpetas donde se quiere guardar la salida.

---

## Cómo compilar

Se requiere *g++* como compilador. Desde la carpeta donde están los archivos ejecutar para compilar los archivos:

> make

Y para borrarlos:

> make clean

---

## Uso

Detallamos el uso de los programas, los parámetros que reciben y el formato de la solución que devuelven.

## Hiperconectados

Ofrecemos las siguientes opciones para ejecutar y testear el programa:

> ./hiperconectados

Para ejecutar pasando los grafos por *línea de comandos*. La primera línea indica la cantidad **v** de nodos, la segunda la cantidad **e** de ejes. Luego habrá que pasar **e** líneas indicando tres valores **a**, **b**, **c**, que indicarán para cada una de las **e** aristas el los nodos **a** y **b** que conectan y el peso **c** de las mismas. La salida consistirá de **e** líneas. Cada linea tendrá un string que indicará si la posible arista está en *toda* solución, *alguna* solución o *ninguna*. (Por defecto el programa utiliza Prim como subalgoritmo para resolver el problema).

> ./hiperconectados *filename* *algorithm*

De esta manera se puede ejecutar el programa levantando un grafo almacenado en la ruta especificada por *filename* -el mismo debe respetar el formato detallado anteriormente-. Para elegir el algoritmo se debe indicar una de las siguientes opciones: **P** para Prim, **K** para Kruskal y **KPC** para Kruskal con Path Compression. La salida consistira en las **e** líneas de aristas del grafo según la lógica anterior.

> ./hiperconectados *filename* *algorithm* *laps*

Agregando un número entero de *laps* se puede medir el desempeño del algoritmo. Para lo mismo se ejecuta tantas veces como *laps* indique, se guarda el tiempo que tarda en resolver el problema para el grafo utilizando el algoritmo indicando y se promedia dependiendo de la cantidad de llamadas. La salida se encontrará en formato CSV en la ruta:

> resultados/

## Hiperauditados

Para usar hiperauditados pasando los grafos por command line ejecutar:

> ./hiperauditados

La primera línea indicará la cantidad de nodos **v** seguida de la cantidad de aristas **e**. Luego se introducirán **v** líneas correspondientes al costo del litro de combustible de cada ciudad. Por último, se necesitarán **e** líneas indicando las ciudades **a** y **b** conectadas por una arista y **c**, la distancia en litros de combustible. La *salida* consistirá de n(n-1)/2 líneas de tres enteros **a** **b** y **c**, indicando el costo mínimo (**c**) entre las ciudades respetando **a** < **b**. 

(El algoritmo por defecto es Dijkstra)

La otra opción para ejecutar el programa es:

> ./hiperauditados *filename* *algorithm*

Permite ejecutar el programa levantando un grafo desde *filename* y utilizando el subalgoritmo indicado por *algorithm*, con las opciones: **D** para Dijkstra, **DPQ** para Dijkstra con Priority Queue, **A** para A*, **BF** para Bellman-Ford, **FW** para Floyd-Warshall y **DZ** para Dantzig. El archivo debe respetar la entrada descripta anteriormente.

Por último para poder testar los tiempos de resolución se debe agregar el parámetro correspondiente a la cantidad de *laps* para ejecutar el programa:

> ./hiperauditados *filename* *algorithm* *laps*

Los resultados se encontrarán en:

> resultados/

---
## Generación de grafos

### generator.cpp

Se puede ejecutar el generador con las siguientes opciones -para *hiperauditados* solo puede utilizarse la última-:

> ./generator *n*

De esta manera se genera un grafo completo de *n* nodos.

> ./generator *n* *e*

Genera un grafo completo de *n* nodos y *e* aristas.

> ./generator *n* *e* *s* *problem*

Nos devuelve un grafo de *n* nodos, *e* aristas, utilizando el valor de *s* como semilla para la función srand() de C++ y si se utiliza el valor 2 como *problem* se genera un archivo que respeta la entrada que espera **Hiperauditados**.

Todos los grafos son devueltos como archivos de texto en la carpeta en que se ejecuta el generador.

### euclidiangraphs.cpp

Todos estos grafos son para *hiperauditados*. Se puede pasar por línea de comandos la cantidad de nodos y ejes que se quieren para el grafo ejecutando:

> ./euclidiangraphs

Por último se pueden pasar como parámetros de la siguiente manera (útil para automatizar con un script):

> ./euclidiangraphs *v* *e* *s*

Indicando *v* cantidad de nodos, *e* cantidad de aristas y *s* semilla para srand() de C++.

Todos los grafos son devueltos como archivos de texto en la carpeta en que se ejecuta el generador.

---
