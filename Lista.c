#include "Lista.h"

int CrearLista(tLista *lista){
    ///Seteo puntero en null.
    *lista = NULL;
    return 0; ///No hubo errores.
}

int ListaVacia(const tLista *lista){
    ///verifico si el puntero es nulo.
    if(*lista==NULL){
        return 1; ///esta vacia.
    }
    return 0; ///no esta vacia.
}

int ListaLlena(const tLista *lista, size_t tamData){
    /// *lista no se usa solo agregado por compatibilidad.
    tNodo *nod = (tNodo *)malloc(sizeof(tNodo));
    if(nod == NULL){
        return 1; ///No se puede alojar memoria para un nodo.
    }
    void *data = malloc(tamData);
    if(data == NULL){
        return 1; ///Se pudo alojar el nodo pero no la info.
    }
    free(data);
    free(nod);
    return 0; ///Hay espacio suficiente.
}

int VaciarLista(tLista *lista){

    int cont = 0;
    tNodo *aux = *lista;

    while(*lista != NULL){
        *lista = aux->sig;
        free(aux->data);
        free(aux);
        aux = *lista;
        cont++;
    }

    return cont; ///Se borraron todos los nodos. Retorna la cantidad de nodos borrados.
}

int PonerAlComienzo(tLista *lista, void *data, size_t tamData){
    ///chequeo lista llena.. esto deberia copiarse al codigo de la funcion porque es una primitiva.
    if(ListaLlena(lista, tamData)){
        return 1; ///La lista esta llena no puedo alojar mas memoria.
    }

    tNodo *nuevoNodo = (tNodo *)malloc(sizeof(tNodo));
    void *nuevaData = malloc(tamData);
    memcpy(nuevaData, data, tamData);
    nuevoNodo->data = nuevaData;
    nuevoNodo->tamData = tamData;

    nuevoNodo -> sig = *lista;
    *lista = nuevoNodo;

    return 0; ///elemento agregado con exito
}

int PonerAlFinal(tLista *lista, void *data, size_t tamData){
    tNodo *lecturaActual;
    tNodo *nuevoNodo;
    void *nuevaData;
    if(ListaVacia(lista)){
        ///tendria que usar el cod directamente porque es primitiva pero me da paja
        PonerAlComienzo(lista, data, tamData);
    }
    else{
        lecturaActual = *lista;
        while(lecturaActual->sig != NULL){
            lecturaActual = lecturaActual->sig;
        }
        if(ListaLlena(lista, tamData)){
            return 1;
        }
        else{
            nuevoNodo = (tNodo*)malloc(sizeof(tNodo));
            nuevaData = malloc(tamData);
            memcpy(nuevaData, data, tamData);
            nuevoNodo->data = nuevaData;
            nuevoNodo->sig = NULL;
            nuevoNodo->tamData = tamData;
            lecturaActual->sig = nuevoNodo;
            return 0;
        }
    }
    return 0;
}


int PonerEnLista(tLista *lista, void *data, size_t tamData, int pos){
    tNodo *nuevoNodo;
    void *nuevaData;
    int posLectura = 0;
    tNodo *lecturaActual;
    tNodo *lecturaAnterior;
    ///chequeo si la pos es la ultima o esta en el medio o se pasa...
    if(pos < 0){

        return 1; ///error

    } ///tomando 0 como el primer lugar
    else if(pos == 0 || ListaVacia(lista)){ ///si selecciona la primera pos o esta vacia
        ///tendria que usar el cod directamente porque es primitiva pero me da paja
        PonerAlComienzo(lista, data, tamData);
        return 0;
    }
    else{
        lecturaActual = *lista;
        while(posLectura != pos){
            if(lecturaActual->sig == NULL){
                if(posLectura < pos){
                    ///tendria que usar el cod directamente porque es primitiva pero me da paja
                    PonerAlFinal(lista, data, tamData);
                    return 0;
                }
                else{
                    ///esto podria ser una funcion .. InsertarEntre ?
                    nuevoNodo = (tNodo*)malloc(sizeof(tNodo));
                    nuevaData = malloc(tamData);
                    memcpy(nuevaData, data, tamData);
                    nuevoNodo->data = nuevaData;
                    nuevoNodo->sig = lecturaActual;
                    nuevoNodo->tamData = tamData;
                    lecturaAnterior->sig = nuevoNodo;
                    return 0;
                }
            }
            lecturaAnterior = lecturaActual;
            lecturaActual = lecturaActual->sig;
            posLectura++;
        }
        ///esto podria ser una funcion .. InsertarEntre ?
        nuevoNodo = (tNodo*)malloc(sizeof(tNodo));
        nuevaData = malloc(tamData);
        memcpy(nuevaData, data, tamData);
        nuevoNodo->data = nuevaData;
        nuevoNodo->sig = lecturaActual;
        nuevoNodo->tamData = tamData;
        lecturaAnterior->sig = nuevoNodo;
        return 0;
    }
    return 0;
}

int VerUltimoLista(const tLista *lista, void *dataDest){

    tNodo *lecturaActual;

    ///tendria que usar el cod directamente porque es primitiva pero me da paja
    if(ListaVacia(lista)){
        return 1; ///La lista esta vacia no hay ultimo
    }
    else{
        lecturaActual = *lista;
        while(lecturaActual->sig != NULL){
            lecturaActual = lecturaActual->sig;
        }
        memcpy(dataDest, lecturaActual->data, lecturaActual->tamData);
    }
    return 0;
}


int VerPrimeroLista(const tLista *lista, void *dataDest){

    ///tendria que usar el cod directamente porque es primitiva pero me da paja
    if(ListaVacia(lista)){
        return 1; ///La lista esta vacia no hay primero
    }
    else{
        memcpy(dataDest, (*lista)->data, (*lista)->tamData);
    }
    return 0;
}

int SacarUltimoLista(const tLista *lista, void *dataDest){

    tNodo *lecturaActual;
    tNodo *lecturaAnterior;

    ///tendria que usar el cod directamente porque es primitiva pero me da paja
    if(ListaVacia(lista)){
        return 1; ///La lista esta vacia no hay ultimo
    }
    else{
        lecturaActual = *lista;
        while(lecturaActual->sig != NULL){
            lecturaAnterior = lecturaActual;
            lecturaActual = lecturaActual->sig;
        }
        memcpy(dataDest, lecturaActual->data, lecturaActual->tamData);
        lecturaAnterior -> sig = NULL;
        free(lecturaActual->data);
        free(lecturaActual);
    }
    return 0;
}


int SacarPrimeroLista(tLista *lista, void *dataDest){
    tNodo *nuevoPrimero;
    tNodo *auxLista = *lista;
    ///tendria que usar el cod directamente porque es primitiva pero me da paja
    if(ListaVacia(lista)){
        return 1; ///La lista esta vacia no hay primero
    }
    else{
        memcpy(dataDest, (*lista)->data, (*lista)->tamData);
        nuevoPrimero = (*lista)->sig;
        free((*lista)->data);
        free(auxLista);
        *lista = nuevoPrimero;
    }
    return 0;
}

void RecorrerLista(tLista *lista, void (*accion)(void *), size_t dataSize){

    void *aux;
    while(*lista){
        aux = malloc(dataSize);
        memcpy(aux, (*lista)->data, dataSize);
        accion(aux);
        free(aux);
        lista = &(*lista)->sig;
    }
}


