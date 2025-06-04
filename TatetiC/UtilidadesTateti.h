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

#endif // UTILIDADESTATETI_H_INCLUDED
