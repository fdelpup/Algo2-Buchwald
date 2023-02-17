#ifndef POSTS_H
#define POSTS_H

#include <stdlib.h>

#include "abb.h"
#include "hash.h"
#include "pila.h"

struct posts {
    char* nombre;
    char* dato;
    int id;
    int cant_usuarios;
    abb_t* likes;
    hash_t* hash_original;
    pila_t* pila_aux;
};
typedef struct posts posts_t;

posts_t* crear_post(char* nombre, char* contenido, int id, hash_t* hash_original, pila_t* pila_aux, int cant_usuarios);

void destruir_post(void* post);
#endif  // POSTS_H