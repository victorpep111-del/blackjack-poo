#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>  
#include "Participante.h"

class Jugador : public Participante {
public:
    Jugador();
    explicit Jugador(const string& nombre);
    ~Jugador() override;

    void jugarTurno(Baraja& baraja, int valorGanar) override;
};

#endif 