#ifndef SECUENCIADOR_H_INCLUDED
#define SECUENCIADOR_H_INCLUDED

#include <vector>
#include "cEntidad.h"
#include "cJugador.h"
#include "cTiro.h"
#include "cTiroEnemigo.h"
#include "cEnemigo1.h"
#include "cEnemigo2.h"
#include "cEnemigo3.h"
#include "cEnemigo4.h"
#include "cJefeFinal.h"
#include "cJFEscudo.h"
#include "cTiroBoss.h"
#include "ctime"
#include "mapa.h"
#include "interfaz.h"
#include "nivelTuto1.h"
#include "nivelTuto2.h"
#include "nivelTuto3.h"
#include "nivel1.h"
#include "nivel2.h"
#include "nivel3.h"
#include "nivel4.h"
#include "nivelBoss.h"
#include "nivelFinal.h"
#include "perder.h"
//////////
int secuenciador(bool flagTuto){
    int nivel;
    if(flagTuto)
        nivel = 7;
    else
        nivel = 1;
    Player jugador;
    Tiro tiro;
    while(nivel){

        switch(nivel){
        case -2:
        return 2;
        break;

        case -1:
        nivel = perder();
        break;

        ///NIVELES
        case 1:
        jugador.setX(20);
        jugador.setY(300);
        jugador.setVida(5);
        nivel = nivel1(&jugador, &tiro);
        break;

        case 2:
        nivel = nivel2(&jugador, &tiro);
        break;

        case 3:
        nivel = nivel3(&jugador, &tiro);
        break;

        case 4:
        nivel = nivel4(&jugador, &tiro);
        break;

        case 5:
        nivel = nivelBoss(&jugador, &tiro);
        break;

        case 6:
        nivel = Final(&jugador);
        break;
        ///TUTO
        case 7:
        nivel = nivelTuto1(&jugador, &tiro);
        break;

        case 8:
        nivel = nivelTuto2(&jugador, &tiro);
        break;

        case 9:
        nivel = nivelTuto3(&jugador, &tiro);
        break;
        }
    }
    return nivel;
}


#endif // SECUENCIADOR_H_INCLUDED
