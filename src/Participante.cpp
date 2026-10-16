// ============================================================================
// Participante.cpp - Implementacion de la clase abstracta Participante
// ============================================================================
#include "Participante.h"
#include "Constantes.h"
#include <stdexcept>
#include <iostream>
using namespace std;

Participante::Participante() : nombre("Sin nombre"), cantidadMano(0), valorGanar(21) {}

Participante::Participante(const string& n) : nombre(n), cantidadMano(0), valorGanar(21) {}

Participante::~Participante() {}

const string& Participante::getNombre() const { return nombre; }

void Participante::setNombre(const string& n) {
    if (n.empty()) throw invalid_argument("Nombre vacio.");
    nombre = n;
}

void Participante::setValorGanar(int v) { valorGanar = v; }

int Participante::getCantidadMano() const { return cantidadMano; }

Carta Participante::getCartaMano(int i) const {
    if (i < 0 || i >= cantidadMano) {
        throw out_of_range("Indice fuera de rango.");
    }
    return mano[i];
}

void Participante::recibirCarta(const Carta& carta) {
    if (cantidadMano >= MAX_MANO) {
        throw runtime_error("La mano esta llena.");
    }
    mano[cantidadMano++] = carta;
}

void Participante::recibirCarta(Baraja& baraja) {
    recibirCarta(baraja.repartir());
}

void Participante::limpiarMano() {
    cantidadMano = 0;
}

int Participante::calcularPuntos() const {
    int total = 0, ases = 0;
    for (int i = 0; i < cantidadMano; ++i) {
        total = total + mano[i];
        if (mano[i].getRango() == Rango::As) ++ases;
    }
    if (ases > 0 && total + 10 <= valorGanar) total += 10;
    return total;
}

bool Participante::tieneBlackjack(int valorGanar) const {
    return cantidadMano == 2 && calcularPuntos() == valorGanar;
}

bool Participante::sePaso(int valorGanar) const {
    return calcularPuntos() > valorGanar;
}

void Participante::mostrarMano() const {
    cout << "  " << nombre << ": ";
    for (int i = 0; i < cantidadMano; ++i) {
        cout << mano[i] << " ";
    }
    cout << "(Puntos: " << calcularPuntos() << ")\n";
}