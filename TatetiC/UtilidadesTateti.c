#include "UtilidadesTateti.h"

void MostrarTablero3x3(char tablero[][TAMALTO]){
    printf("\n \t\t%c | %c | %c\n", tablero[0][0], tablero[0][1], tablero[0][2]);
    printf("\t\t---------\n");
    printf(" \t\t%c | %c | %c\n", tablero[1][0], tablero[1][1], tablero[1][2]);
    printf("\t\t---------\n");
    printf(" \t\t%c | %c | %c\n\n", tablero[2][0], tablero[2][1], tablero[2][2]);
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
    printf("\n\nIncio de partida!!\n\n");
    aleatorio = (rand() % (1 - 0 + 1)) + 0;
    return aleatorio;
}

int CasilleroVacio(char tablero[][TAMALTO], int fil, int col){
    return (tablero[fil][col]==' ');
}

void EscribirTablero(char tablero[][TAMALTO], int fil, int col, char caracter){
    tablero[fil][col] = caracter;
}


void RegistrarMovimientoJugador(char tablero[][TAMALTO], int filas, int columnas, char jugadorChar){
    int numero, bandera, fila, columna;
    printf("\n\n[1][2][3]\n[4][5][6]\n[7][8][9]\n");
    printf("Seleccione su movimiento: ");
    do{
        scanf("%d",&numero);
        fila = (numero-1)/3;    ///Convierto el numero en fila y columna
        columna = (numero-1)%3;
        if (numero<=0 || numero>=10){
            printf("\nMovimiento invalido, reingrese: ");
            bandera = 1;
        }
        else if (!CasilleroVacio(tablero, fila, columna)){
            printf("\nCasillero ocupado, reingrese: ");
            bandera = 1;
        }
        else{
            EscribirTablero(tablero, fila, columna, jugadorChar); ///Escribo en el tablero
            bandera = 0;
        }
    } while(bandera == 1);
///el usuario elige un movimiento y coloca un "jugador char" en la posicion seleccionada. Verifica que sea posible.
}


