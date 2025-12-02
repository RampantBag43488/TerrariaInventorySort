# Proyecto sort de inventario (Terraria)
### Iñaki Mancera Llano

## Descripcion
Este proyecto trata de simular la funcion de ordenar inventario de un inventario del videojuego terraria ordenando por cantidad del objeto que hay y por tipo (ambos de mayor a menor y menor a mayor) y la funcion de los slots para objetos lanzables en el inventario de terraria. La funcion de objetos lanzables funciona como en el videojuego, el item en el "slot de hasta arriba" es el que se usa al lanzar en el juego y siguen en orden una vez se acaba el primero.

## Implementaciones
Se implementa el algoritmo de ordenamiento QuickSort para ordenar un vectos de los distintos items. Para los ordenamientos distintos que son cantidad y tipo (ambos de mayor a menor y menor a mayor), se implementan 4 distintas funciones que comparan los atributos de los items de cantidad y tipo y deciden cual devolver a QuickSort como mayor.
Se implementa una queue simulando los 3 slots para objetos lanzables a la derecha del inventario de terraria, siendo que el item en el slot hasta arriba es el que primero se empieza a lanzar y cuando se acaba siguen los siguientes en orden decendente, por lo que se usa la estructura lineal queue.

## Analisis de complejidad
### QuickSort
Tiempo
- Mejor caso: O(n Log(n))
- Caso promedio: O(n Log(n))
- Peor caso: O(n^2)

Espacio
- O(Log(n))

### ItemQueue
Tiempo mejor caso
- Acceso: O(n)
- Busqueda: O(n)
- Insercion: O(1)

Tiempo peor caso
- Acceso: O(n)
- Busqueda: O(n)
- Insercion: O(1)

Espacio
- O(n)

### Proyecto completo
Tiempo mejor y peor caso
- T(n) = O(n) + O(n)t1 + (O(n)(t2 + t3 + t4 + t5) + O(n Log(n))t6 + t7O(1) + O(n)t8 = O(n Log(n))/O(n^2)

O(n): Carga de archivo.

t1: Mostrar items en vector.

t2, t3, t4, t5: Quicksort aplicado de distintas formas.

t6: Queue de objetos lanzables.

t7: Objetos lanzados.

t8: Veces que se guardaron los items en .csv con nuevo orden.


Espacio
- S(n) = O(n) + O(Log(n)) + O(1) = O(n)

vector, quicksort y queue/sistema/variables.

## Consideraciones (casos que pueden romper el proyecto)
El código despliega un menú donde ver el inventario, acomodarlo de distintas formas, agregar objetos lanzables a la fila de objetos lanzables, lanzar un objeto en la fila y guardar los cambios hechos al orden del inventario en el .csv.
El programa corre tanto en la consola como en visual studio code(con las extensiones necesarias instaladas y MinGW) y está hecho con c++ standard por lo que corre en todos los sistemas operativos.
Se debe tener en una misma carpeta el main, los dos archivos.h y el .csv (si es el vs code el .csv debe estar en la carpeta de output).

compilar en consola con: "g++ TerrariaMain.cpp" (esto teniendo todos los archivos como se especifico y habriendo desde alli la consola).

### Correcciones
- Se agrego funcion de actualizacion de datos en el .csv.
- Se agregaron comentarios para describir las funciones.
