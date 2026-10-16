#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include "Constantes.h"
using namespace std;

int leerEntero(const string& mensaje, int minimo, int maximo);

extern string nombresPalos[4];
void setNombresPalos(const string palos[4]);

#endif