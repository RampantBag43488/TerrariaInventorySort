#ifndef ITEMQUEUE_H_
#define ITEMQUEUE_H_

#include <iostream>
#include <vector>
#include "item.h"

using namespace std;

template <class T>
class itemQueue {
    private:
        int head, tail, size, counter;
        T* slots;

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

template <class T>
void itemQueue<T>::enqueue(T v) {
    if(full()){
        return;
    }

    slots[tail] = v;
    tail = (tail + 1) % size;
    counter++;
}

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

template <class T>
bool itemQueue<T>::empty() {
    return (counter == 0);
}

template <class T>
bool itemQueue<T>::full() {
    return (counter == size);
}

template <class T>
T itemQueue<T>::front() {
    return slots[head];
}

template <class T>
int itemQueue<T>::count() {
    return counter;
}

#endif