#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{
    void *data;
    size_t tamData;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tLista;

int CrearLista(tLista *);
int ListaVacia(const tLista *);
int ListaLlena(const tLista *, size_t);
int VaciarLista(tLista *);
int PonerAlComienzo(tLista *, void *, size_t);
int PonerAlFinal(tLista *, void *, size_t);
int PonerEnLista(tLista *, void *, size_t, int);
int VerUltimoLista(const tLista *, void *);
int VerPrimeroLista(const tLista *, void *);
int SacarPrimeroLista(tLista *, void *);
int SacarUltimoLista(const tLista *, void *);
void RecorrerLista(tLista *, void (*accion)(void *), size_t);



#endif // LISTA_H_INCLUDED
