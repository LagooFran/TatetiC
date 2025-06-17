#include "UtilidadesTateti.h"
#include "AlgoritmoJugador.h"

#define CHARAINT(c) \
    (((c) >= '0' && (c) <= '9') ? ((c) - '0') : \
    ((c) >= 'A' && (c) <= 'Z') ? ((c) - 'A' + 10) : -1)


void MostrarTablero(char tablero[][TAMLARGO]){
    int fil, col;

    printf("\n");

    for(fil=0; fil<TAMALTO; fil++){
        printf("\t");
        for(col=0; col<TAMLARGO; col++){
            printf(GRIS);
            if(tablero[fil][col] == CRUZ) printf(ROJO);
            if(tablero[fil][col] == CIRCULO) printf(AZUL);
            printf(" %c ",tablero[fil][col]);
            printf(RESETCOLOR);
            if(col != TAMLARGO-1) printf("║");
        }
        int i=0;
        printf("\n\t");
        if(fil!=TAMALTO-1){
            while(i<TAMLARGO-1){
                printf("═══╬");
                i++;
            }
            printf("═══");
        }
        printf("\n");
    }
    printf("\n\n\n");
}




void ReiniciarTablero(char tablero[][TAMLARGO]){
    int cont=49, band = 0, fil, col;
    for(fil=0; fil<TAMALTO; fil++){
        for(col=0; col<TAMLARGO; col++){
            if(cont>57 && band == 0){
                cont = 65;
                band = 1;
            }
            if(cont == (int)(CIRCULO) || cont == (int)(CRUZ)) cont++;
            tablero[fil][col] = ((char)cont);
            cont++;
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

int EmpezarPartida(char tablero[][TAMLARGO]){ ///Inicia la partida, retorna quien tendra el primer movimiento 0 = jugador, 1 = maquina.
    int aleatorio;
    srand(time(NULL));
    ReiniciarTablero(tablero);
    printf("\n\n%sINICIO DE PARTIDA!!%s\n\n", AMARILLO, RESETCOLOR);
    aleatorio = (rand() % (1 - 0 + 1)) + 0;
    return aleatorio;
}

int CasilleroVacio(char tablero[][TAMLARGO], int fil, int col){
    return (tablero[fil][col]!= CRUZ && tablero[fil][col]!= CIRCULO);
}

void EscribirTablero(char tablero[][TAMLARGO], int fil, int col, char caracter){
    tablero[fil][col] = caracter;
}


void RegistrarMovimientoJugador(char tablero[][TAMLARGO], int filas, int columnas, char jugadorChar){
    int bandera, fila, columna, casillero, limite;
    char movimiento;
    limite = (TAMALTO*TAMLARGO + 56);
    do{
        bandera = 0;
        while (getchar() != '\n'); /// Limpio el buffer
        movimiento = getchar();
        if((!ESMAYUSCULA(movimiento) && !ESNUMERO(movimiento)) || movimiento == '0' || (int)movimiento>=limite){
                printf("\nMovimiento invalido, reingrese: ");
                bandera = 1;
        }
        else{
            if(movimiento>= (int)(CIRCULO)) movimiento--; ///Salteo la letra 'O'
            casillero = CHARAINT(movimiento);       ///Convierto el numero en fila y columna
                    fila = (casillero-1)/TAMLARGO;
                    columna = (casillero-1)%TAMLARGO;
        }
        if (!CasilleroVacio(tablero, fila, columna) && bandera == 0){ ///Verifico si esta vacia la posicion
            printf("\nCasillero ocupado, reingrese: ");
            bandera = 1;
        }
    } while(bandera == 1);
    EscribirTablero(tablero, fila, columna, jugadorChar); ///Escribo en el tablero
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

