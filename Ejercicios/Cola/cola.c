#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

nodo_t *crear_nodo(void* dato){
    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if(nuevo_nodo == NULL){
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



/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea una cola.
// Post: devuelve una nueva cola vacía.  //BIEN
cola_t *cola_crear(void){
    cola_t *nueva_cola = malloc(sizeof(cola_t));
    if(nueva_cola == NULL){
        return NULL;
    }
    nueva_cola->primero = NULL;
    nueva_cola->ultimo = NULL;

    return nueva_cola;
}

// Destruye la cola. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la cola llama a destruir_dato.
// Pre: la cola fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la cola.
// void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)); // FALTA HACERLA


void cola_destruir(cola_t *cola){
    
    while(!cola_esta_vacia(cola)){
        cola_desencolar(cola);
    }
    free(cola);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




// Devuelve verdadero si la cola no tiene elementos encolados, false en caso contrario.
// Pre: la cola fue creada.
bool cola_esta_vacia(const cola_t *cola){ //BIEN
    if(cola->primero == NULL){
        return true;
    }else{
        return false;
    }
}

// Agrega un nuevo elemento a la cola. Devuelve falso en caso de error.
// Pre: la cola fue creada.
// Post: se agregó un nuevo elemento a la cola, valor se encuentra al final
// de la cola.
bool cola_encolar(cola_t *cola, void *valor){
    void* creacion_nodo = crear_nodo(valor);
    if(creacion_nodo == NULL){
        return false;
    }
    if(cola_esta_vacia(cola)){
        cola->primero = creacion_nodo;
        cola->ultimo = creacion_nodo;
    }else{
        cola->ultimo->prox_nodo = creacion_nodo; //CHEQUEAR ESTO!
        cola->ultimo = creacion_nodo;
    }
    return true;

}

// Obtiene el valor del primer elemento de la cola. Si la cola tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el primer elemento de la cola, cuando no está vacía.
void *cola_ver_primero(const cola_t *cola){
    if(!cola_esta_vacia(cola)){
        return cola->primero->dato;
    }else{
        return NULL;
    }
}

// Saca el primer elemento de la cola. Si la cola tiene elementos, se quita el
// primero de la cola, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el valor del primer elemento anterior, la cola
// contiene un elemento menos, si la cola no estaba vacía.

void *cola_desencolar(cola_t *cola){

    if(!cola_esta_vacia(cola)){

        void* datos = cola->primero->dato;  
        nodo_t *nodo = cola->primero->prox_nodo;

        if(nodo == NULL){
            free(cola->primero);
            cola->primero = NULL;
            cola->ultimo = NULL;
            
        }else{
            free(cola->primero);
            cola->primero = nodo;
        }

        return datos;

    }else{
        return NULL;
    }
}

