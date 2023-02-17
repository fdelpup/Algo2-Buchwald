
#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La cola está planteada como una cola de punteros genéricos. */

struct lista;
typedef struct lista lista_t;

typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento en la posicion del primero de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista en la primera posicion, dato se encuentra al principio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento en la posicion del ultimo de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista en la ultima posicion, dato se encuentra al principio
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Elimina el primer elemento de la lista y devuelve su dato. Devuelve NULL si la lista esta vacia.
// Pre: la lista fue creada.
// Post: se elimino el primer elemento de la lista, devuelve su dato.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t *lista);

// Obtiene el largo de la lista.
// Pre: La lista fue creada
// Post: se devolvio un size_t con el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

// Visita cada elemento de la lista con la funcion pasada por parametro y aplica dicha funcion a cada elemento.
// Pre: Lista este creada y se defina una funcion visitar
// Post: Visita cada elemento de la lista con la funcion pasada por parametro y aplica dicha funcion a cada elemento. Si visitar devuelve FALSE, corta la iteracion.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

// Crea un iterador de la lista.
// Post: devuelve un nuevo iterador de la lista vacía y en caso de alguna falla devuelve NULL.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza en el iterador, devuelve false si no hay mas elementos para avanzar.
// Pre: la lista_iter fue creada.
// Post: Devuelve true si hay elementos para avanzar.
bool lista_iter_avanzar(lista_iter_t *iter);

// Pre: la lista_iter fue creada.
// Post: Devuelve el dato, en caso de estar al final, devuelve NULL
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Pre: la lista_iter fue creada.
// Post: Devuelve true cuando no hay mas elementos en la lista_iter.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye lista_iter.
// Pre: lista_iter fue creada.
// Post: se elimino la lista_iter.
void lista_iter_destruir(lista_iter_t *iter);

// Agrega un nuevo elemento en la posicion en la que se encuentra. Devuelve falso en caso de error.
// Pre: lista_iter fue creada.
// Post: se agregó un nuevo elemento en esa posicion con su dato. Y el elemento anterior en esa posicion pasa a ser el siguiente.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Elimina el elemento de lista en la posicion que se encuentra y devuelve su dato. Devuelve NULL si no hay mas elementos.
// Pre: lista_iter fue creada.
// Post: se elimino el elemento de la lista en esa posicion, devuelve su dato.
void *lista_iter_borrar(lista_iter_t *iter);

void pruebas_lista_estudiante(void);

#endif  // LISTA_H