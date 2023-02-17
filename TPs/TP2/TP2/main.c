#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "extra.h"

int main(int argc, char* argv[]) {
    if (argc == 1 || argc >= 3) {
        fprintf(stdout, "Error: Cantidad erronea de parametros\n");
        return -1;
    }
    pila_t* pila_aux = pila_crear();
    hash_t* hash = hash_crear(NULL);
    pila_t* pila = pila_crear();
    hash_t* hash_usuarios = hash_crear(NULL);
    int n_usuarios = 0;
    n_usuarios = agregar_usuarios(argv[1], hash, pila, hash_usuarios);
    if (n_usuarios == -1) {
        return -1;
    }
    const char** arr = malloc(sizeof(char*) * (size_t)n_usuarios);
    arr = agrega_arreglo(arr, argv[1], hash);

    int* afinidad[n_usuarios];
    for (int i = 0; i < n_usuarios; i++) {
        afinidad[i] = malloc(sizeof(int*));
        *afinidad[i] = i;
    }

    datos_u_t** tabla = crear_lista_datos(n_usuarios);
    guardar_datos_usuarios(hash, tabla, n_usuarios, arr, afinidad);
    hash_t* hash_posts = hash_crear(destruir_post);  // pasar destrir post
    int id = 0;

    if (recibir_parametro(hash, pila, id, hash_posts, pila_aux, hash_usuarios) == -1) {
        return -1;
    }

    // ACA destruir
    while (!pila_esta_vacia(pila)) {
        void* dato = pila_desapilar(pila);
        if (dato) {
            free(dato);
        }
    }
    pila_destruir(pila);
    hash_iter_t* iter = hash_iter_crear(hash);

    while (!hash_iter_al_final(iter)) {
        datos_u_t* datos = hash_obtener(hash, hash_iter_ver_actual(iter));
        datos_u_destruir(datos);
        hash_iter_avanzar(iter);
    }

    for (int i = 0; i < n_usuarios; i++) {
        free((char*)arr[i]);
        free(afinidad[i]);
    }
    free(arr);
    free(tabla);
    pila_destruir(pila_aux);
    hash_iter_destruir(iter);
    hash_destruir(hash);
    hash_destruir(hash_posts);
    return 0;
}