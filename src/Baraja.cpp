// ============================================================================
// Baraja.cpp - Implementacion de la clase Baraja
// ============================================================================
#include "Baraja.h"
#include "Excepciones.h"
#include <algorithm>
using namespace std;

void Baraja::construirMazo() {
    cantidad = 0;
    for (int p = 0; p < 4; ++p) { 
        for (int r = 1; r <= 13; ++r) {
            cartas[cantidad++] = Carta(p, static_cast<Rango>(r));
        }
    }
}

Baraja::Baraja() : cantidad(0), generador(random_device{}()) {
    construirMazo();
    barajar();
}

Baraja::Baraja(unsigned int semilla) : cantidad(0), generador(semilla) {
    construirMazo();
    barajar();
}

Baraja::~Baraja() {
    cantidad = 0;
}

void Baraja::barajar() {
    shuffle(cartas, cartas + cantidad, generador);
}

Carta Baraja::repartir() {
    if (cantidad == 0) {
        throw BarajaVaciaException();
    }
    return cartas[--cantidad];
}

void Baraja::repartir(int n, Carta* salida) {
    for (int i = 0; i < n; ++i) {
        salida[i] = repartir();
    }
}

int Baraja::quedanCartas() const {
    return cantidad;
}

void Baraja::reiniciar() {
    construirMazo();
    barajar();
}

bool Baraja::contiene(const Carta& c) const {
    for (int i = 0; i < cantidad; ++i) {
        if (cartas[i].getPalo() == c.getPalo() &&
            cartas[i].getRango() == c.getRango()) {
            return true;
        }
    }
    return false;
}

bool Baraja::quitarCarta(const Carta& c) {
    for (int i = 0; i < cantidad; ++i) {
        if (cartas[i].getPalo() == c.getPalo() &&
            cartas[i].getRango() == c.getRango()) {
            // Desplazar los elementos hacia la izquierda
            for (int j = i; j < cantidad - 1; ++j) {
                cartas[j] = cartas[j + 1];
            }
            --cantidad;
            return true;
        }
    }
    return false;
}

int Baraja::getCantidad() const { return cantidad; }

Carta Baraja::getCarta(int i) const {
    if (i < 0 || i >= cantidad) {
        throw out_of_range("Indice fuera de rango.");
    }
    return cartas[i];
}