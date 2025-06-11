#ifndef ALGORITMOJUGADOR_H_INCLUDED
#define ALGORITMOJUGADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMLARGO 3
#define TAMALTO 3
#define CRUZ 'X'
#define CIRCULO 'O'


int Ganador(char[][TAMALTO], int, int);
void SeleccionarMejorMovimiento(char [][TAMALTO], int, int, char, char);
#endif // ALGORITMOJUGADOR_H_INCLUDED
