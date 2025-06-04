#include "UtilidadesTateti.h"

void MostrarTablero3x3(char tablero[][TAMALTO]){
    printf(" \t\t%c | %c | %c\n", tablero[0][0], tablero[0][1], tablero[0][2]);
    printf("\t\t---------\n");
    printf(" \t\t%c | %c | %c\n", tablero[1][0], tablero[1][1], tablero[1][2]);
    printf("\t\t---------\n");
    printf(" \t\t%c | %c | %c\n", tablero[2][0], tablero[2][1], tablero[2][2]);
}

void ReiniciarTablero(char tablero[][TAMALTO], int filas, int columnas){
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            tablero[i][j] = ' ';
        }
    }
}

void RandomizarLista(tLista *lista){
    jugador *auxJug;
    int aleatorio;
    srand(time(NULL));
    while(*lista){
        auxJug = (*lista)->data;
        if((*lista)->sig != NULL){
            aleatorio = (rand() % (1 - 0 + 1)) + 0;
            if(aleatorio){
                auxJug = (*lista)->data;
                (*lista)->data = (*lista)->sig->data;
                (*lista)->sig->data = auxJug;
            }
        }

        lista = &(*lista)->sig;
    }

}

int EmpezarPartida(char tablero[][TAMALTO], int filas, int columnas){ ///Inicia la partida, retorna quien tendra el primer movimiento 0 = jugador, 1 = maquina.
    int aleatorio;
    srand(time(NULL));
    ReiniciarTablero(tablero, filas, columnas);
    printf("Incio de partida!!\n");
    aleatorio = (rand() % (1 - 0 + 1)) + 0;
    return aleatorio;
}

void RegistrarMovimientoJugador(char tablero[][TAMALTO], int filas, int columnas, char jugadorChar){
///el usuario elige un movimiento y coloca un "jugador char" en la posicion seleccionada. Verifica que sea posible.
}
