#include "lista.h"

#include <stdio.h>
#include <stdlib.h>
typedef struct nodo nodo_t;

struct nodo {
    void *dato;
    nodo_t *prox;
};

nodo_t *crear_nodo(void *dato) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL) {
        return NULL;
    }
    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

struct lista {
    nodo_t *primero;
    nodo_t *ultimo;
    size_t largo;
};

void agregar_lista_vacia(lista_t *lista, nodo_t *nodo) {
    lista->primero = nodo;
    lista->ultimo = nodo;
}

void sumar_largo(lista_t *lista) { lista->largo += 1; }

void restar_largo(lista_t *lista) { lista->largo -= 1; }

lista_t *lista_crear(void) {
    lista_t *lista = malloc(sizeof(lista_t));
    if (lista == NULL) {
        return NULL;
    }

    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista) { return lista->largo == 0; }

bool lista_insertar_primero(lista_t *lista, void *dato) {
    nodo_t *nuevo_nodo = crear_nodo(dato);
    if (nuevo_nodo == NULL) {
        return false;
    }
    if (lista_esta_vacia(lista)) {
        agregar_lista_vacia(lista, nuevo_nodo);
    } else {
        nuevo_nodo->prox = lista->primero;
        lista->primero = nuevo_nodo;
    }
    sumar_largo(lista);
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t *nuevo_nodo = crear_nodo(dato);
    if (nuevo_nodo == NULL) {
        return false;
    }

    if (lista_esta_vacia(lista)) {
        agregar_lista_vacia(lista, nuevo_nodo);
    } else {
        lista->ultimo->prox = nuevo_nodo;
        lista->ultimo = nuevo_nodo;
    }
    sumar_largo(lista);
    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }

    void *dato = lista->primero->dato;
    nodo_t *nodo = lista->primero->prox;

    free(lista->primero);

    if (nodo == NULL) {
        lista->primero = NULL;
        lista->ultimo = NULL;
    } else {
        lista->primero = nodo;
    }
    restar_largo(lista);
    return dato;
}

void *lista_ver_primero(const lista_t *lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t *lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista) { return lista->largo; }

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
    nodo_t *actual = lista->primero;
    while (actual) {
        nodo_t *prox = actual->prox;
        if (destruir_dato) {
            (*destruir_dato)(actual->dato);
        }
        free(actual);
        actual = prox;
    }
    free(lista);
}

// Iterador Interno

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    if (!visitar) {
        return;
    }

    nodo_t *actual = lista->primero;
    while (actual) {
        nodo_t *prox = actual->prox;

        if (!visitar(actual->dato, extra)) {
            return;
        }
        actual = prox;
    }
}

//
// Imprimir una lista con iterador externo
//

struct lista_iter {
    nodo_t *actual;
    nodo_t *anterior;
    lista_t *lista_en_iter;
};

// lista_crear debe tener una lista no null
lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if (iter == NULL) {
        return NULL;
    }
    iter->lista_en_iter = lista;
    iter->actual = iter->lista_en_iter->primero;
    iter->anterior = NULL;
    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
    if (iter->actual == NULL) {
        return false;
    }
    iter->anterior = iter->actual;
    iter->actual = iter->actual->prox;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if (iter->actual == NULL) {
        return NULL;
    }
    return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
    return iter->actual == NULL;
}

void lista_iter_destruir(lista_iter_t *iter) { free(iter); }

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    if (iter->anterior == NULL) {
        lista_insertar_primero(iter->lista_en_iter, dato);
        iter->actual = iter->lista_en_iter->primero;
        return true;
    }
    if (lista_iter_al_final(iter)) {
        lista_insertar_ultimo(iter->lista_en_iter, dato);
        iter->actual = iter->lista_en_iter->ultimo;
        return true;
    }

    nodo_t *nuevo_nodo = crear_nodo(dato);
    if (nuevo_nodo == NULL) {
        return false;
    }

    iter->anterior->prox = nuevo_nodo;
    nuevo_nodo->prox = iter->actual;
    iter->actual = nuevo_nodo;
    sumar_largo(iter->lista_en_iter);

    return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) {
        return NULL;
    }
    void *dato = iter->actual->dato;
    nodo_t *prox = iter->actual->prox;

    if (iter->anterior == NULL) {
        void *dato_borrado = lista_borrar_primero(iter->lista_en_iter);
        iter->actual = prox;
        return dato_borrado;
    } else if (prox == NULL) {
        void *dato_borrado = iter->lista_en_iter->ultimo->dato;
        iter->anterior->prox = prox;
        free(iter->actual);
        iter->lista_en_iter->ultimo = iter->anterior;
        iter->actual = prox;

        restar_largo(iter->lista_en_iter);
        return dato_borrado;
    }

    free(iter->actual);
    iter->anterior->prox = prox;
    iter->actual = prox;
    restar_largo(iter->lista_en_iter);
    return dato;
}
