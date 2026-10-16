#ifndef PARTICIPANTE_H
#define PARTICIPANTE_H

#include <string>       
#include "Carta.h"      
#include "Baraja.h"     

using namespace std;
class Participante {
private:
    string nombre;

protected:
    static const int MAX_MANO = 20;
    Carta mano[MAX_MANO];
    int cantidadMano;
    int valorGanar;   // objetivo configurable (para decidir el valor del As)

public:
    Participante();
    explicit Participante(const string& nombre);
    virtual ~Participante();

    const string& getNombre() const;
    void setNombre(const string& nuevoNombre);
    void setValorGanar(int v);
    int getCantidadMano() const;
    Carta getCartaMano(int i) const;

    void recibirCarta(const Carta& carta);
    void recibirCarta(Baraja& baraja);

    virtual void limpiarMano();
    int calcularPuntos() const;                    
    bool tieneBlackjack(int valorGanar) const;        
    bool sePaso(int valorGanar) const;              

    virtual void mostrarMano() const;
    virtual void jugarTurno(Baraja& baraja, int valorGanar) = 0; 
};

#endif