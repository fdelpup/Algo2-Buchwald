#include "pila.h"

#include <stdlib.h>

#define CAPACIDAD_INICIAL_PILA 2

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};


// Funciones Auxiliares

bool redimensionar_pila(pila_t *pila){
    
    if(pila->cantidad == pila->capacidad){ 
        pila->capacidad = pila->capacidad * 2;
        void **datos_multiplicados = realloc(pila->datos, pila->capacidad * sizeof(void*));
        if(datos_multiplicados == NULL){
            return false;
        }
        pila->datos = datos_multiplicados;
    }

    if((pila->cantidad * 4) <= pila->capacidad ){ 
        pila->capacidad = pila->capacidad / 2;
        void **datos_divididos = realloc(pila->datos, pila->capacidad * sizeof(void*));
        if(datos_divididos == NULL){
            return false;
        }
        pila->datos = datos_divididos;
    }

    return true;
}


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// Crea una pila.
// Post: devuelve una nueva pila vacía.
pila_t *pila_crear(void){

    pila_t *nueva_pila = malloc(sizeof(pila_t)); 
    if(nueva_pila == NULL){
        return NULL;
    }
    nueva_pila->capacidad = CAPACIDAD_INICIAL_PILA;

    void **datos = malloc(nueva_pila->capacidad * sizeof(void*));
    if(datos == NULL){
        return NULL;
    }
    nueva_pila->datos = datos;
    nueva_pila->cantidad = 0;

    return nueva_pila;
}

// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

// Devuelve verdadero si la pila no tiene elementos apilados, false en caso contrario.
// Pre: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila){
    return (pila->cantidad == 0);
}

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, void *valor){

    if(!redimensionar_pila(pila)){
        return false;
    }

    pila->datos[pila->cantidad] = valor; 
    pila->cantidad += 1;
    
    return true;

}

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve NULL.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, NULL en caso contrario.

void *pila_ver_tope(const pila_t *pila){

    if(pila_esta_vacia(pila)){
        return NULL;
    }
    return pila->datos[pila->cantidad - 1]; 
}

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve
// NULL.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior
// y la pila contiene un elemento menos.

void *pila_desapilar(pila_t *pila){ 

    if(pila_esta_vacia(pila)){
        return NULL;
    }else{
        if(!redimensionar_pila(pila)){
            return NULL;
        }
        void* valor_anterior = pila->datos[pila->cantidad - 1];
        (pila->cantidad) -= 1;
        return valor_anterior; 
    }
    
}


