#ifndef REGISTROS_H_INCLUDED
#define REGISTROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <curl/curl.h>
#include "cJSON.h"
#include "UtilidadesTateti.h"
#define TAM_NOMBRE 300
#define TAM_FECHA 100


void CrearJSON(grupo *);
void AgregarJugadores(tLista *, cJSON *);
void ObtenerFecha(char *, int, int);
void RecuperarDatos(grupo *, const char *);


#endif // REGISTROS_H_INCLUDED
