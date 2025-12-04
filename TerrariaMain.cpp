/*
 *
 * Proyecto inventario de terraria main
 * Inaki Mancera Llano
 * A01708827
 * 01/12/2025
 * version: 2
 * Este proyecto busca simular el inventario del videojuego terraria, permite
 * acomodar los items en el inventario por cantidad o por tipo (mayor a menor 
 * y menor a mayor) y anadir item que se puedan lanzar a la fila de objetos 
 * lanzables donde el que este primero se va lanzando primero.
 * 
 */

// Objetos de mi proyecto, queue y librerias necesarias
#include <fstream>
#include <sstream>
#include <algorithm>   // para std::min
#include "itemqueue.h"

using namespace std;

/**
 * menu muestra las opciones que tiene el usuario para interactuar con el inventario.
 *
 * Despliega las opciones para que el usuario escoja.
 *
 * @param
 * @return 
 */
void menu() {
    cout << "\n--- MENU DEL INVENTARIO (Terraria) ---\n";
    cout << "1. Mostrar inventario\n";
    cout << "2. Ordenar por cantidad (menor a mayor)\n";
    cout << "3. Ordenar por cantidad (mayor a menor)\n";
    cout << "4. Ordenar por tipo (menor a mayor)\n";
    cout << "5. Ordenar por tipo (mayor a menor)\n";
    cout << "6. Colocar un item lanzable para uso\n";
    cout << "7. Disparar!!!!\n";
    cout << "8. Guardar items en el .csv\n";
    cout << "9. Salir\n";
    cout << "Elige una opcion: ";
}

/**
 * printCube dibuja en consola un "slot" vacio del inventario.
 *
 * Crea un vector de strings que representan las lineas de un
 * recuadro con borde (usado para mostrar un slot sin item) y
 * luego las imprime una por una en la consola.
 *
 * @param
 * @return 
 */
void printCube() {
    vector<string> lines = {
        "##################",
        "#                #",
        "#                #",
        "#                #",
        "#                #",
        "#                #",
        "#                #",
        "#                #",
        "##################"
    };

    for (const string &line : lines) {
        cout << line << '\n';
    }

}

/**
 * printCubeArrow dibuja un slot con una flecha y datos del item.
 *
 * Crea un "cubo" similar a printCube pero con una flecha apuntando
 * hacia arriba en el centro, representando que ese item está listo
 * para usarse. En la parte inferior se escribe el nombre del item
 * a la izquierda y la cantidad a la derecha.
 *
 * @param name   nombre del item lanzable que se mostrará en el cuadro
 * @param number cantidad del item que se mostrara en el cuadro
 * @return 
 */
void printCubeArrow(string name,int number) {
    vector<string> lines = {
        "##################",
        "#                #",
        "#       ^        #",
        "#      ^^^       #",
        "#     ^^^^^      #",
        "#       ^        #",
        "#       ^        #",
        "#                #",
        "##################"
    };

    int rowName = lines.size() - 2;
    for (int i = 0; i < (int)name.size() && i + 1 < (int)lines[rowName].size() - 1; i++) {
        lines[rowName][1 + i] = name[i];
    }

    string numStr = to_string(number);

    int row = lines.size() - 2;
    int len = lines[row].size();
    int startPos = len - 1 - numStr.size();

    for (int i = 0; i < (int)numStr.size(); i++) {
        lines[row][startPos + i] = numStr[i];
    }

    for (const string &line : lines) {
        cout << line << '\n';
    }
}

/**
 * cargarCSV usa la funcion ifstream para leer los datos del .csv
 *
 * Carga el archivo con la funcion file, checa si cargo bien para 
 * proseguir y si no cargo bien retorna false. Se saca la primera 
 * linea que son los headers de las columnas y luego con getline 
 * se va sacando cada linea, ingresando datos a strings y en los 
 * que son numeros se usa la funcion stoi para hacerlos enteros. 
 * Una vez sacada la linea entera se guarda en el vector de items
 * creando un item nuevo con la funcion emplace_back de vector y
 * se repite esto hasta encontrarse con una linea vacia.
 *
 * @param
 * @return booleano true=si cargo bien el archivo
 */
bool cargarCSV(string DocumentName, vector<Item> &items) {
    ifstream file(DocumentName);

    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo: " << DocumentName << "\n";
        return false;
    }

    string line;

    // Leer primera linea
    getline(file, line);

    // Leer registros
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name, samount, stype, sthrowable;

        getline(ss, name, ',');
        getline(ss, samount, ',');
        getline(ss, stype, ',');
        getline(ss, sthrowable, ',');

        int amount = stoi(samount);
        int type = stoi(stype);
        int throwable = stoi(sthrowable);
        
        items.emplace_back(name, amount, type, throwable);
    }

    file.close();
    return true;
}

/**
 * guardarCSV usa la funcion ofstream para abrir el .csv y va 
 * metiendo lineas
 *
 * Abre el archivo con ofstream y le va instertando los datos 
 * en el orden que esten en el vector de items
 *
 * @param
 * @return booleano true=se sobre escribio correctamente
 */
