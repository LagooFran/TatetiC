#include "AlgoritmoJugador.h"


int Ganador(char tablero[][TAMALTO], int filas, int columnas){ ///retorna 1 = si gano la O |-1 = si gano la X | 0 = no hay ganador todavia | 2 = empate

    int x, o;
    ///recorro filas
    x = 0;
    o = 0;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            printf("%c", tablero[i][j]);
            if(tablero[i][j] == 'X'){
                printf("Suma X\n");
                x ++;
            }
            else if(tablero[i][j] == 'O'){
                printf("Suma O\n");
                o ++;
            }


            if(x == 3){
                return -1;
            }
            else if(o == 3){
                return 1;
            }
        }
        x = 0;
        o = 0;
    }

    x = 0;
    o = 0;
    ///recorro columnas
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(tablero[j][i] == 'X'){
                x ++;
            }
            else if(tablero[j][i] == 'O'){
                o ++;
            }

            if(x == 3){
                return -1;
            }
            else if(o == 3){
                return 1;
            }
        }
        x = 0;
        o = 0;
    }

    ///recorro diagonal principal
    for(int i = 0; i < filas; i++){
        if(tablero[i][i] == 'X'){
            x ++;
        }
        else if(tablero[i][i] == 'O'){
            o ++;
        }

        if(x == 3){
            return -1;
        }
        else if(o == 3){
            return 1;
        }

    }

    x = 0;
    o = 0;

    ///recorro diagonal inversa
    for(int i = 3; i > filas; i--){
        if(tablero[i][i] == 'X'){
            x ++;
        }
        else if(tablero[i][i] == 'O'){
            o ++;
        }


        if(x == 3){
            return -1;
        }
        else if(o == 3){
            return 1;
        }
    }

    x = 0;
    o = 0;

    ///Si no hay un ganador
    ///compruebo si hay casillas sin completar
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(tablero[i][j] == ' '){
                return 0; ///todavia hay movimientos posibles
            }
        }
    }

    return 2; ///Empate
}

void SeleccionarMejorMovimiento(char tablero[][TAMALTO], int filas, int columnas, char maquinaChar){
///elige el mejor movimiento y pone un "maquinaChar" en el lugar correspondiente.
///si el medio esta libre elige ese movimiento.
///si el jugador esta por ganar elige el movimiento de bloqueo.
///sino elige movimientos al azar priorizando filas donde tenga ya casilleros ocupados.

}
