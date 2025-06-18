#ifndef UTILIDADESTATETI_H_INCLUDED
#define UTILIDADESTATETI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Lista.h"
#define TAMLARGO 3
#define TAMALTO 3
#define TAMTEXTO 300
#define MAXLINEA 300
#define ROJO "\033[31m"
#define AZUL "\033[36m"
#define GRIS "\033[38;5;238m"
#define AMARILLO "\033[33m"
#define RESETCOLOR "\033[0m"
#define ESLETRA(x)   ( (('a'<=(x) && (x)<='z') || ('A'<=(x) && (x)<='Z')) ? 1 : 0 )
#define ESMAYUSCULA(x) (('A'<=(x) && (x)<='Z') ? 1 : 0 )
#define AMAYUSCULA(x) ( (('a'<=(x) && (x)<='z')) ? ((x)-32) : (x) )
#define ESNUMERO(x)   ( ('0'<=(x) && (x)<='9')? 1 : 0 )
#define ESOPCION(x)   ( (('A'<=(x) && (x)<='C')) ? 1 : 0 )


typedef struct{
    char nombre[TAMTEXTO];
    int puntos;
}jugador;

typedef struct{
    char nombreGrupo[TAMTEXTO];
    int totalPuntos;
    int cantJugadores;
    tLista *jugadores;
}grupo;

typedef struct{
    char jugador[TAMTEXTO];
    char ganador[TAMTEXTO];
    char tableroFinal[TAMALTO][TAMLARGO];
    int puntosGanados;
}partidaResumen;



void MostrarTablero3x3(char[][TAMLARGO]);
void MostrarTablero(char [][TAMLARGO]);
void ReiniciarTablero(char[][TAMLARGO]);
int EmpezarPartida(char [][TAMLARGO]);
void RandomizarLista(tLista *);
void RegistrarMovimientoJugador(char [][TAMLARGO], int, int, char);
void EscribirTablero(char [][TAMLARGO], int, int, char);
int CasilleroVacio(char [][TAMLARGO], int, int);
int OrdenarPuntosDescendente(void *, void *);
void GenerarArchivoResumen(tLista *, tLista *);
int ObtenerCantidadDePartidas();

#endif // UTILIDADESTATETI_H_INCLUDED
