#ifndef JUEGO_H
#define JUEGO_H

#include "Baraja.h"
#include "Jugador.h"
#include "Dealer.h"
#include "Configuracion.h"

class Juego {
private:
    Configuracion config;
    Baraja baraja;

    static const int MAX_JUG = 10;
    Jugador jugadores[MAX_JUG];
    int numJugadores;
    Dealer dealer;

    int rondas, victorias, derrotas, empates, blackjacks;

    void mostrarBienvenida() const;
    void pedirNombres();
    void mostrarReglas() const;
    void prepararRonda();
    void mostrarMesa() const;
    void anunciarResultado(int pj, int pd, const string& nombre);

public:
    Juego();
    Juego(const Configuracion& cfg);
    ~Juego();

    void ronda();
    void mostrarEstadisticas() const;
    void iniciar();
};

#endif