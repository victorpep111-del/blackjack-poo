#ifndef BARAJA_H
#define BARAJA_H

#include <random>         
#include "Carta.h"         

using namespace std;

class Baraja {
private:
    static const int MAX_CARTAS = 52;
    Carta cartas[MAX_CARTAS];
    int cantidad;
    mt19937 generador;

    void construirMazo();

public:
    Baraja();
    explicit Baraja(unsigned int semilla);
    ~Baraja();

    void barajar();
    Carta repartir();
    void repartir(int n, Carta* salida);
    int quedanCartas() const;
    void reiniciar();

    bool contiene(const Carta& c) const;
    bool quitarCarta(const Carta& c);
    int getCantidad() const;
    Carta getCarta(int i) const;
};

#endif