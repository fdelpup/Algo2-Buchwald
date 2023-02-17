#include "hash.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "main.h"

#define TAM_TABLA_ORIGINAL 13
#define REDIMENSION 2
#define FACTOR_CARGA_AGRANDAR 2
#define FACTOR_CARGA_BORRAR 1 / 3

// https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29

#define MULTIPLICADOR (37)

unsigned long f_hash(const char *s) {
    unsigned long h;
    unsigned const char *us;
    /* cast s to unsigned const char * */
    /* this ensures that elements of s will be treated as having values >= 0 */
    us = (unsigned const char *)s;
    h = 0;
    while (*us != '\0') {
        h = (h * MULTIPLICADOR + *us);
        us++;
    }

    return h;
}

// Los structs deben llamarse "hash" y "hash_iter".

typedef struct campo campo_t;

struct campo {
    const char *clave;
    void *dato;
};

struct hash {
    lista_t **tabla;
    size_t capacidad;
    size_t cantidad;
    hash_destruir_dato_t destruir;
};

/* Iterador del hash */
struct hash_iter {
    size_t pos;
    lista_iter_t *lista_iter;
    const hash_t *hash;
};

lista_t **crear_tabla_hash(size_t tamanio) {
    lista_t **tabla = malloc(sizeof(lista_t *) * tamanio);
    if (!tabla) {
        return NULL;
    }
    for (int i = 0; i < tamanio; i++) {
        tabla[i] = lista_crear();
        if (!tabla[i]) {
            for (int j = 0; j < i; j++) {
                lista_destruir(tabla[j], NULL);
            }
            free(tabla);
            return NULL;
        }
    }
    return tabla;
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t *hash = malloc(sizeof(hash_t));
    if (hash == NULL) {
        return NULL;
    }
    hash->capacidad = TAM_TABLA_ORIGINAL;
    hash->cantidad = 0;
    hash->tabla = crear_tabla_hash(hash->capacidad);
    if (hash->tabla == NULL) {
        free(hash);
        return NULL;
    }

    hash->destruir = destruir_dato;

    return hash;
}

bool hash_redimension(hash_t *hash, size_t nuevo_tam) {
    lista_t **nueva_tabla = crear_tabla_hash(nuevo_tam);
    if (nueva_tabla == NULL) {
        return false;
    }
    for (int i = 0; i < hash->capacidad; i++) {
        while (!lista_esta_vacia(hash->tabla[i])) {
            campo_t *campo = lista_borrar_primero(hash->tabla[i]);
            unsigned long posicion = f_hash(campo->clave) % nuevo_tam;
            lista_insertar_ultimo(nueva_tabla[posicion], campo);
        }
        lista_destruir(hash->tabla[i], NULL);
    }

    free(hash->tabla);
    hash->tabla = nueva_tabla;
    hash->capacidad = nuevo_tam;
    return true;
}

