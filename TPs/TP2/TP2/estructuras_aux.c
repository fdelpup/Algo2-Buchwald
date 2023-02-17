#include "extra.h"

datos_u_t* datos_u_crear(int compare(const void* a, const void* b)) {
    datos_u_t* datos_u = malloc(sizeof(datos_u_t));
    if (!datos_u) {
        return NULL;
    }
    datos_u->hash = hash_crear(NULL);
    if (datos_u->hash == NULL) {
        free(datos_u);
        return NULL;
    }
    datos_u->heap = heap_crear(compare);
    if (datos_u->heap == NULL) {
        free(datos_u->hash);
        free(datos_u);
        return NULL;
    }
    return datos_u;
}

posts_t* crear_post(char* nombre, char* contenido, int id, hash_t* hash, pila_t* pila, pila_t* pila_aux) {
    posts_t* post = malloc(sizeof(posts_t));
    if (!post) {
        return NULL;
    }
    post->likes = abb_crear(strcmp, NULL);
    post->nombre = nombre;
    post->dato = contenido;
    post->id = id;
    post->hash = hash;
    post->pila_aux = pila_aux;
    return post;
}

// publicacion_t* crear_publicacion(posts_t* post, int* afinidad) {
//     publicacion_t* publicacion = malloc(sizeof(publicacion_t));
//     publicacion->dato_cmp = afinidad;
//     publicacion->post = post;
//     return publicacion;
// }

void destruir_post(void* post) {
    abb_destruir(((posts_t*)post)->likes);
    free(((posts_t*)post)->dato);
    free(post);
}

// void destruir_publicacion(void* publicacion) {
//     free(publicacion);
// }

void datos_u_destruir(datos_u_t* datos) {
    hash_destruir(datos->hash);
    heap_destruir(datos->heap, NULL);
    free(datos);
}

datos_u_t** crear_lista_datos(int n_usuarios) {
    datos_u_t** tabla = malloc(sizeof(datos_u_t*) * (size_t)n_usuarios);
    if (!tabla) {
        return NULL;
    }
    for (int i = 0; i < n_usuarios; i++) {
        tabla[i] = datos_u_crear(strcmpare);
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