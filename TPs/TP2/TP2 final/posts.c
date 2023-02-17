#include "posts.h"

#include "string.h"

posts_t* crear_post(char* nombre, char* contenido, int id, hash_t* hash_original, pila_t* pila_aux, int cant_usuarios) {
    posts_t* post = malloc(sizeof(posts_t));
    if (!post) {
        return NULL;
    }
    post->likes = abb_crear(strcmp, NULL);
    post->nombre = nombre;
    post->dato = contenido;
    post->id = id;
    post->cant_usuarios = cant_usuarios;
    post->hash_original = hash_original;
    post->pila_aux = pila_aux;
    return post;
}

void destruir_post(void* post) {
    abb_destruir(((posts_t*)post)->likes);
    free(((posts_t*)post)->dato);
    free(post);
}
