#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <string>
using namespace std;

// Constantes del juego           
const int PLANTA_DEALER = 17;         
const int MINIMO_PARA_BARAJAR = 15;   

enum class Palo { Corazones, Diamantes, Treboles, Picas };

enum class Rango {
    As = 1, Dos, Tres, Cuatro, Cinco, Seis, Siete,
    Ocho, Nueve, Diez, Jota, Reina, Rey
};

enum class Resultado {
    VictoriaJugador,
    VictoriaDealer,
    Empate,
    BlackjackJugador,
    BlackjackDealer
};

string aTexto(Palo palo);
string aTexto(Rango rango);

#endif 