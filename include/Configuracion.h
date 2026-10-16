#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <string>
using namespace std;

class Configuracion {
private:
    int numJugadores;
    string palos[4];
    int valorGanar;

public:
    Configuracion();
    void cargarDesdeArchivo(const string& ruta);

    int getNumJugadores() const;
    string getPalo(int i) const;
    int getValorGanar() const;
};

#endif