lista_iter_t *iter_actual_igual_clave(const hash_t *hash, const char *clave) {
    size_t pos = f_hash(clave) % hash->capacidad;

    lista_iter_t *iter = lista_iter_crear(hash->tabla[pos]);
    while (!lista_iter_al_final(iter)) {
        campo_t *campo_actual = (campo_t *)lista_iter_ver_actual(iter);
        if (strcmp(campo_actual->clave, clave) == 0) {
            return iter;
        }
        lista_iter_avanzar(iter);
    }
    return iter;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    if ((hash->cantidad / hash->capacidad) >= FACTOR_CARGA_AGRANDAR) {
        if (!hash_redimension(hash, hash->capacidad * REDIMENSION)) {
            return false;
        }
    }
    lista_iter_t *iter = iter_actual_igual_clave(hash, clave);

    if (!lista_iter_al_final(iter)) {
        campo_t *campo_actual = (campo_t *)lista_iter_ver_actual(iter);
        if (hash->destruir != NULL) {
            (hash->destruir)(campo_actual->dato);
        }
        campo_actual->dato = dato;
        lista_iter_destruir(iter);
        return true;
    }

    campo_t *campo = malloc(sizeof(campo_t));
    if (campo == NULL) {
        return false;
    }

    const char *clave_1 = strdupp(clave);
    if (clave_1 == NULL) {
        free(campo);
        return false;
    }
    campo->clave = clave_1;
    campo->dato = dato;

    if (!lista_iter_insertar(iter, campo)) {
        return false;
    }
    lista_iter_destruir(iter);
    hash->cantidad += 1;
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave) {
    lista_iter_t *iter = iter_actual_igual_clave(hash, clave);

    if (((float)hash->cantidad / (float)hash->capacidad) <= FACTOR_CARGA_BORRAR && hash->capacidad / REDIMENSION >= TAM_TABLA_ORIGINAL) {
        if (!hash_redimension(hash, hash->capacidad / REDIMENSION)) {
            return false;
        }
    }

    if (lista_iter_al_final(iter)) {
        lista_iter_destruir(iter);
        return NULL;
    }
    campo_t *campo_actual = (campo_t *)lista_iter_ver_actual(iter);
    void *dato_borrado = campo_actual->dato;
    lista_iter_borrar(iter);
    lista_iter_destruir(iter);
    hash->cantidad -= 1;
    free((char *)(campo_actual->clave));
    free(campo_actual);
    return dato_borrado;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
    lista_iter_t *iter = iter_actual_igual_clave(hash, clave);

    if (lista_iter_al_final(iter)) {
        lista_iter_destruir(iter);
        return NULL;
    }

    campo_t *campo_actual = (campo_t *)lista_iter_ver_actual(iter);
    lista_iter_destruir(iter);
    return campo_actual->dato;
}

bool hash_pertenece(const hash_t *hash, const char *clave) {
    lista_iter_t *iter = iter_actual_igual_clave(hash, clave);
    if (lista_iter_al_final(iter)) {
        lista_iter_destruir(iter);
        return false;
    }
    lista_iter_destruir(iter);
    return true;
}

size_t hash_cantidad(const hash_t *hash) {
    return hash->cantidad;
}

void hash_destruir(hash_t *hash) {
    for (int i = 0; i < hash->capacidad; i++) {
        while (!lista_esta_vacia(hash->tabla[i])) {
            campo_t *campo = lista_borrar_primero(hash->tabla[i]);
            if (hash->destruir != NULL) {
                (hash->destruir)(campo->dato);
            }
            free((char *)(campo->clave));
            free(campo);
        }

        lista_destruir(hash->tabla[i], NULL);
    }
    free(hash->tabla);
    free(hash);
}

hash_iter_t *asignar_lista_iter(const hash_t *hash, hash_iter_t *iter, lista_iter_t *lista) {
    for (; iter->pos < hash->capacidad; iter->pos++) {
        if (!lista_esta_vacia(hash->tabla[iter->pos])) {
            if (lista) {
                lista_iter_destruir(lista);
            }
            iter->lista_iter = lista_iter_crear(hash->tabla[iter->pos]);
            iter->hash = hash;
            return iter;
        }
    }
    return NULL;
}

hash_iter_t *hash_iter_crear(const hash_t *hash) {
    hash_iter_t *iter = calloc(1, sizeof(hash_iter_t));
    iter->pos = 0;
    if (asignar_lista_iter(hash, iter, iter->lista_iter)) {
        return iter;
    }
    iter->lista_iter = NULL;
    iter->hash = hash;
    return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) {
        return false;
    }
    lista_iter_avanzar(iter->lista_iter);
    if (!lista_iter_al_final(iter->lista_iter)) {
        return true;
    }
    iter->pos += 1;

    asignar_lista_iter(iter->hash, iter, iter->lista_iter);
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) {
        return NULL;
    }
    campo_t *campo_actual = (campo_t *)(lista_iter_ver_actual(iter->lista_iter));
    return campo_actual->clave;
}

bool hash_iter_al_final(const hash_iter_t *iter) {
    if (!iter->lista_iter) {
        return true;
    }
    return iter->pos == iter->hash->capacidad && lista_iter_al_final(iter->lista_iter);
}

void hash_iter_destruir(hash_iter_t *iter) {
    lista_iter_destruir(iter->lista_iter);
    free(iter);
    return;
}
