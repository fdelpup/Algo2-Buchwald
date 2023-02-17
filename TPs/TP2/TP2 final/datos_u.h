#ifndef DATOS_U_H
#define DATOS_U_H

#include <stdlib.h>

#include "hash.h"
#include "heap.h"

struct datos_u {
    heap_t* feed;
    int pos;
};
typedef struct datos_u datos_u_t;

datos_u_t* datos_u_crear(int compare(const void* a, const void* b), int pos);

void datos_u_destruir(datos_u_t* datos);

datos_u_t** crear_lista_datos(int n_usuarios, int strcmpare(const void* dato_1, const void* dato_2));
#endif  // DATOS_USUARIOS_H
