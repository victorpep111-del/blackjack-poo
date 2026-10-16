#include "Juego.h"
#include "Excepciones.h"
#include "Utilidades.h"
#include <iostream>
using namespace std;

Juego::Juego()
    : numJugadores(1), rondas(0), victorias(0),
      derrotas(0), empates(0), blackjacks(0) {}

Juego::Juego(const Configuracion& cfg)
    : config(cfg), numJugadores(cfg.getNumJugadores()),
      rondas(0), victorias(0), derrotas(0), empates(0), blackjacks(0) {
    if (numJugadores > MAX_JUG) numJugadores = MAX_JUG;
    if (numJugadores < 1) numJugadores = 1;
    for (int i = 0; i < numJugadores; ++i) {
        jugadores[i].setNombre("Jugador " + to_string(i + 1));
        jugadores[i].setValorGanar(cfg.getValorGanar());
    }
    dealer.setValorGanar(cfg.getValorGanar());
}

Juego::~Juego() {
    cout << "\n[Destructor de Juego] Gracias por jugar.\n";
}

void Juego::mostrarBienvenida() const {
    cout << "==========================================\n";
    cout << "        BLACKJACK - POO EN C++\n";
    cout << "==========================================\n";
    cout << "CONFIGURACION:\n";
    cout << "  Jugadores: " << numJugadores << "\n";
    cout << "  Palos: ";
    for (int i = 0; i < 4; ++i) cout << config.getPalo(i) << " ";
    cout << "\n  Valor para ganar: " << config.getValorGanar() << "\n";
    cout << "==========================================\n";
}

void Juego::pedirNombres() {
    cout << "\nIngresa los nombres de los " << numJugadores << " jugadores:\n";
    for (int i = 0; i < numJugadores; ++i) {
        cout << "Jugador " << (i + 1) << ": ";
        string nombre;
        if (!getline(cin, nombre)) {
            throw EntradaInvalidaException("Se cerro la entrada.");
        }
        if (!nombre.empty()) jugadores[i].setNombre(nombre);
    }
}

void Juego::mostrarReglas() const {
    cout << "\n--- REGLAS ---\n"
         << " - Palos: ";
    for (int i = 0; i < 4; ++i) cout << config.getPalo(i) << " ";
    cout << "\n - Valor para ganar: " << config.getValorGanar() << "\n"
         << " - As vale 1 u 11, J/Q/K valen 10\n"
         << " - Dealer pide hasta " << (config.getValorGanar() - 4) << "\n"
         << " - Cada jugador juega su turno contra el dealer\n";
}

void Juego::prepararRonda() {
    if (baraja.quedanCartas() < MINIMO_PARA_BARAJAR + 4 * numJugadores) {
        baraja.reiniciar();
    }
    for (int i = 0; i < numJugadores; ++i) jugadores[i].limpiarMano();
    dealer.limpiarMano();
}

void Juego::mostrarMesa() const {
    cout << "\n=========== MESA ===========\n";
    dealer.mostrarMano();
    for (int i = 0; i < numJugadores; ++i) {
        jugadores[i].mostrarMano();
    }
    cout << "============================\n";
}

void Juego::anunciarResultado(int pj, int pd, const string& nombre) {
    int vg = config.getValorGanar();
    cout << "  " << nombre << " (" << pj << ") vs Dealer (" << pd << "): ";
    if (pj > vg) { cout << "PIERDE (se paso)\n"; ++derrotas; }
    else if (pd > vg) { cout << "GANA (dealer se paso)\n"; ++victorias; }
    else if (pj > pd) { cout << "GANA\n"; ++victorias; }
    else if (pd > pj) { cout << "PIERDE\n"; ++derrotas; }
    else { cout << "EMPATE\n"; ++empates; }
}

void Juego::ronda() {
    try {
        prepararRonda();
        ++rondas;
        cout << "\n############ RONDA " << rondas << " ############\n";
        cout << "Valor para ganar: " << config.getValorGanar() << "\n";

        // Repartir 2 cartas a cada jugador y al dealer
        for (int i = 0; i < 2; ++i) {
            for (int k = 0; k < numJugadores; ++k) jugadores[k].recibirCarta(baraja);
            dealer.recibirCarta(baraja);
        }

        mostrarMesa();

        // Turno de cada jugador
        for (int i = 0; i < numJugadores; ++i) {
            cout << "\n### Turno de " << jugadores[i].getNombre() << " ###\n";
            jugadores[i].jugarTurno(baraja, config.getValorGanar());
        }

        // Turno del dealer (juega ultimo)
        dealer.jugarTurno(baraja, config.getValorGanar());

        // Resultados
        cout << "\n--- RESULTADOS ---\n";
        int pd = dealer.calcularPuntos();
        for (int i = 0; i < numJugadores; ++i) {
            int pj = jugadores[i].calcularPuntos();
            anunciarResultado(pj, pd, jugadores[i].getNombre());
        }

    } catch (const BarajaVaciaException& e) {
        cout << "\n[Error] " << e.what() << " Rebarajando.\n";
        baraja.reiniciar();
    }
}

void Juego::mostrarEstadisticas() const {
    cout << "\n--------- ESTADISTICAS ---------\n"
         << " Rondas jugadas: " << rondas << "\n"
         << " Victorias: " << victorias << "\n"
         << " Derrotas: " << derrotas << "\n"
         << " Empates: " << empates << "\n"
         << " Cartas en baraja: " << baraja.quedanCartas() << "\n"
         << "--------------------------------\n";
}

void Juego::iniciar() {
    mostrarBienvenida();
    pedirNombres();

    int op = 0;
    do {
        cout << "\n===== MENU =====\n"
             << " 1) Jugar ronda\n"
             << " 2) Estadisticas\n"
             << " 3) Reglas\n"
             << " 4) Salir\n";
        op = leerEntero("Elige: ", 1, 4);
        switch (op) {
            case 1: ronda(); break;
            case 2: mostrarEstadisticas(); break;
            case 3: mostrarReglas(); break;
            case 4: cout << "\nHasta pronto!\n"; break;
        }
    } while (op != 4);
    mostrarEstadisticas();
}