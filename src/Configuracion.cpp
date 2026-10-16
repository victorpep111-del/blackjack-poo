#include "Configuracion.h"
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
using namespace std;

namespace {
    // Quita espacios y '\r' (por si el archivo se guardo con saltos CRLF)
    string recortar(const string& s) {
        size_t i = s.find_first_not_of(" \t\r\n");
        if (i == string::npos) return "";
        size_t j = s.find_last_not_of(" \t\r\n");
        return s.substr(i, j - i + 1);
    }

    // Lee la siguiente linea no vacia
    string leerLinea(ifstream& f, const string& que) {
        string linea;
        while (getline(f, linea)) {
            linea = recortar(linea);
            if (!linea.empty()) return linea;
        }
        throw runtime_error("setup.txt incompleto: falta " + que);
    }

    int aEntero(const string& s, const string& que) {
        char* fin = nullptr;
        long v = strtol(s.c_str(), &fin, 10);
        if (s.empty() || *fin != '\0')
            throw runtime_error("Valor no numerico para " + que + ": '" + s + "'");
        return static_cast<int>(v);
    }
}

Configuracion::Configuracion()
    : numJugadores(1), valorGanar(21) {
    palos[0] = "Corazones";
    palos[1] = "Diamantes";
    palos[2] = "Treboles";
    palos[3] = "Picas";
}

void Configuracion::cargarDesdeArchivo(const string& ruta) {
    ifstream f(ruta);
    if (!f.is_open()) {
        throw runtime_error("No se pudo abrir " + ruta);
    }

    int nj = aEntero(leerLinea(f, "numero de jugadores"), "numero de jugadores");
    string lineaPalos = leerLinea(f, "nombres de los palos");
    int vg = aEntero(leerLinea(f, "valor para ganar"), "valor para ganar");

    if (nj < 1 || nj > 10)
        throw runtime_error("El numero de jugadores debe estar entre 1 y 10.");
    if (vg < 5 || vg > 100)
        throw runtime_error("El valor para ganar debe estar entre 5 y 100.");

    string nuevos[4];
    stringstream ss(lineaPalos);
    string palo;
    int i = 0;
    while (i < 4 && getline(ss, palo, ',')) {
        palo = recortar(palo);
        if (!palo.empty()) nuevos[i++] = palo;
    }
    if (i != 4)
        throw runtime_error("Se necesitan exactamente 4 nombres de palos separados por comas.");

    // Solo se asigna si todo fue valido
    numJugadores = nj;
    valorGanar = vg;
    for (int k = 0; k < 4; ++k) palos[k] = nuevos[k];
}

int Configuracion::getNumJugadores() const { return numJugadores; }
string Configuracion::getPalo(int i) const {
    if (i < 0 || i > 3) throw out_of_range("Indice de palo fuera de rango.");
    return palos[i];
}
int Configuracion::getValorGanar() const { return valorGanar; }
