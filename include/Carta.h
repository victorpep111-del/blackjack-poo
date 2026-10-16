#ifndef CARTA_H
#define CARTA_H

#include <iostream>
#include "Constantes.h"
using namespace std;

class Carta {
private:
    int palo;      
    Rango rango;

public:
    Carta();
    Carta(int palo, Rango r);
    Carta(int palo, int numero);

    int getPalo() const;   
    Rango getRango() const;
    int valor() const;

    int operator+(const Carta& otra) const;
    friend int operator+(int acumulado, const Carta& c);
    friend ostream& operator<<(ostream& os, const Carta& c);
};

#endif