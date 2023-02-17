#define _GNU_SOURCE

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int agregar_usuarios(char* nombre_archivo, hash_t* hash_original, hash_t* hash_usuarios) {
    FILE* arch_usuarios = fopen(nombre_archivo, "r");
    if (!arch_usuarios) {
        printf("Error: archivo fuente inaccesible\n");
        hash_destruir(hash_original);
        return -1;
    }

    size_t n = 32;
    char* nombre = (char*)malloc(n * sizeof(char));
    if (nombre == NULL) {
        printf("Error: malloc fallo\n");
        fclose(arch_usuarios);
        hash_destruir(hash_original);
        return -1;
    }
    int i = 0;
    size_t cantidad;
    while ((getline(&nombre, &n, arch_usuarios) != EOF)) {
        cantidad = strlen(nombre);
        char* copia_nombre;

        if (nombre[cantidad - 1] == '\n') {
            hash_guardar(hash_original, (const char*)nombre, nombre);
            copia_nombre = strdupp(nombre);
            hash_guardar(hash_usuarios, (const char*)nombre, copia_nombre);
            i += 1;
        } else {
            hash_guardar(hash_original, (const char*)(strcat(nombre, "\n")), nombre);
            copia_nombre = strdupp(strcat(nombre, "\n"));
            hash_guardar(hash_usuarios, (const char*)(strcat(nombre, "\n")), copia_nombre);
            i += 1;
        }
    }
    free(nombre);
    fclose(arch_usuarios);

    return i;
}

const char** agrega_arreglo(const char* arr[], char* nombre_archivo, hash_t* hash_original) {
    FILE* arch_usuarios = fopen(nombre_archivo, "r");
    if (!arch_usuarios) {
        printf("Error: archivo fuente inaccesible\n");
        hash_destruir(hash_original);
        return NULL;
    }
    size_t n = 32;
    char* nombre = (char*)malloc(n * sizeof(char));
    if (nombre == NULL) {
        printf("Error: malloc fallo\n");
        fclose(arch_usuarios);
        hash_destruir(hash_original);
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

void guardar_datos_usuarios(hash_t* hash_original, datos_u_t** datos, int n, const char* arr[]) {
    for (int j = 0; j < n; j++) {
        hash_guardar(hash_original, arr[j], datos[j]);
    }
}

int recibir_parametro(hash_t* hash_original, int id, hash_t* hash_posts, pila_t* pila_aux, hash_t* hash_usuarios, int cant_usuarios) {
    size_t n_2 = 32;
    char* chequeo = (char*)malloc(n_2 * sizeof(char));
    if (chequeo == NULL) {
        printf("Error: malloc fallo\n");
        hash_destruir(hash_original);
        return -1;
    }
    char* usuario_logueado = NULL;
    while (getline(&chequeo, &n_2, stdin) != EOF) {
        if (strcmp(chequeo, "login\n") == 0) {
            if (usuario_logueado != NULL) {
                printf("Error: Ya habia un usuario loggeado\n");
                continue;
            }
            usuario_logueado = funcion_login(hash_original, &chequeo, n_2, hash_usuarios);
            continue;
        } else if (strcmp(chequeo, "logout\n") == 0) {
            usuario_logueado = funcion_logout(chequeo, n_2, usuario_logueado);

            continue;
        } else if (strcmp(chequeo, "publicar\n") == 0) {
            if (funcion_publicar(hash_original, &chequeo, n_2, id, hash_posts, pila_aux, usuario_logueado, cant_usuarios) == -1) {
                continue;
            }
            printf("Post publicado\n");
            id += 1;
            continue;
        } else if (strcmp(chequeo, "ver_siguiente_feed\n") == 0) {
            if (usuario_logueado == NULL || funcion_siguiente(hash_obtener(hash_original, usuario_logueado), chequeo, pila_aux, usuario_logueado) == -1) {
                printf("Usuario no loggeado o no hay mas posts para ver\n");
            }
            continue;
        } else if (strcmp(chequeo, "likear_post\n") == 0) {
            if (funcion_likear(hash_posts, chequeo, n_2, usuario_logueado) == -1) {
                printf("Error: Usuario no loggeado o Post inexistente\n");
            }
            continue;
        } else if (strcmp(chequeo, "mostrar_likes\n") == 0) {
            if (mostrar_likes(hash_posts, chequeo, n_2) == -1) {
                printf("Error: Post inexistente o sin likes\n");
            }
            continue;
        }
    }
    free(chequeo);
    return 0;
}

char* funcion_login(hash_t* hash_original, char** chequeo, size_t n_2, hash_t* hash_usuarios) {
    ssize_t get = getline(chequeo, &n_2, stdin);
    if (get == -1) {
        return NULL;
    }
    if (!hash_pertenece(hash_original, *chequeo)) {
        printf("Error: usuario no existente\n");
        return NULL;
    }
    char* nombre = hash_obtener(hash_usuarios, *chequeo);
    printf("Hola %s", nombre);

    return nombre;
}

char* funcion_logout(char* chequeo, size_t n_2, char* usuario_logueado) {
    if (usuario_logueado == NULL) {
        printf("Error: no habia usuario loggeado\n");
        return NULL;
    }
    printf("Adios\n");
    return NULL;
}

int funcion_publicar(hash_t* hash_original, char** chequeo, size_t n_2, int id, hash_t* hash_posts, pila_t* pila_aux, char* usuario_logueado, int cant_usuarios) {
    if (usuario_logueado == NULL) {
        printf("Error: no habia usuario loggeado\n");
        return -1;
    }
    ssize_t get = getline(chequeo, &n_2, stdin);
    if (get == -1) {
        return -1;
    }
    char* contenido = strdupp(*chequeo);
    hash_iter_t* iter = hash_iter_crear(hash_original);
    posts_t* post = crear_post(usuario_logueado, contenido, id, hash_original, pila_aux, cant_usuarios);
    char id_v[10];
    sprintf(id_v, "%d\n", id);
    hash_guardar(hash_posts, id_v, post);
    while (!hash_iter_al_final(iter)) {
        const char* clave = hash_iter_ver_actual(iter);
        if (!clave) {
            break;
        }
        pila_apilar(pila_aux, (char*)clave);
        datos_u_t* actual = hash_obtener(hash_original, clave);
        if (strcmp(clave, usuario_logueado) == 0) {
            hash_iter_avanzar(iter);
            continue;
        }
        heap_encolar(actual->feed, post);
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    return 0;
}

int funcion_siguiente(datos_u_t* datos, char* chequeo, pila_t* pila_aux, char* usuario_logueado) {
    if (!datos) {
        return -1;
    }
    if (heap_esta_vacio(datos->feed)) {
        return -1;
    }
    pila_apilar(pila_aux, usuario_logueado);
    posts_t* post = heap_desencolar(datos->feed);
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

int funcion_likear(hash_t* hash_posts, char* chequeo, size_t n_2, char* usuario_logueado) {
    if (usuario_logueado == NULL) {
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

    if (!abb_pertenece(post->likes, usuario_logueado)) {
        abb_guardar(post->likes, usuario_logueado, usuario_logueado);
    }

    printf("Post likeado\n");
    return 0;
}

int mostrar_likes(hash_t* hash_posts, char* chequeo, size_t n_2) {
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

bool func_visitar(const char* clave, void* dato, void* extra) {
    printf("\t%s", (char*)dato);
    return true;
}
