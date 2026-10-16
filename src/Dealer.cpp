// ============================================================================
// Dealer.cpp - Implementacion de la clase Dealer
// ============================================================================
#include "Dealer.h"
#include "Constantes.h"
#include <iostream>
using namespace std;

Dealer::Dealer() : Participante("Dealer"), segundaCartaOculta(true) {}
Dealer::Dealer(const string& n) : Participante(n), segundaCartaOculta(true) {}
Dealer::~Dealer() {}

void Dealer::revelarCarta() { segundaCartaOculta = false; }
bool Dealer::cartaOculta() const { return segundaCartaOculta; }

void Dealer::limpiarMano() {
    Participante::limpiarMano();
    segundaCartaOculta = true;
}

void Dealer::mostrarMano() const {
    cout << "  " << getNombre() << ": ";
    for (int i = 0; i < cantidadMano; ++i) {
        if (segundaCartaOculta && i == 1) {
            cout << "[??] ";
        } else {
            cout << mano[i] << " ";
        }
    }
    if (segundaCartaOculta) {
        cout << "(Puntos: ?)\n";
    } else {
        cout << "(Puntos: " << calcularPuntos() << ")\n";
    }
}

void Dealer::jugarTurno(Baraja& baraja, int valorGanar) {
    cout << "\n--- Turno de " << getNombre() << " ---\n";
    revelarCarta();
    mostrarMano();

    int planta = valorGanar - 4;   // 17 si se gana con 21
    while (calcularPuntos() < planta && baraja.quedanCartas() > 0) {
        recibirCarta(baraja);
        cout << "  " << getNombre() << " pide: " << mano[cantidadMano - 1] << "\n";
        mostrarMano();
    }

    if (sePaso(valorGanar)) {          
        cout << "  >> " << getNombre() << " se paso (BUST).\n";
    } else {
        cout << "  >> " << getNombre() << " se planta con "
             << calcularPuntos() << ".\n";
    }
}