bool guardarCSV(string DocumentName, vector<Item> &items) {
    ofstream file(DocumentName);

    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo para escribir: " << DocumentName << "\n";
        return false;
    }

    file << "Nombre,Cantidad,Tipo,Lanzable\n";
    for (Item &i : items) {
        file << i.getName() << "," << i.getAmount() << "," << i.getType() 
        << "," << i.getThrowable() << "\n";
    }

    file.close();
    return true;
}

/**
 * menorAmount compara la cantidad de dos items distintos
 *
 * Recibe referencia a dos items distintos y compara su 
 * cantidad para luego ser organizados en base a si el 
 * primero es menor, si son iguales devuelve si el 
 * primero es menor en tipo.
 *
 * @param
 * @return booleano true=si el primero es menor en cantidad
 */
bool menorAmount(Item &a, Item &b) {
    if (a.getAmount() != b.getAmount())
        return a.getAmount() < b.getAmount();
    return a.getType() < b.getType();
}

/**
 * mayorAmount compara la cantidad de dos items distintos
 *
 * Recibe referencia a dos items distintos y compara su 
 * cantidad para luego ser organizados en base a si el 
 * primero es mayor, si son iguales devuelve si el 
 * primero es mayor en tipo.
 *
 * @param
 * @return booleano true=si el primero es mayor en cantidad
 */
bool mayorAmount(Item &a, Item &b) {
    if (a.getAmount() != b.getAmount())
        return a.getAmount() > b.getAmount();
    return a.getType() > b.getType();
}

/**
 * menorType compara el tipo de dos items distintos
 *
 * Recibe referencia a dos items distintos y compara su 
 * tipo para luego ser organizados en base a si el 
 * primero es menor, si son iguales devuelve si el 
 * primero es menor en cantidad.
 *
 * @param
 * @return booleano true=si el primero es menor en tipo
 */
bool menorType(Item &a, Item &b) {
    if (a.getType() != b.getType())
        return a.getType() < b.getType();
    return a.getAmount() < b.getAmount();
}

/**
 * mayorType compara el tipo de dos items distintos
 *
 * Recibe referencia a dos items distintos y compara su 
 * tipo para luego ser organizados en base a si el 
 * primero es mayor, si son iguales devuelve si el 
 * primero es mayor en cantidad.
 *
 * @param
 * @return booleano true=si el primero es mayor en tipo
 */
bool mayorType(Item &a, Item &b) {
    if (a.getType() != b.getType())
        return a.getType() > b.getType();
    return a.getAmount() > b.getAmount();
}

/**
 * compararItems elige el criterio de comparación según el caso.
 *
 * Recibe referencia a dos items y un entero que indica el caso de
 * ordenamiento:
 * 1 = cantidad ascendente, 2 = cantidad descendente,
 * 3 = tipo ascendente,     4 = tipo descendente.
 * Regresa true si el primer item debe ir antes que el segundo.
 *
 * @param referencias a dos items y entero modo
 * @return booleano true=si a debe ir antes que b
 */
bool compararItems(Item &a, Item &b, int modo) {
    switch (modo) {
        case 1:  return menorAmount(a, b);
        case 2:  return mayorAmount(a, b);
        case 3:  return menorType(a, b);
        case 4:  return mayorType(a, b);
        default: return menorAmount(a, b); // por defecto
    }
}

/**
 * insertionSortSegment ordena un segmento pequeño del vector con insertion sort.
 *
 * Recibe el vector de items, el índice inicial y final del segmento, y el
 * modo de ordenamiento. Recorre el segmento y va insertando cada elemento
 * en la posición correcta usando el criterio elegido con compararItems.
 *
 * @param referencia a vector items, entero left, entero right, entero modo
 * @return 
 */
void insertionSortSegment(vector<Item> &v, int left, int right, int modo) {
    for (int i = left + 1; i <= right; ++i) {
        Item key = v[i];
        int j = i - 1;

        while (j >= left && compararItems(key, v[j], modo)) {
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = key;
    }
}

/**
 * mergeSegments mezcla dos segmentos contiguos ya ordenados del vector.
 *
 * Recibe el vector de items, los índices left, mid y right que definen
 * dos subarreglos ordenados: [left, mid] y [mid+1, right]. Crea arreglos
 * temporales para cada segmento y los mezcla en el vector original usando
 * el criterio indicado por modo.
 *
 * @param referencia a vector items, enteros left, mid, right y entero modo
 * @return 
 */
void mergeSegments(vector<Item> &v, int left, int mid, int right, int modo) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Item> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = v[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = v[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (compararItems(L[i], R[j], modo)) {
            v[k++] = L[i++];
        } else {
            v[k++] = R[j++];
        }
    }

    while (i < n1) {
        v[k++] = L[i++];
    }

    while (j < n2) {
        v[k++] = R[j++];
    }
}

/**
 * timSort ordena el vector de items usando una version simplificada de TimSort.
 *
 * Primero divide el vector en bloques pequeños (runs) de tamaño MINRUN y 
 * ordena cada bloque con insertionSortSegment. Después, va haciendo merges 
 * de bloques de tamaño MINRUN, 2*MINRUN, 4*MINRUN, etc., hasta que todo 
 * el vector queda ordenado de acuerdo al modo de comparación elegido.
 *
 * @param referencia a vector items y entero modo de ordenamiento
 * @return 
 */
void timSort(vector<Item> &v, int modo) {
    const int MINRUN = 32;
    int n = v.size();

    if (n <= 1) {
        return;
    }

    // 1) Ordenar pequeños bloques con insertion sort
    for (int start = 0; start < n; start += MINRUN) {
        int end = min(start + MINRUN - 1, n - 1);
        insertionSortSegment(v, start, end, modo);
    }

    // 2) Merge de bloques de tamaño MINRUN, luego 2*MINRUN, 4*MINRUN, ...
    for (int size = MINRUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            if (mid >= n - 1) {
                break; // no hay segundo bloque completo
            }
            int right = min(left + 2 * size - 1, n - 1);
            mergeSegments(v, left, mid, right, modo);
        }
    }
}

