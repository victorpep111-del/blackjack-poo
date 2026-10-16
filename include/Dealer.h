#ifndef DEALER_H
#define DEALER_H

#include <string> 
#include "Participante.h"

class Dealer : public Participante {
private:
    bool segundaCartaOculta;

public:
    Dealer();
    explicit Dealer(const string& nombre);
    ~Dealer() override;

    void revelarCarta();
    bool cartaOculta() const;

    void limpiarMano() override;
    void mostrarMano() const override;
    void jugarTurno(Baraja& baraja, int valorGanar) override;
};

#endif