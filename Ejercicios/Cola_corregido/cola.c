#include "cola.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo nodo_t;

struct nodo{
    void *dato;     // Apunta al dato almacenado
    nodo_t *prox;   // Apunta al prox nodo
};

struct cola{
    nodo_t *primero;
    nodo_t *ultimo;
};

nodo_t *crear_nodo(void *dato) {
    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (nuevo_nodo == NULL) {
        return NULL;
    }
    nuevo_nodo->dato = dato;
    nuevo_nodo->prox = NULL;

    return nuevo_nodo;
}

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/


cola_t *cola_crear(void) {
    cola_t *nueva_cola = malloc(sizeof(cola_t));
    if (nueva_cola == NULL) {
        return NULL;
    }
    nueva_cola->primero = NULL;
    nueva_cola->ultimo = NULL;

    return nueva_cola;
}


void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {
    while (!cola_esta_vacia(cola)) {
        void *dato = cola_desencolar(cola);
        if (destruir_dato)
            destruir_dato(dato);
    }
    free(cola);
}


bool cola_esta_vacia(const cola_t *cola) { 
    if (cola->primero == NULL) {
        return true;
    }
    return false;
}


bool cola_encolar(cola_t *cola, void *valor) {
    void *nuevo_nodo = crear_nodo(valor);
    if (nuevo_nodo == NULL) {
        return false;
    }
    if (cola_esta_vacia(cola)) {
        cola->primero = nuevo_nodo;
        cola->ultimo = nuevo_nodo;
    } else {
        cola->ultimo->prox = nuevo_nodo; 
        cola->ultimo = nuevo_nodo;
    }
    return true;
}


void *cola_ver_primero(const cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }
    return cola->primero->dato;
}


void *cola_desencolar(cola_t *cola) {

    if (cola_esta_vacia(cola)) {
        return NULL;
    }

    void *dato = cola->primero->dato;
    nodo_t *nodo = cola->primero->prox;

    free(cola->primero);    

    if (nodo == NULL) {
        cola->primero = NULL;
        cola->ultimo = NULL;
    } else {
        cola->primero = nodo;
    }

    return dato;
}
