#include "UtilidadesTateti.h"
#include "AlgoritmoJugador.h"


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
    printf("Nombre: %s, Puntos: %d\n", pAuxJug->nombre, pAuxJug->puntos);
}

///cuando prueba el programa funciona bien pero se queda en bucle infinito porque nadie hace ningun movimiento (las funciones no estan programadas todavia)
///para probar el programa sin hacer movimientos setear el tablero de alguna manera inicialmente y comentar todos los ReiniciarTablero()
/// 1. hay que hacer las funciones de movimiento. RegistrarMovimientoUsuario y SeleccionarMejorMovimiento (movimiento de la maquina)
/// 2. una vez terminado los movimiento solo habria que hacer la integracion con la API y estaria listo

int main()
{
    int seleccion;
    int salir = 0;
    int puntosGanados = 0;
    int turno;
    int ganador = 0;
    char tablero[TAMLARGO][TAMALTO];
    char jugadorChar, maquinaChar;
    ReiniciarTablero(tablero, TAMALTO, TAMLARGO);
    jugador jug;
    jugador *pJug = &jug;
    grupo grup;
    grupo *pGrup = &grup;
    tLista listaJug;
    tLista *pListaJug = &listaJug;
    tLista listaJugFinal;
    tLista *pListaJugFinal = &listaJugFinal;


    system("chcp 65001"); ///Setea la consola de windows para poder usar caracteres UTF-8
    system("cls");

    ///Menu para tateti
    while(salir!=1){
        printf("TatetiC!\n\n");
        printf("[1] Comenzar a jugar\n[2] Ver ranking\n[3] Salir\n");
        scanf("%d", &seleccion);


        switch(seleccion){
            case 1:
                system("cls");
                ///cargo los datos del grupo en struct
                printf("Ingrese el nombre del grupo: ");
                scanf(" %s", pGrup->nombreGrupo);
                pGrup->totalPuntos = 0;

                ///el struct grupo contiene una lista de jugadores
                printf("\nIngrese la cantidad de jugadores: ");
                scanf(" %d", &pGrup->cantJugadores);
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

                ///empiezo el loop de juego
                CrearLista(pListaJugFinal);
                while(ListaVacia(pListaJug) != 1){
                    ///al inicio de cada partido saco el primer jugador de la lista inicial.
                    SacarPrimeroLista(pListaJug, pJug);
                    turno = EmpezarPartida(tablero, TAMLARGO, TAMALTO);
                    if(turno == 0){
                        maquinaChar = CRUZ;
                        jugadorChar = CIRCULO;
                        printf("Jugador %s: %s%c%s\n", pJug->nombre, AZUL, jugadorChar, RESETCOLOR);
                        printf("Maquina: %s%c%s\n", ROJO, maquinaChar, RESETCOLOR);
                    }
                    else{
                        jugadorChar = CRUZ;
                        maquinaChar = CIRCULO;
                        printf("Jugador %s: %s%c%s\n", pJug->nombre, ROJO, jugadorChar, RESETCOLOR);
                        printf("Maquina: %s%c%s\n", AZUL, maquinaChar, RESETCOLOR);
                    }
                    MostrarTablero3x3(tablero);
                    while(ganador == 0){


                        ///despues de cada movimiento compruebo si hay un ganador o empate.
                        if(turno == 0){
                            ///juega la maquina
                            printf("Movimiento de la maquina:\n");
                            SeleccionarMejorMovimiento(tablero, TAMLARGO, TAMALTO, maquinaChar, jugadorChar);
                            ///cambio el turno para que luego juegue el jugador
                            turno = 1;
                        }
                        else{ ///turno = 1
                            ///juega el jugador
                            RegistrarMovimientoJugador(tablero, TAMLARGO, TAMALTO, jugadorChar);
                            ///cambio el turno pra que luego juegue la maquina.
                            turno = 0;
                        }
                        MostrarTablero3x3(tablero);
                        ganador = Ganador(tablero, TAMLARGO, TAMALTO);

                    }

                    if(ganador == -1){
                        if(jugadorChar == CRUZ){
                            printf("Gana el jugador\n");
                            pJug->puntos = pJug->puntos+3;
                        }
                        else{
                            printf("Gana la maquina\n");
                            pJug->puntos = pJug->puntos-1;
                        }

                    }
                    else if(ganador == 1){
                        if(jugadorChar == CIRCULO){
                            printf("Gana el jugador\n");
                            pJug->puntos = pJug->puntos+3;
                        }
                        else{
                            printf("Gana la maquina\n");
                            pJug->puntos = pJug->puntos-1;
                        }

                    }
                    else if(ganador == 2){
                        printf("Empate");
                        pJug->puntos = pJug->puntos+2;
                    }


                    ///cada vez que termina un juego actualizo los puntos del jugador
                    pJug->puntos = pJug->puntos + puntosGanados;
                    ///y agrego al jugador con su puntuacion a la lista de grupo
                    PonerAlFinal(pListaJugFinal, pJug, sizeof(jug));
                    ReiniciarTablero(tablero, 3, 3);
                    ganador = 0;
                }

                ///Una vez terminados todos los juegos agrego la lista al struct del grupo
                pGrup->jugadores = pListaJugFinal;
                ///muestro los jugadores y sus puntos
                RecorrerLista(pGrup->jugadores, MostrarJugadorYPuntos, sizeof(jugador));
                ///una vez se termina con todo eso habria que usar pListaJugFinal para contactar con la api y crear el archivo de registro

                break;

            case 2:
                printf("op2");
                break;
            case 3:
                printf("Saliendo...");
                salir = 1;
                break;
            default:
                printf("Opcion Invalida\n");
                break;
        }
    }
}
