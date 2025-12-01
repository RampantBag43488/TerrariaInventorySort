#ifndef ITEM_H_
#define ITEM_H_

#include <iostream>
#include <string>

using namespace std;

class Item {
    private:
        string name;
        int amount;
        int type;
        bool throwable;

    public:
        // Constructor vacío
        Item() : name(""), amount(0), type(0), throwable(0) {}

        // Constructor con parámetros
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