// ============================================================================
// Jugador.cpp - Implementacion de la clase Jugador
// ============================================================================
#include "Jugador.h"
#include "Utilidades.h"
#include <iostream>
using namespace std;

Jugador::Jugador() : Participante("Jugador") {}
Jugador::Jugador(const string& n) : Participante(n) {}
Jugador::~Jugador() {}

void Jugador::jugarTurno(Baraja& baraja, int valorGanar) {
    cout << "\n--- Turno de " << getNombre() << " ---\n";
    while (!sePaso(valorGanar) && calcularPuntos() < valorGanar) {
        mostrarMano();
        int op = leerEntero("1)Pedir 2)Plantarse: ", 1, 2);
        if (op == 1) {
            recibirCarta(baraja);
            cout << "  Pediste: " << mano[cantidadMano - 1] << "\n";
        } else break;
    }
    mostrarMano();
}