#include "UtilidadesTateti.h"
#include "AlgoritmoJugador.h"

#define CHARAINT(c) \
    (((c) >= '0' && (c) <= '9') ? ((c) - '0') : \
    ((c) >= 'A' && (c) <= 'Z') ? ((c) - 'A' + 10) : -1)


void MostrarTablero(char tablero[][TAMLARGO]){
    int fil, col;

    system("cls");
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

void ObtenerFecha2(char *fecha, size_t tam){


    time_t t;
    struct tm *tm_info;

    t = time(NULL);
    tm_info = localtime(&t); // Obtiene la fecha y hora local

    strftime(fecha, tam, "%Y-%m-%d-%H-%M", tm_info);

    return;
}

void  CargarRanking(void *datos, void *contexto){
    char temp[TAMTEXTO*2+20];

    jugador *pJug = (jugador *)datos;
    FILE *archivo = (FILE *)contexto;
    strcpy(temp, "");
    sprintf(temp, "Jugador: %s Puntos: %d \n", pJug->nombre, pJug->puntos);
    fputs(temp, archivo);
}

void GenerarArchivoResumen(tLista *listaPartidas, tLista *listaJugadores){

    char fecha[TAM_FECHA];
    char nombreArchivo[TAM_NOMBRE];
    char temp[TAMTEXTO*2+20];
    char tempPuntos[4];
    partidaResumen part;
    partidaResumen *pPart = &part;

    ObtenerFecha2(fecha, TAM_FECHA);
    strcpy(nombreArchivo, "informe_juego_");
    strcat(nombreArchivo, fecha);
    strcat(nombreArchivo, ".txt");

    FILE *archivo;
    if(!(archivo = fopen(nombreArchivo, "a"))){ //ACA FALTA VALIDAR SI SE ABRIO BIEN EL ARCHIVO
        printf("\n Error al generar el archivo LOG");
        //No retorno nada para que igualmente envie los datos a la api y libere memoria
    }
    if (archivo) {
        while(!ListaVacia(listaPartidas)){


            SacarPrimeroLista(listaPartidas, pPart);

            strcat(pPart->jugador, " vs Maquina");
            fputs(pPart->jugador, archivo);
            fputs("\n", archivo);

            strcpy(temp, "");
            strcat(temp, "Resultado/Ganador: ");
            strcat(temp, pPart->ganador);
            fputs(temp, archivo);
            fputs("\n", archivo);

            ///printeo el tablero al archivo
            for (int i = 0; i < TAMALTO; i++) {
                fprintf(archivo, "  ");
                for (int j = 0; j < TAMLARGO; j++) {
                    fprintf(archivo, "%c ", pPart->tableroFinal[i][j]);
                }
                fprintf(archivo, "\n");
            }

            fprintf(archivo, "\n");
            strcpy(temp, "");
            strcat(temp, "Cambio en puntos: ");
            sprintf(tempPuntos, "%d", pPart->puntosGanados);
            strcat(temp, tempPuntos);
            fputs(temp, archivo);
            fputs("\n", archivo);
            fprintf(archivo, "-------------------------------");
            fprintf(archivo, "\n");

        }

        fprintf(archivo, "Ranking Jugadores Local: \n");
        ordenar(listaJugadores, OrdenarPuntosDescendente);
        RecorrerListaEnContexto(listaJugadores, CargarRanking, archivo);
        fclose(archivo);
    }

}

int ObtenerCantidadDePartidas(){
    char linea[MAXLINEA];
    int cantPart;

    //Abro el archivo para recuperar la url
    FILE* pArch;
    if(!(pArch = (fopen("Config.TXT", "rt"
                        )))){
        printf("\n\nError al abrir el Config.TXT\n");
        return -1;
    }

    //Obtengo la  primera linea
    fgets(linea, MAXLINEA, pArch);
    //Obtengo la segunda linea
    fgets(linea, MAXLINEA, pArch);

    //la segunda linea contiene el numero de partidas por jugador sin ningun extra.
    sscanf(linea, "%d", &cantPart);

    fclose(pArch); //Cierro el archivo porque no lo uso mas
    return cantPart;
}

