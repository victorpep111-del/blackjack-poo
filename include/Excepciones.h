// ============================================================================
// Excepciones.h - Excepciones personalizadas del juego
// ============================================================================
#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

#include <stdexcept>
#include <string>
using namespace std;

class BarajaVaciaException : public runtime_error {
public:
    BarajaVaciaException();
};

class EntradaInvalidaException : public runtime_error {
public:
    explicit EntradaInvalidaException(const string& mensaje);
};

#endif