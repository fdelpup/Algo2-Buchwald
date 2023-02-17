#include "datos_u.h"

datos_u_t* datos_u_crear(int post_cmp(const void* a, const void* b), int pos) {
    datos_u_t* datos_u = malloc(sizeof(datos_u_t));
    if (!datos_u) {
        return NULL;
    }
    datos_u->pos = pos;
    datos_u->feed = heap_crear(post_cmp);
    if (datos_u->feed == NULL) {
        free(datos_u);
        return NULL;
    }
    return datos_u;
}

void datos_u_destruir(datos_u_t* datos) {
    heap_destruir(datos->feed, NULL);
    free(datos);
}

datos_u_t** crear_lista_datos(int n_usuarios, int post_cmp(const void* dato_1, const void* dato_2)) {
    datos_u_t** tabla = malloc(sizeof(datos_u_t*) * (size_t)n_usuarios);
    if (!tabla) {
        return NULL;
    }
    for (int i = 0; i < n_usuarios; i++) {
        tabla[i] = datos_u_crear(post_cmp, i);
        if (!tabla[i]) {
            for (int j = 0; j < i; j++) {
                datos_u_destruir(tabla[j]);
            }
            free(tabla);
            return NULL;
        }
    }
    return tabla;
}