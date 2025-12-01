# Proyecto POO (inventario)
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
- O(n Log(n))

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

## Consideraciones (casos que pueden romper el proyecto)

### Correcciones
