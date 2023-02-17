#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc == 1 || argc >= 3) {
        fprintf(stdout, "Error: Cantidad erronea de parametros\n");
        return -1;
    }

    hash_t* hash_usuarios = hash_crear(free);
    pila_t* pila_aux = pila_crear();
    hash_t* hash_original = hash_crear(NULL);

    int n_usuarios = 0;
    n_usuarios = agregar_usuarios(argv[1], hash_original, hash_usuarios);
    if (n_usuarios == -1) {
        return -1;
    }

    const char** arr = malloc(sizeof(char*) * (size_t)n_usuarios);
    arr = agrega_arreglo(arr, argv[1], hash_original);

    datos_u_t** tabla = crear_lista_datos(n_usuarios, post_cmp);
    guardar_datos_usuarios(hash_original, tabla, n_usuarios, arr);
    hash_t* hash_posts = hash_crear(destruir_post);

    int id = 0;
    if (recibir_parametro(hash_original, id, hash_posts, pila_aux, hash_usuarios, n_usuarios) == -1) {
        return -1;
    }

    hash_iter_t* iter = hash_iter_crear(hash_original);
    while (!hash_iter_al_final(iter)) {
        datos_u_t* datos = hash_obtener(hash_original, hash_iter_ver_actual(iter));
        datos_u_destruir(datos);
        hash_iter_avanzar(iter);
    }

    for (int i = 0; i < n_usuarios; i++) {
        free((char*)arr[i]);
    }

    free(arr);
    free(tabla);
    hash_destruir(hash_usuarios);
    pila_destruir(pila_aux);
    hash_iter_destruir(iter);
    hash_destruir(hash_original);
    hash_destruir(hash_posts);
    return 0;
}