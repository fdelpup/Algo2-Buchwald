#define _GNU_SOURCE

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "extra.h"

int funcion_login(hash_t* hash, pila_t* pila, char** chequeo, size_t n_2) {
    ssize_t get = getline(chequeo, &n_2, stdin);
    if (get == -1) {
        return -1;
    }
    if (!hash_pertenece(hash, *chequeo)) {
        printf("Error: usuario no existente\n");
        return -1;
    }
    char* nombre = strdupp(*chequeo);
    pila_apilar(pila, nombre);
    // printf("%s", *chequeo);
    printf("Hola %s", *chequeo);

    return 0;
}

int funcion_logout(hash_t* hash, pila_t* pila, char* chequeo, size_t n_2) {
    if ((char*)pila_ver_tope(pila) == NULL) {
        printf("Error: no habia usuario loggeado\n");
        return -1;
    }
    pila_apilar(pila, NULL);
    printf("Adios\n");
    return 0;
}

void llenar_afinidad(const char* arr[], hash_t* hash_datos, int cant_usuarios, int inicio, int* afinidad[]) {
    int afinidad_num = cant_usuarios - 1;

    for (int i = inicio - 1; i >= 0; i--) {
        afinidad_num -= 1;
        hash_guardar(hash_datos, arr[i], afinidad[afinidad_num]);
    }
    // printf("%ls\n", (int*)(afinidad[afinidad_num]));
    afinidad_num = cant_usuarios - 1;
    for (int i = inicio + 1; i < cant_usuarios; i++) {
        afinidad_num -= 1;
        hash_guardar(hash_datos, arr[i], afinidad[afinidad_num]);
    }
}

void guardar_datos_usuarios(hash_t* hash, datos_u_t** datos, int n, const char* arr[], int* afinidad[]) {
    for (int j = 0; j < n; j++) {
        llenar_afinidad(arr, datos[j]->hash, n, j, afinidad);
        hash_guardar(hash, arr[j], datos[j]);
    }
}

