#include "AlgoritmoJugador.h"
#include "UtilidadesTateti.h"

int Ganador(char tablero[][TAMLARGO]){ ///retorna 1 = si gano la O |-1 = si gano la X | 0 = no hay ganador todavia | 2 = empate

    int x=0, o=0, fil, col, linea;
    ///recorro filas
    linea = TAMLARGO;
    for(fil = 0; fil < TAMALTO; fil++){
        for(col = 0; col < TAMLARGO; col++){
            if(tablero[fil][col] == CRUZ) x ++;
            else if(tablero[fil][col] == CIRCULO) o ++;

            if(x == linea) return GANACRUZ;
            else if(o == linea) return GANACIRCULO;
        }
        x = 0;
        o = 0;
    }

    x = 0;
    o = 0;
    ///recorro columnas
    linea = TAMALTO;
    for(col = 0; col < TAMLARGO; col++){
        for(fil = 0; fil < TAMALTO; fil++){
            if(tablero[fil][col] == CRUZ) x ++;
            else if(tablero[fil][col] == CIRCULO) o ++;

            if(x == linea) return GANACRUZ;
            else if(o == linea) return GANACIRCULO;
        }
        x = 0;
        o = 0;
    }

    ///recorro diagonal principal
    if (TAMALTO>TAMLARGO) linea = TAMALTO;
    else linea = TAMLARGO;
    for(fil = 0; fil < TAMALTO; fil++){
        if(tablero[fil][fil] == CRUZ) x ++;
        else if(tablero[fil][fil] == CIRCULO) o ++;

        if(x == linea) return -1;
        else if(o == linea) return 1;
    }

    x = 0;
    o = 0;
    ///recorro diagonal inversa
    if (TAMALTO>TAMLARGO) linea = TAMALTO;
    else linea = TAMLARGO;
    col = TAMLARGO;
    fil = 0;
    while (col>0 && fil<TAMALTO){
        if(tablero[fil][col] == CRUZ){
            x ++;
            printf("X:%d, col:%d, fil:%d\n",x, fil, col);
        }
        else if(tablero[fil][col] == CIRCULO) o ++;
        col--;
        fil++;
    }

        if(x == linea) return GANACRUZ;
        else if(o == linea) return GANACIRCULO;

    x = 0;
    o = 0;

    ///Si no hay un ganador
    ///compruebo si hay casillas sin completar
    for(int fil = 0; fil < TAMALTO; fil++){
        for(int col = 0; col < TAMLARGO; col++){
            if(tablero[fil][col] != CRUZ && tablero[fil][col] != CIRCULO) return 0; ///todavia hay movimientos posibles
        }
    }
    return EMPATE; ///Empate
}


int encontrarJugadaGanadora(char tablero[TAMALTO][TAMLARGO], int* fil, int* col, char caracter) {
    char aux;
    for (int i = 0; i < TAMALTO; i++) {
        for (int j = 0; j < TAMLARGO; j++) {
            if (CasilleroVacio(tablero, i, j)) {
                aux = tablero[i][j];
                tablero[i][j] = caracter; ///Reemplazo con el caracter y verifico si hay un ganador
                if (Ganador(tablero) == 1 || Ganador(tablero) == -1) { ///Si hay un ganador, significa que ese movimiento permite ganar
                    *fil = i;
                    *col = j;
                    tablero[i][j] = aux; /// Revierto
                    return 1;
                }
                tablero[i][j] = aux; ///Revierto
            }
        }
    }
    return 0;
}


void SeleccionarMejorMovimiento(char tablero[][TAMLARGO], int filas, int columnas, char maquinaChar, char jugadorChar){
    int fil, col;

    ///si el medio esta libre elige ese movimiento.
    if (CasilleroVacio(tablero,TAMALTO/2,TAMLARGO/2)){
        EscribirTablero(tablero, TAMALTO/2, TAMLARGO/2, maquinaChar);
        return;
    }

    ///si la maquina puede ganar elige ese movimiento.
    if (encontrarJugadaGanadora(tablero, &fil, &col, maquinaChar) == 1){
        EscribirTablero(tablero, fil, col, maquinaChar);
        return;
    }

    ///si el jugador esta por ganar elige el movimiento de bloqueo.
    if (encontrarJugadaGanadora(tablero, &fil, &col, jugadorChar) == 1){
        EscribirTablero(tablero, fil, col, maquinaChar);
        return;
    }

    ///Elige un movimiento al azar.
    srand(time(NULL));
    while (1) {
        fil = rand() % TAMALTO;
        col = rand() % TAMLARGO;
        if (CasilleroVacio(tablero, fil, col)) {
            EscribirTablero(tablero, fil, col, maquinaChar);
            return;
        }
    }
}
