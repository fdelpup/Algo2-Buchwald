#ifndef EXTRA_H
#define EXTRA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abb.h"
#include "hash.h"
#include "heap.h"
#include "lista.h"
#include "pila.h"

// struct estructuras auxiliares;

struct datos_u {
    heap_t* heap;
    hash_t* hash;
};
typedef struct datos_u datos_u_t;

struct posts {
    char* nombre;
    char* dato;
    int id;
    abb_t* likes;
    hash_t* hash;
    pila_t* pila;
    pila_t* pila_aux;
};
typedef struct posts posts_t;

// struct publicacion {
//     int* dato_cmp;
//     posts_t* post;
// };
// typedef struct publicacion publicacion_t;

// comportamiento estructuras auxiliares

datos_u_t* datos_u_crear(int compare(const void* a, const void* b));

posts_t* crear_post(char* nombre, char* contenido, int id, hash_t* hash, pila_t* pila, pila_t* pila_aux);

// publicacion_t* crear_publicacion(posts_t* post, int* afinidad);

void destruir_post(void* post);

void destruir_publicacion(void* publicacion);

void datos_u_destruir(datos_u_t* datos);

datos_u_t** crear_lista_datos(int n_usuarios);

// funciones auxiliares

int strcmpare(const void* dato_1, const void* dato_2);

int int_cmp(const void* a, const void* b);

int int_cmp_aux(int a, int b);

char* strdupp(const char* clave);

int agregar_usuarios(char* nombre_archivo, hash_t* hash, pila_t* pila, hash_t* hash_usuarios);
int funcion_login(hash_t* hash, pila_t* pila, char** chequeo, size_t n_2, hash_t* hash_usuarios);
int funcion_logout(hash_t* hash, pila_t* pila, char* chequeo, size_t n_2);
const char** agrega_arreglo(const char* arr[], char* nombre_archivo, hash_t* hash);
void guardar_datos_usuarios(hash_t* hash, datos_u_t** datos, int n, const char* arr[], int* afinidad[]);
int recibir_parametro(hash_t* hash, pila_t* pila, int id, hash_t* hash_posts, pila_t* pila_aux, hash_t* hash_usuarios);

#endif  // EXTRA_H