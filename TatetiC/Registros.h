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
#define MAXLINEA 300

void CrearJSON(tLista *);
void AgregarJugadores(tLista *, cJSON *);
void ObtenerFecha(char *, size_t);
void RecuperarDatos(grupo *, const char *);
void CargarJugadoresDesdeAPI(tLista*);


#endif // REGISTROS_H_INCLUDED