int funcion_publicar(hash_t* hash, pila_t* pila, char** chequeo, size_t n_2, int id, hash_t* hash_posts, pila_t* pila_aux) {
    if (pila_ver_tope(pila) == NULL) {
        printf("Error: no habia usuario loggeado\n");
        return -1;
    }
    ssize_t get = getline(chequeo, &n_2, stdin);
    if (get == -1) {
        return -1;
    }
    char* contenido = strdupp(*chequeo);
    hash_iter_t* iter = hash_iter_crear(hash);
    posts_t* post = crear_post(pila_ver_tope(pila), contenido, id, hash, pila, pila_aux);
    char id_v[10];
    sprintf(id_v, "%d\n", id);
    hash_guardar(hash_posts, id_v, post);
    while (!hash_iter_al_final(iter)) {
        const char* clave = hash_iter_ver_actual(iter);
        if (!clave) {
            break;
        }
        pila_apilar(pila_aux, (char*)clave);
        datos_u_t* actual = hash_obtener(hash, clave);
        if (strcmp(clave, pila_ver_tope(pila)) == 0) {
            hash_iter_avanzar(iter);
            continue;
        }
        // if (!actual) {
        //     break;
        // }
        // publicacion_t* publicacion = crear_publicacion(post, hash_obtener(actual->hash, pila_ver_tope(pila)));
        heap_encolar(actual->heap, post);

        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    return 0;
}
int funcion_siguiente(datos_u_t* datos, char* chequeo, pila_t* pila, pila_t* pila_aux) {
    if (!datos) {
        return -1;
    }
    if (heap_esta_vacio(datos->heap)) {
        return -1;
    }
    pila_apilar(pila_aux, pila_ver_tope(pila));
    posts_t* post = heap_desencolar(datos->heap);
    if (!post) {
        return -1;
    }

    printf("Post ID %i\n", post->id);
    char* nombre = strtok(post->nombre, "\n");
    printf("%s dijo: %s", nombre, post->dato);
    printf("Likes: %li\n", abb_cantidad(post->likes));
    post->nombre = (strcat(nombre, "\n"));

    return 0;
}

int funcion_likear(hash_t* hash_posts, char* chequeo, pila_t* pila, size_t n_2) {
    if (pila_ver_tope(pila) == NULL) {
        return -1;
    }

    ssize_t get = getline(&chequeo, &n_2, stdin);
    if (get == -1) {
        return -1;
    }
    if (!chequeo) {
        return -1;
    }
    if (!hash_pertenece(hash_posts, chequeo)) {
        return -1;
    }
    posts_t* post = hash_obtener(hash_posts, chequeo);

    if (!abb_pertenece(post->likes, pila_ver_tope(pila))) {
        abb_guardar(post->likes, pila_ver_tope(pila), pila_ver_tope(pila));
    }

    printf("Post likeado\n");
    return 0;
}

bool func_visitar(const char* clave, void* dato, void* extra) {
    printf("\t%s", (char*)dato);
    return true;
}

int mostrar_likes(hash_t* hash_posts, char* chequeo, pila_t* pila, size_t n_2) {
    ssize_t get = getline(&chequeo, &n_2, stdin);
    if (get == -1) {
        return -1;
    }
    if (!chequeo) {
        return -1;
    }
    if (!hash_pertenece(hash_posts, chequeo)) {
        return -1;
    }
    posts_t* post = hash_obtener(hash_posts, chequeo);
    if (abb_cantidad(post->likes) == 0) {
        return -1;
    }
    printf("El post tiene %li likes:\n", abb_cantidad(post->likes));
    abb_in_order(post->likes, func_visitar, NULL);
    return 0;
}

int recibir_parametro(hash_t* hash, pila_t* pila, int id, hash_t* hash_posts, pila_t* pila_aux) {
    size_t n_2 = 32;
    char* chequeo = (char*)malloc(n_2 * sizeof(char));
    if (chequeo == NULL) {
        printf("Error: malloc fallo\n");
        hash_destruir(hash);
        return -1;
    }
    while (getline(&chequeo, &n_2, stdin) != EOF) {
        if (strcmp(chequeo, "login\n") == 0) {
            if (pila_ver_tope(pila) != NULL) {
                printf("Error: Ya habia un usuario loggeado\n");
                continue;
            }
            funcion_login(hash, pila, &chequeo, n_2);
            continue;
        } else if (strcmp(chequeo, "logout\n") == 0) {
            funcion_logout(hash, pila, chequeo, n_2);
            continue;
        } else if (strcmp(chequeo, "publicar\n") == 0) {
            if (funcion_publicar(hash, pila, &chequeo, n_2, id, hash_posts, pila_aux) == -1) {
                continue;
            }
            printf("Post publicado\n");
            id += 1;
            continue;
        } else if (strcmp(chequeo, "ver_siguiente_feed\n") == 0) {
            if (!pila_ver_tope(pila) || funcion_siguiente(hash_obtener(hash, pila_ver_tope(pila)), chequeo, pila, pila_aux) == -1) {
                printf("Usuario no loggeado o no hay mas posts para ver\n");
            }
            continue;
        } else if (strcmp(chequeo, "likear_post\n") == 0) {
            if (funcion_likear(hash_posts, chequeo, pila, n_2) == -1) {
                printf("Error: Usuario no loggeado o Post inexistente\n");
            }
            continue;
        } else if (strcmp(chequeo, "mostrar_likes\n") == 0) {
            if (mostrar_likes(hash_posts, chequeo, pila, n_2) == -1) {
                printf("Error: Post inexistente o sin likes\n");
            }
            continue;
        }
    }
    free(chequeo);
    return 0;
}

const char** agrega_arreglo(const char* arr[], char* nombre_archivo, hash_t* hash) {
    FILE* arch_usuarios = fopen(nombre_archivo, "r");
    if (!arch_usuarios) {
        printf("Error: archivo fuente inaccesible\n");
        hash_destruir(hash);
        return NULL;
    }
    size_t n = 32;
    char* nombre = (char*)malloc(n * sizeof(char));
    if (nombre == NULL) {
        printf("Error: malloc fallo\n");
        fclose(arch_usuarios);
        hash_destruir(hash);
        return NULL;
    }
    int i = 0;
    size_t cantidad;
    while ((getline(&nombre, &n, arch_usuarios) != EOF)) {
        cantidad = strlen(nombre);

        if (nombre[cantidad - 1] == '\n') {
            arr[i] = strdupp(nombre);
            i++;
        } else {
            arr[i] = strdupp(strcat(nombre, "\n"));
            i++;
        }
    }
    fclose(arch_usuarios);
    free(nombre);
    return arr;
}

int agregar_usuarios(char* nombre_archivo, hash_t* hash, pila_t* pila) {
    FILE* arch_usuarios = fopen(nombre_archivo, "r");
    if (!arch_usuarios) {
        printf("Error: archivo fuente inaccesible\n");
        hash_destruir(hash);
        return -1;
    }

    size_t n = 32;
    char* nombre = (char*)malloc(n * sizeof(char));
    if (nombre == NULL) {
        printf("Error: malloc fallo\n");
        fclose(arch_usuarios);
        hash_destruir(hash);
        return -1;
    }
    int i = 0;
    size_t cantidad;
    while ((getline(&nombre, &n, arch_usuarios) != EOF)) {
        cantidad = strlen(nombre);
        if (nombre[cantidad - 1] == '\n') {
            hash_guardar(hash, (const char*)nombre, nombre);
            i += 1;
        } else {
            hash_guardar(hash, (const char*)(strcat(nombre, "\n")), nombre);
            i += 1;
        }
    }
    free(nombre);
    fclose(arch_usuarios);

    return i;
}
