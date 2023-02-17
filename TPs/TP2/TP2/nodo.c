#include "nodo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

nodo_t* crear_nodo(void* dato) {
    nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
    if (nuevo_nodo == NULL) {
        return NULL;
    }
    // nuevo_nodo->dato = malloc(sizeof(void*));
    // if(nuevo_nodo->dato == NULL){
    //     return NULL;
    // }
    nuevo_nodo->dato = dato;
    nuevo_nodo->prox_nodo = NULL;

    return nuevo_nodo;
}