#include "UtilidadesTateti.h"
#include "AlgoritmoJugador.h"
#include "Registros.h"


void MostrarJugador(void * jug){
    jugador auxJug;
    jugador *pAuxJug = &auxJug;
    pAuxJug = (jugador *)jug;
    printf("Nombre: %s\n", pAuxJug->nombre);
}

void MostrarJugadorYPuntos(void * jug){
    jugador auxJug;
    jugador *pAuxJug = &auxJug;
    pAuxJug = (jugador *)jug;
    printf("Nombre: %-30s\tPuntos: %d\n", pAuxJug->nombre, pAuxJug->puntos);
}


///cuando prueba el programa funciona bien pero se queda en bucle infinito porque nadie hace ningun movimiento (las funciones no estan programadas todavia)
///para probar el programa sin hacer movimientos setear el tablero de alguna manera inicialmente y comentar todos los ReiniciarTablero()
/// 1. hay que hacer las funciones de movimiento. RegistrarMovimientoUsuario y SeleccionarMejorMovimiento (movimiento de la maquina)
/// 2. una vez terminado los movimiento solo habria que hacer la integracion con la API y estaria listo

int main()
{
    char seleccion;
    int basura;
    int salir = 0;
   // int puntosGanados = 0;
    int turno;
    int ganador = 0;
    int bandera = 0;
    int offline = 0;
    int cantPartidasXJug = 1, contPartidas = 0;
    char tablero[TAMALTO][TAMLARGO];
    char jugadorChar, maquinaChar;
    int validador;
    int c;
    char colorJugador[15], colorMaquina[15];
    ReiniciarTablero(tablero);

    jugador jug;
    jugador *pJug = &jug;
    grupo grup;
    grupo *pGrup = &grup;

    tLista listaJug;
    tLista *pListaJug = &listaJug;
    CrearLista(pListaJug);

    tLista listaJugFinal;
    tLista *pListaJugFinal = &listaJugFinal;
    CrearLista(pListaJugFinal);

    tLista listaPartidas;
    tLista *pListaPartidas = &listaPartidas; ///lista para guardar las partidas y luego guardarlas en el txt
    CrearLista(pListaPartidas);

    partidaResumen resFinal = {0};
    partidaResumen *pResFinal = &resFinal; ///estructura para guardar en la lista de partidas

    printf("Cargando...\n");

    cantPartidasXJug = ObtenerCantidadDePartidas();

    if(cantPartidasXJug < 1){
        printf("La cantidad de partidas por jugador es incorrecta por favor verifique el archivo config. Volviendo a la configuracion por defecto (1)\n");
        cantPartidasXJug = 1;
        system("pause");
    }

    if(Validar_API()!= 200){
        printf("\nLa URL que apunta la API no es valida o no se puede establecer la conexion. Forzando Modo OFFLINE. Sus partidas no seran guardadas\n");
        offline = 1;
        system("pause");
    }

    system("chcp 65001"); ///Setea la consola de windows para poder usar caracteres UTF-8
    system("cls");

    ///Menu para tateti
    printf("%s\tTatetiC!%s", AMARILLO,RESETCOLOR);
    if(offline == 1){
        printf(" %s|| Modo Offline.%s", ROJO, RESETCOLOR);
    }
    while(salir!= 1){
        if (bandera == 0) printf("\n\n\n[A] Comenzar a jugar\n[B] Ver ranking\n[C] Salir\n\n");
        seleccion = getchar();
        while ((basura = getchar()) != '\n' && basura != EOF) { ///Reviso si quedó algo en el buffer
            seleccion = 'X'; ///Opcion invalida
        }


        switch(AMAYUSCULA(seleccion)){
            case 'A':
                system("cls");
                ///cargo los datos del grupo en struct
                printf("Ingrese el nombre del grupo: ");
                scanf(" %s", pGrup->nombreGrupo);
                pGrup->totalPuntos = 0;

                ///el struct grupo contiene una lista de jugadores
                printf("\nIngrese la cantidad de jugadores: ");
                validador = scanf(" %d", &pGrup->cantJugadores);
                while(validador != 1){
                    while ((c = getchar()) != '\n' && c != EOF);//Limpia el buffer de teclado
                    printf("\nEl valor debe ser numerico...");
                    printf("\nIngrese la cantidad de jugadores: ");
                    validador = scanf(" %d", &pGrup->cantJugadores);
                }
                printf("\nCarga de jugadores:\n");
                CrearLista(pListaJug);

                ///cargo una lista auxiliar de jugadores
                for(int i = 0; i<pGrup->cantJugadores; i++){
                    printf("Ingrese el nombre del jugador %d: ", i+1);
                    scanf(" %s", pJug->nombre);
                    pJug->puntos = 0;
                    PonerAlFinal(pListaJug, pJug, sizeof(jugador));
                }
                system("cls");
                ///Una vez los jugadores estan cargados debo randomizar el orden en el que jugaran.
                RandomizarLista(pListaJug);
                ///muestro el orden de los jugadores
                printf("GRUPO: %s\n\n", pGrup->nombreGrupo);
                printf("Orden de juego: \n");
                RecorrerLista(pListaJug, MostrarJugador, sizeof(jugador));
                system("pause");

                ///empiezo el loop de juego
                VaciarLista(pListaJugFinal);
                CrearLista(pListaJugFinal);
                while(ListaVacia(pListaJug) != 1){
                    ///al inicio de cada partido saco el primer jugador de la lista inicial.
                    SacarPrimeroLista(pListaJug, pJug);

                    while(contPartidas < cantPartidasXJug){
                    ///partida jugdador
                    turno = EmpezarPartida(tablero);

                    memset(&resFinal, 0, sizeof(partidaResumen));
                    if(turno == 0){
                        maquinaChar = CRUZ;
                        jugadorChar = CIRCULO;
                        strcpy(colorJugador, AZUL);
                        strcpy(colorMaquina, ROJO);
                        printf("Jugador %s: %s%c%s\n", pJug->nombre, colorJugador, jugadorChar, RESETCOLOR);
                        printf("Maquina: %s%c%s\n", colorMaquina, maquinaChar, RESETCOLOR);
                    }
                    else{
                        jugadorChar = CRUZ;
                        maquinaChar = CIRCULO;
                        strcpy(colorJugador, ROJO);
                        strcpy(colorMaquina, AZUL);
                        printf("Jugador %s: %s%c%s\n", pJug->nombre, colorJugador, jugadorChar, RESETCOLOR);
                        printf("Maquina: %s%c%s\n", colorMaquina, maquinaChar, RESETCOLOR);
                    }
                    MostrarTablero(tablero);
                    while(ganador == 0){


                        ///despues de cada movimiento compruebo si hay un ganador o empate.
                        if(turno == 0){
                            ///juega la maquina
                            printf("Movimiento de la %sMAQUINA%s:\n", colorMaquina, RESETCOLOR);
                            system("pause");
                            SeleccionarMejorMovimiento(tablero, TAMLARGO, TAMALTO, maquinaChar, jugadorChar);
                            ///cambio el turno para que luego juegue el jugador
                            turno = 1;
                        }
                        else{ ///turno = 1
                            ///juega el jugador
                            printf("Movimiento de jugador %s%s%s: ", colorJugador, pJug->nombre, RESETCOLOR);
                            RegistrarMovimientoJugador(tablero, TAMLARGO, TAMALTO, jugadorChar);
                            ///cambio el turno pra que luego juegue la maquina.
                            turno = 0;
                        }
                        MostrarTablero(tablero);
                        ganador = Ganador(tablero);
                        system("pause");

                    }
                    strcpy(pResFinal->jugador, pJug->nombre);
                    if(ganador == GANACRUZ){
                        if(jugadorChar == CRUZ){
                            system("cls");
                            printf("Gana el jugador\n");
                            //pJug->puntos = /*pJug->puntos+*/3;
                            strcpy(pResFinal->ganador, pJug->nombre);
                            pResFinal->puntosGanados = 3;
                            pGrup->totalPuntos += 3;
                            pJug->puntos += 3;
                            system("pause");
                        }
                        else{
                            system("cls");
                            printf("Gana la maquina\n");
                            //pJug->puntos = /*pJug->puntos*/-1;
                            strcpy(pResFinal->ganador, "Maquina");
                            pResFinal->puntosGanados = -1;
                            pGrup->totalPuntos += -1;
                            pJug->puntos += -1;
                            system("pause");
                        }

                    }
                    else if(ganador == GANACIRCULO){
                        if(jugadorChar == CIRCULO){
                            system("cls");
                            printf("Gana el jugador\n");
                            //pJug->puntos = /*pJug->puntos+*/3;
                            strcpy(pResFinal->ganador, pJug->nombre);
                            pResFinal->puntosGanados = 3;
                            pGrup->totalPuntos += 3;
                            pJug->puntos += 3;
                            system("pause");
                        }
                        else{
                            system("cls");
                            printf("Gana la maquina\n");
                            //pJug->puntos = /*pJug->puntos*/-1;
                            strcpy(pResFinal->ganador, "Maquina");
                            pResFinal->puntosGanados = -1;
                            pGrup->totalPuntos += -1;
                            pJug->puntos += -1;
                            system("pause");
                        }

                    }
                    else if(ganador == EMPATE){
                        system("cls");
                        printf("Empate\n");
                        //pJug->puntos = /*pJug->puntos +*/2;
                        strcpy(pResFinal->ganador, "Empate: ");
                        strcat(pResFinal->ganador, pJug->nombre);
                        pResFinal->puntosGanados = 2;
                        pGrup->totalPuntos += 2;
                        pJug->puntos += 2;
                        system("pause");

                    }

                    ///copio el tablero al final de la partida en la lista de partidas jugadas
                    for(int i = 0; i < TAMALTO; i++) {
                        for(int j = 0; j < TAMLARGO; j++) {
                            pResFinal->tableroFinal[i][j] = tablero[i][j];
                        }
                    }

                    PonerAlFinal(pListaPartidas, pResFinal, sizeof(partidaResumen));

                    ///cada vez que termina un juego actualizo los puntos del jugador
                   // pJug->puntos = pJug->puntos;// + puntosGanados; //Esto duplica los puntos?
                    ///y agrego al jugador con su puntuacion a la lista de grupo

                    ReiniciarTablero(tablero);
                    ganador = 0;
                    contPartidas++;
                    ///fin partida jugador
                    }
                    PonerAlFinal(pListaJugFinal, pJug, sizeof(jug));
                    contPartidas = 0;
                }

                ///Una vez terminados todos los juegos agrego la lista al struct del grupo
                pGrup->jugadores = pListaJugFinal;
                ///muestro los jugadores y sus puntos
                RecorrerLista(pGrup->jugadores, MostrarJugadorYPuntos, sizeof(jugador));
                printf("\nPuntos conseguidos por el grupo %s%s%s: %d", colorJugador, pGrup->nombreGrupo, RESETCOLOR, pGrup->totalPuntos);
                ///una vez se termina con todo eso habria que usar pListaJugFinal para contactar con la api y crear el archivo de registro
                GenerarArchivoResumen(pListaPartidas, pListaJugFinal);
                CrearJSON(pListaJugFinal);
                bandera = 0;
                while ((c = getchar()) != '\n' && c != EOF);//Limpia el buffer de teclado
                break;

            case 'B':
                if(offline != 1){
                    system("cls");
                    //Ordeno la lista
                    VaciarLista(pListaJugFinal);
                    CargarJugadoresDesdeAPI(pListaJugFinal);
                    ordenar(pListaJugFinal,OrdenarPuntosDescendente);
                    printf("RANKING: \n");
                    RecorrerLista(pListaJugFinal, MostrarJugadorYPuntos, sizeof(jugador));
                    VaciarLista(pListaJugFinal);
                    printf("\n\n");
                    bandera = 0;
                    break;
                }
                else{
                    system("cls");
                    printf("%sRanking Desactivado. Usted esta en modo Offline\n%s", ROJO, RESETCOLOR);
                    system("pause");
                    break;
                }


            case 'C':
                printf("Saliendo...");
                VaciarLista(pListaJug);
                VaciarLista(pListaJugFinal);
                VaciarLista(pListaPartidas);
                salir = 1;
                break;
            default:
                printf("Opcion Invalida, reingrese:");
                bandera = 1;
                break;
        }
    }
}
