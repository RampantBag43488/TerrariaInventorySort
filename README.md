# Proyecto sort de inventario (Terraria)
### Iñaki Mancera Llano

## Descripcion
Este proyecto simula la funcion de ordenar inventario de un inventario del videojuego terraria ordenando por cantidad del objeto que hay y por tipo (ambos de mayor a menor y menor a mayor) y la funcion de los slots para objetos lanzables en el inventario de terraria. La funcion de objetos lanzables funciona como en el videojuego, el item en el "slot de hasta arriba" es el que se usa al lanzar en el juego y siguen en orden una vez se acaba el primero.

## Implementaciones
Se implementa el algoritmo de ordenamiento TimSort para ordenar un vectos de los distintos items, se escogio este algoritmo por que mantiene un tiempo de Θ(n log(n)) como el mergesort en sus tres casos (se usa la logica del timsort que es dividir en runs, acomodar con insertion y juntar con merge, pero solo se usa una version simplificada del mismo lo que lo hace mas sencillo de implementar y entender aparte de que solo se pone lo necesario para el proyecto, siendo el timsort un algoritmo extenso) y en su version original su mejor caso es de O(n). Este se implementa dividiendo el vector a ordenar en bloques de un tamano definido, ordena cada bloque con un insertionsort (insertando cada elemento en la posicion correcta dependiendo como se quiera ordenar) y termina juntando los bloque como se hace en el mergesort (con un arreglo izquierdo y uno derecho). Se utilizo este algoritmo por que el mergesort fue implementado en la evidencia 1 de problemas. Para los ordenamientos distintos que son cantidad y tipo (ambos de mayor a menor y menor a mayor), se implementan 4 distintas funciones que comparan los atributos de los items de cantidad y tipo y deciden cual devolver a TimSort como mayor.
Se implementa una queue simulando los 3 slots para objetos lanzables a la derecha del inventario de terraria, siendo que el item en el slot hasta arriba es el que primero se empieza a lanzar y cuando se acaba siguen los siguientes en orden decendente, por lo que se usa la estructura lineal queue.

## Analisis de complejidad
### TimSort
Tiempo
- Mejor caso: O(n Log(n))
- Caso promedio: O(n Log(n))
- Peor caso: O(n Log(n))

Espacio
- O(n)

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
- T(n) = O(n) + O(n)t1 + (O(n Log(n))(t2 + t3 + t4 + t5) + O(n)t6 + t7O(1) + O(n)t8 = O(n Log(n))/O(n^2)

O(n): Carga de archivo.

t1: Mostrar items en vector.

t2, t3, t4, t5: TimSort aplicado de distintas formas.

t6: Queue de objetos lanzables.

t7: Objetos lanzados.

t8: Veces que se guardaron los items en .csv con nuevo orden.


Espacio
- S(n) = O(n) + O(n) + O(1) = O(n)

vector, timsort y queue/sistema/variables.

## Consideraciones
El código despliega un menú donde ver el inventario, acomodarlo de distintas formas, agregar objetos lanzables a la fila de objetos lanzables, lanzar un objeto en la fila y guardar los cambios hechos al orden del inventario en el .csv.
El programa corre tanto en la consola como en visual studio code(con las extensiones necesarias instaladas y MinGW) y está hecho con c++ standard por lo que corre en todos los sistemas operativos.
Se debe tener en una misma carpeta el main, los dos archivos.h y el .csv (si es el vs code el .csv debe estar en la carpeta de output).

compilar en consola con: "g++ TerrariaMain.cpp" (esto teniendo todos los archivos como se especifico y habriendo desde alli la consola).

### Correcciones
- Se agrego funcion de actualizacion de datos en el .csv.
- Se agregaron comentarios para describir las funciones.
- Se agrego un display de los tres slots de items lanzables que tiene el inventario de terraria para ir viendo los cambios conforme se ingresan items y se usar.
- Se cambio de quicksort a timsort para una mejora en el peor caso de tiempo y en el major caso de tiempo del algoritmo de ordenamiento.
- Se implementaro funciones para obtener el item en la posicion 2 y 3 de la lista de items lanzables si es que hay para hacer posible el displey de los mismos en el main.
