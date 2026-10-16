#include "Juego.h"
#include "Configuracion.h"
#include "Utilidades.h"
#include "Excepciones.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    Configuracion config;
    try {
        config.cargarDesdeArchivo("setup.txt");
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        cerr << "Usando valores por defecto.\n";
    }

    string palos[4];
    for (int i = 0; i < 4; ++i) palos[i] = config.getPalo(i);
    setNombresPalos(palos);

    try {
        Juego juego(config);
        juego.iniciar();
    } catch (const EntradaInvalidaException& e) {
        cout << "\n[Entrada cerrada] " << e.what() << "\n";
    } catch (const exception& e) {
        cerr << "\n[Error] " << e.what() << "\n";
        return 1;
    }
    return 0;
}