#include "UtilidadesTateti.h"
#include "AlgoritmoJugador.h"


void MostrarTablero3x3(char tablero[][TAMALTO]){
    int fil, col;

    printf("\n");

    for(fil=0; fil<3; fil++){
        printf("\t");
        for(col=0; col<3; col++){
            printf(GRIS);
            if(tablero[fil][col] == CRUZ) printf(ROJO);
            if(tablero[fil][col] == CIRCULO) printf(AZUL);
            printf(" %c ",tablero[fil][col]);
            printf(RESETCOLOR);
            if(col != TAMALTO-1) printf("║");
        }
        if(fil != TAMLARGO-1) printf("\n\t═══╬═══╬═══\n");
    }
    printf("\n\n\n");
}

void ReiniciarTablero(char tablero[][TAMALTO], int filas, int columnas){
    int cont=0;
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            cont++;
            tablero[i][j] = ((char)cont) + '0';
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
    printf("\n\n%sINICIO DE PARTIDA!!%s\n\n", AMARILLO, RESETCOLOR);
    aleatorio = (rand() % (1 - 0 + 1)) + 0;
    return aleatorio;
}

int CasilleroVacio(char tablero[][TAMALTO], int fil, int col){
    return (tablero[fil][col]!= CRUZ && tablero[fil][col]!= CIRCULO);
}

void EscribirTablero(char tablero[][TAMALTO], int fil, int col, char caracter){
    tablero[fil][col] = caracter;
}


void RegistrarMovimientoJugador(char tablero[][TAMALTO], int filas, int columnas, char jugadorChar){
    int numero, bandera, fila, columna;
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
}

int OrdenarPuntosDescendente(void *a, void *b){
    jugador jug1 = *(jugador*)a;
    jugador jug2 = *(jugador*)b;

    if(jug1.puntos > jug2.puntos)
        return -1;
    if(jug1.puntos < jug2.puntos)
        return 1;
    return 0;
}

