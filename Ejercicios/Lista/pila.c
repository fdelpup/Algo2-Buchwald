#include "pila.h"

#include <stdlib.h>

#define CAPACIDAD_INICIAL_PILA 2

/* Definición del struct pila proporcionado por la cátedra. */

struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};


// Funciones Auxiliares

bool redimensionar_pila(pila_t *pila, size_t nueva_capacidad){
    
    void **datos_redimensionados = realloc(pila->datos, nueva_capacidad * sizeof(void*));
    if(datos_redimensionados == NULL){
        return false;
    }
    pila->datos = datos_redimensionados;

    return true;
}


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/


pila_t *pila_crear(void){

    pila_t *nueva_pila = malloc(sizeof(pila_t)); 
    if(nueva_pila == NULL){
        return NULL;
    }
    nueva_pila->capacidad = CAPACIDAD_INICIAL_PILA;

    void **datos = malloc(nueva_pila->capacidad * sizeof(void*));
    if(datos == NULL){
        free(nueva_pila);
        return NULL;
    }
    nueva_pila->datos = datos;
    nueva_pila->cantidad = 0;

    return nueva_pila;
}


void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}


bool pila_esta_vacia(const pila_t *pila){
    return (pila->cantidad == 0);
}


bool pila_apilar(pila_t *pila, void *valor){

    if(pila->cantidad == pila->capacidad){
        pila->capacidad = pila->capacidad * 2;
        bool res = redimensionar_pila(pila, pila->capacidad);
        if(!res){
            return false;
        }
    }

    pila->datos[pila->cantidad] = valor; 
    pila->cantidad += 1;
    
    return true;

}


void *pila_ver_tope(const pila_t *pila){

    if(pila_esta_vacia(pila)){
        return NULL;
    }
    return pila->datos[pila->cantidad - 1]; 
}


void *pila_desapilar(pila_t *pila){ 

    if(pila_esta_vacia(pila)){
        return NULL;
    }else{
        if((pila->cantidad * 4) <= pila->capacidad){
            pila->capacidad = pila->capacidad / 2;
            bool res = redimensionar_pila(pila, pila->capacidad);
            if(!res){
                return false;
            }
        }
        void* valor_anterior = pila->datos[pila->cantidad - 1];
        (pila->cantidad) -= 1;
        return valor_anterior; 
    }
    
}


