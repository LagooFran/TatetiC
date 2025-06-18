#ifndef ALGORITMOJUGADOR_H_INCLUDED
#define ALGORITMOJUGADOR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UtilidadesTateti.h"
#define CRUZ 'X'
#define CIRCULO 'O'
#define GANACIRCULO 1
#define GANACRUZ -1
#define EMPATE 2
#define TAM_NOMBRE 300
#define TAM_FECHA 100


int Ganador(char[][TAMLARGO]);
void SeleccionarMejorMovimiento(char [][TAMLARGO], int, int, char, char);
#endif // ALGORITMOJUGADOR_H_INCLUDED
