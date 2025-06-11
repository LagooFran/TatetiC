#include "AlgoritmoJugador.h"
#include "UtilidadesTateti.h"

int Ganador(char tablero[][TAMALTO], int filas, int columnas){ ///retorna 1 = si gano la O |-1 = si gano la X | 0 = no hay ganador todavia | 2 = empate

    int x=0, o=0, j, i;
    ///recorro filas
    for(i = 0; i < filas; i++){
        for(j = 0; j < columnas; j++){
            //printf("%c", tablero[i][j]);
            if(tablero[i][j] == CRUZ){
                //printf("Suma X\n");
                x ++;
            }
            else if(tablero[i][j] == CIRCULO){
                //printf("Suma O\n");
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
    for(i = 0; i < filas; i++){
        for(j = 0; j < columnas; j++){
            if(tablero[j][i] == CRUZ){
                x ++;
            }
            else if(tablero[j][i] == CIRCULO){
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
    for(i = 0; i < filas; i++){
        if(tablero[i][i] == CRUZ){
            x ++;
        }
        else if(tablero[i][i] == CIRCULO){
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
    j = columnas;
    for(i = 0; i < filas; i++){
        j--;
            if(tablero[i][j] == CRUZ){
                x ++;
            }
            else if(tablero[i][j] == CIRCULO){
                o ++;
            }
        }

        if(x == 3){
            return -1;
        }
        else if(o == 3){
            return 1;
        }

    x = 0;
    o = 0;

    ///Si no hay un ganador
    ///compruebo si hay casillas sin completar
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(tablero[i][j] != CRUZ && tablero[i][j] != CIRCULO){
                return 0; ///todavia hay movimientos posibles
            }
        }
    }
    return 2; ///Empate
}


int encontrarJugadaGanadora(char tablero[3][3], int* fil, int* col, char caracter) {
    char aux;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (CasilleroVacio(tablero, i, j)) {
                aux = tablero[i][j];
                tablero[i][j] = caracter; ///Reemplazo con el caracter y verifico si hay un ganador
                if (Ganador(tablero, 3, 3) == 1 || Ganador(tablero,3,3) == -1) { ///Si hay un ganador, significa que ese movimiento permite ganar
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


void SeleccionarMejorMovimiento(char tablero[][TAMALTO], int filas, int columnas, char maquinaChar, char jugadorChar){
    int fil, col;

    ///si el medio esta libre elige ese movimiento.
    if (CasilleroVacio(tablero,1,1)){
        EscribirTablero(tablero, 1, 1, maquinaChar);
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
        fil = rand() % 3;
        col = rand() % 3;
        if (CasilleroVacio(tablero, fil, col)) {
            EscribirTablero(tablero, fil, col, maquinaChar);
            return;
        }
    }
}
