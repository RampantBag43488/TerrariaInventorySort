/*
 *
 * Proyecto inventario de terraria main
 * Inaki Mancera Llano
 * A01708827
 * 01/12/2025
 * version: 1
 * Este proyecto busca simular el inventario del videojuego terraria, permite
 * acomodar los items en el inventario por cantidad o por tipo (mayor a menor 
 * y menor a mayor) y anadir item que se puedan lanzar a la fila de objetos 
 * lanzables donde el que este primero se va lanzando primero.
 * 
 */

// Objetos de mi proyecto, queue y librerias necesarias
#include <fstream>
#include <sstream>
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
    cout << "6. Agregar objeto lanzable para uso\n";
    cout << "7. Disparar!!!!\n";
    cout << "8. Guardar items en el .csv\n";
    cout << "9. Salir\n";
    cout << "Elige una opcion: ";
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
 * quickSort ordena un vector en el caso que se le pase
 *
 * Recibe referencia al vector de items para ordenarse, el 
 * valor mas bajo y el valor mas alto que se usara como 
 * pivote para checar los valores del vactor dependiendo 
 * del caso que se pase para ordenar y con una variable 
 * temporal de tipo item va swapeando i y j hasta que j 
 * llega al final y entonces i sera la posicion de el 
 * pivote asi que intercambian lugar y se hace recursion 
 * con el lado izquierdo y derecho del pivote hasta que 
 * este ordenado.
 *
 * @param referencia a vector items, entero low, entero 
 * high y caso de ordenamiento
 * @return 
 */
void quickSort(vector<Item> &vec, int low, int high, int n) {
    if(low >= high) {
        return;
    }
    int i = low - 1;
    int j = low;
    int pi = high;
    bool cond;
    Item temp;

    while(j < pi) {
        switch (n) {
            case 1: {
                cond = menorAmount(vec[j], vec[pi]);
                break;
            }
            case 2: {
                cond = mayorAmount(vec[j], vec[pi]);
                break;
            }
            case 3: {
                cond = menorType(vec[j], vec[pi]);
                break;
            }
            case 4: {
                cond = mayorType(vec[j], vec[pi]);
                break;
            }
        }

        if(cond) {
            i++;
            Item temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
        }
        j++;
    }

    i++;
    
    temp = vec[i];
    vec[i] = vec[pi];
    vec[pi] = temp;

    quickSort(vec, low, i - 1, n);
    quickSort(vec, i + 1, high, n);
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
 * mostrarItems imprime todos los items lanzables
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
                quickSort(items, 0, items.size() - 1, 1);
                break;
            }
            case 3: {
                quickSort(items, 0, items.size() - 1, 2);
                break;
            }
            case 4: {
                quickSort(items, 0, items.size() - 1, 3);
                break;
            }
            case 5: {
                quickSort(items, 0, items.size() - 1, 4);
                break;
            }
            case 6: {
                if(arrows.full()) {
                    cout << "No caben mas objetos lanzables :o\n";
                }
                else{
                    cin.ignore();
                    string objeto;
                    mostrarFlechas(items);
                    cout << "Que objeto lanzable quiere anadir a los slots de lanzables (nombre exacto): ";
                    getline(cin, objeto);
                    for (Item &i : items) {
                        if(i.getName() == objeto){
                            arrows.enqueue(i);
                        }
                    }
                }
                
                break;
            }
            case 7: {
                if(arrows.empty()) {
                    cout << "No hay mas flechas :(\n";
                }
                else{
                    arrows.dequeue();
                    cout << "Piuuuuuuuu >>---->\n";
                    cout << "Flechas en uso restantes: \n";
                    cout << arrows.front().getName() << ": " << arrows.front().getAmount() << endl;
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
                cout << "Opción inválida.\n";
            }
        }
    return 0;
}