/**
 * mostrarItems imprime todos los items en el orden que estan
 *
 * se usa un for para pasar por todos los elementos en el 
 * vector items y se imprimen todos los valores de cada 
 * item con sus getters.
 *
 * @param recibe el vector items como referencia
 * @return 
 */
void mostrarItems(vector<Item> &items) {
    cout << "======================================================\n";
    for (auto &it : items) {
        cout << "Nombre: " << it.getName() << "\tCantidad: " << it.getAmount() << "\tTipo: " 
        << it.getType() << "\tLanzable: " << it.getThrowable() << "\n";
    }
    cout << "======================================================\n";
}

/**
 * mostrarFlechas imprime todos los items lanzables
 *
 * se usa un for para pasar por todos los elementos en el 
 * vector items y se imprimen todos los valores de cada 
 * item con sus getters, los cuales tengan en el valor de
 * throwable 1.
 *
 * @param recibe el vector items como referencia
 * @return 
 */
void mostrarFlechas(vector<Item> &items) {
    cout << "======================================================\n";
    for (auto &it : items) {
        if(it.getThrowable() == 1){
            cout << "Nombre: " << it.getName() << "\tCantidad: " << it.getAmount() << "\tTipo: " 
            << it.getType() << "\tLanzable: " << it.getThrowable() << "\n";
        }
    }
    cout << "======================================================\n";
}


int main() {
    int opcion = 0;

    vector<Item> items; // vector que representara inventario
    itemQueue<Item> arrows(3); // queue para fila de objetos lanzables

    if (!cargarCSV("ItemsTerraria.csv", items)) {
        cout << "Verifique que ItemsTerraria.csv este en la misma carpeta.\n";
        return 0;
    }

    while (opcion != 9) {
        menu();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                mostrarItems(items);
                break;
            }
            case 2: {
                timSort(items, 1);
                break;
            }
            case 3: {
                timSort(items, 2);
                break;
            }
            case 4: {
                timSort(items, 3);
                break;
            }
            case 5: {
                timSort(items, 4);
                break;
            }
            case 6: { 
                if(arrows.full()) { 
                    cout << "No caben mas objetos lanzables :o\n"; 
                } 
                else{ 
                    int index = 0; 
                    cin.ignore(); 
                    string objeto; 
                    mostrarFlechas(items); 
                    cout << "Que objeto lanzable quiere anadir a los slots de lanzables (nombre exacto): "; 
                    getline(cin, objeto); 

                    for (Item &i : items) { 
                        if(i.getName() == objeto){ 
                            arrows.enqueue(i); 
                            items.erase(items.begin() + index); 
                        } 
                        index++; 
                    } 
                } 
                break; 
            }
            case 7: {
                if (arrows.empty()) {
                    cout << "\n\nNo hay items lanzables colocados:\n";
                    printCube();
                    printCube();
                    printCube();
                }
                else{
                    arrows.dequeue();
                    cout << "\n\nSlots de items lanzables:\n";

                    int c = arrows.count();

                    if (c == 0) {
                        printCube();
                        printCube();
                        printCube();
                    }
                    else if (c == 1) {
                        auto f = arrows.front();
                        printCubeArrow(f.getName(), f.getAmount());
                        printCube();
                        printCube();
                    }
                    else if (c == 2) {
                        auto f = arrows.front();
                        auto m = arrows.middle();
                        printCubeArrow(f.getName(), f.getAmount());
                        printCubeArrow(m.getName(), m.getAmount());
                        printCube();
                    }
                    else {
                        auto f = arrows.front();
                        auto m = arrows.middle();
                        auto l = arrows.last();
                        printCubeArrow(f.getName(), f.getAmount());
                        printCubeArrow(m.getName(), m.getAmount());
                        printCubeArrow(l.getName(), l.getAmount());
                    }
                }
                break;
            }
            case 8:
                if (guardarCSV("ItemsTerraria.csv", items)) {
                    cout << "Inventario guardado correctamente.\n";
                } 
                else {
                    cout << "Error guardando el archivo.\n";
                }
                break;
            case 9:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    }
    return 0;
}
