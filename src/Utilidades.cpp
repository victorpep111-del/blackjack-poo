#include "Utilidades.h"
#include "Constantes.h"
#include "Excepciones.h"
#include <iostream>
#include <limits>
using namespace std;

// Nombres personalizados de palos
string nombresPalos[4] = { "Corazones", "Diamantes", "Treboles", "Picas" };

void setNombresPalos(const string palos[4]) {
    for (int i = 0; i < 4; ++i) nombresPalos[i] = palos[i];
}

// Excepciones
BarajaVaciaException::BarajaVaciaException()
    : runtime_error("La baraja no tiene mas cartas.") {}

EntradaInvalidaException::EntradaInvalidaException(const string& mensaje)
    : runtime_error(mensaje) {}

// aTexto con nombres personalizados
string aTexto(Palo palo) {
    int idx = static_cast<int>(palo);
    if (idx >= 0 && idx < 4) return nombresPalos[idx];
    return "?";
}

string aTexto(Rango rango) {
    switch (rango) {
        case Rango::As:     return "As";
        case Rango::Jota:   return "J";
        case Rango::Reina:  return "Q";
        case Rango::Rey:    return "K";
        default:            return to_string(static_cast<int>(rango));
    }
}

int leerEntero(const string& mensaje, int minimo, int maximo) {
    while (true) {
        cout << mensaje;
        int valor;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (valor >= minimo && valor <= maximo) return valor;
            cout << "  >> Opcion fuera de rango.\n";
        } else {
            if (cin.eof()) throw EntradaInvalidaException("Entrada cerrada.");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  >> Entrada invalida.\n";
        }
    }
}