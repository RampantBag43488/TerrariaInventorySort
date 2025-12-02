
/*
 *
 * Proyecto inventario clase itemQueue
 * Inaki Mancera Llano
 * A01708827
 * 12/06/2025
 * version: 1
 * Esta clase define queue para los items lanzables.
 */
#ifndef ITEMQUEUE_H_
#define ITEMQUEUE_H_

#include <iostream>
#include <vector>
#include "item.h"

using namespace std;

//Declaracion de clase itemQueue con template del tipo de clase
template <class T>
class itemQueue {
    //Declaracion de variables
    private:
        int head, tail, size, counter;
        T* slots;

    //Declaracion de los métodos que va a tener el objeto
    public:
        itemQueue(int);
        void enqueue(T);
        void dequeue();
        bool empty();
        bool full();
        int count();
        T front();
};

template <class T>
itemQueue<T>::itemQueue(int s) {
    size = s;
    slots = new T[size];
    head = 0;
    tail = 0;
    counter = 0;
}

/**
 * enqueue ingresa un objeto a la lista de items lanzables
 *
 * Solo ingresa el item si hay espacio en la queue.
 *
 * @param un objeto del tipo de la queue
 * @return 
 */
template <class T>
void itemQueue<T>::enqueue(T v) {
    if(full()){
        return;
    }

    slots[tail] = v;
    tail = (tail + 1) % size;
    counter++;
}

/**
 * dequeue va eliminando item de la queue en el orden que estan
 *
 * Elimina 1 al valor de cantidad del item y cuando queden 0 se 
 * quita de la queue.
 *
 * @param
 * @return 
 */
template <class T>
void itemQueue<T>::dequeue() {
    if(empty()){
        return;
    }

    T &frontItem = slots[head];
    if(frontItem.getAmount() == 1){
        head = (head + 1) % size;
        counter--;
    }
    else{
        frontItem.setAmount(frontItem.getAmount() - 1);
    }
}

/**
 * empty dice si esta vacia o no la queue
 *
 * Checa el contados de objetos en la queue para saber si
 * hay algo.
 *
 * @param
 * @return booleano true=vacio
 */
template <class T>
bool itemQueue<T>::empty() {
    return (counter == 0);
}

/**
 * full dice si esta llena o no la queue
 *
 * Checa el contados de objetos en la queue y lo compara 
 * con size para saber si esta lleno.
 *
 * @param
 * @return booleano true=lleno
 */
template <class T>
bool itemQueue<T>::full() {
    return (counter == size);
}

/**
 * front regresa el objeto que esta a la cabeza de la queue
 *
 * Solicita el objeto head al vector que representa la queue
 *
 * @param
 * @return Objeto de tipo T
 */
template <class T>
T itemQueue<T>::front() {
    return slots[head];
}

/**
 * count dice cuantos items hay en la queue
 *
 * Regresa el valor counter
 *
 * @param
 * @return contador en entero
 */
template <class T>
int itemQueue<T>::count() {
    return counter;
}

#endif
