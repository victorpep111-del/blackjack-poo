#include "Carta.h"
#include <stdexcept>
using namespace std;

Carta::Carta() : palo(0), rango(Rango::As) {}

Carta::Carta(int p, Rango r) : palo(p), rango(r) {}

Carta::Carta(int p, int numero) : palo(p), rango(Rango::As) {
    if (numero < 1 || numero > 13) {
        throw invalid_argument("El numero de carta debe estar entre 1 y 13.");
    }
    rango = static_cast<Rango>(numero);
}

int Carta::getPalo() const { return palo; }
Rango Carta::getRango() const { return rango; }

int Carta::valor() const {
    switch (rango) {
        case Rango::Jota:
        case Rango::Reina:
        case Rango::Rey: return 10;
        default:         return static_cast<int>(rango);
    }
}

int Carta::operator+(const Carta& otra) const {
    return valor() + otra.valor();
}

int operator+(int acumulado, const Carta& c) {
    return acumulado + c.valor();
}

ostream& operator<<(ostream& os, const Carta& c) {
    os << "[" << aTexto(c.rango) << " de " << aTexto(static_cast<Palo>(c.palo)) << "]";
    return os;
}