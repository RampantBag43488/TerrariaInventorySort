/*
 *
 * Proyecto inventario clase Item
 * Inaki Mancera Llano
 * A01708827
 * 12/06/2025
 * version: 1
 * Esta clase define objeto de tipo Item para inventario y queue.
 */
#ifndef ITEM_H_
#define ITEM_H_

#include <iostream>
#include <string>

using namespace std;

//Declaracion de clase Item
class Item {
    //Declaracion de variables
    private:
        string name;
        int amount;
        int type;
        bool throwable;

    //Declaracion de los métodos que va a tener el objeto
    public:
        Item() : name(""), amount(0), type(0), throwable(0) {}

        Item(string n, int c, int t, bool thr) : name(n), amount(c), type(t), throwable(thr) {}

        // Getters
        string getName() { return name; }
        int getAmount() { return amount; }
        int getType() { return type; }
        bool getThrowable() { return throwable; }

        // Setters
        void setAmount(int c) { amount = c; }
};
#endif
