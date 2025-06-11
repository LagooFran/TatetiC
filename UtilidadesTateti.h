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
#define ROJO "\033[31m"
#define AZUL "\033[36m"
#define GRIS "\033[38;5;238m"
#define AMARILLO "\033[33m"
#define RESETCOLOR "\033[0m"


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



void MostrarTablero3x3(char[][TAMALTO]);
void ReiniciarTablero(char[][TAMALTO], int, int);
int EmpezarPartida(char [][TAMALTO], int, int);
void RandomizarLista(tLista *);
void RegistrarMovimientoJugador(char [][TAMALTO], int, int, char);
void EscribirTablero(char [][TAMALTO], int, int, char);
int CasilleroVacio(char [][TAMALTO], int, int);

#endif // UTILIDADESTATETI_H_INCLUDED
