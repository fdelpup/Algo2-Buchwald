#include "abb.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct abb_nodo {
    struct abb_nodo *izq;
    struct abb_nodo *der;
    const char *clave;
    void *dato;
};

struct abb {
    abb_nodo_t *raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t cant;
};

abb_t *abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
    abb_t *arbol = malloc(sizeof(abb_t));
    if (!arbol) {
        return NULL;
    }
    arbol->raiz = NULL;
    arbol->cmp = cmp;
    arbol->destruir_dato = destruir_dato;
    arbol->cant = 0;
    return arbol;
}

bool _abb_guardar(abb_nodo_t *abb, const char *clave, void *dato, abb_t *arbol) {
    if (!abb) {
        abb = malloc(sizeof(abb_nodo_t));
        if (!abb) {
            return false;
        }
        const char *clave_1 = strdup(clave);
        if (clave_1 == NULL) {
            return false;
        }
        abb->clave = clave_1;
        abb->dato = dato;
        arbol->cant += 1;
        abb->izq = NULL;
        abb->der = NULL;
        return true;
    }
    if (arbol->cmp(clave, abb->clave) == 0) {
        void *dato_a_borrar = abb->dato;
        abb->dato = dato;
        arbol->destruir_dato(dato_a_borrar);
        return true;
    }
    if (arbol->cmp(clave, abb->clave) < 0) {
        return _abb_guardar(abb->izq, clave, dato, arbol);
    } else {
        return _abb_guardar(abb->der, clave, dato, arbol);
    }
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    return _abb_guardar(arbol->raiz, clave, dato, arbol);
}

abb_nodo_t *abb_a_izquierda(abb_nodo_t *abb) {
    if (!abb->izq) {
        return abb;
    }

    return abb_a_izquierda(abb->izq);
}

void *_abb_borrar(abb_nodo_t *abb, const char *clave, abb_t *arbol, abb_nodo_t *padre) {
    if (!abb) {
        return NULL;
    }
    if (arbol->cmp(abb->clave, clave) == 0) {
        if (!abb->der) {
            if (padre == NULL) {
                arbol->raiz = abb->izq;
                void *dato = abb->dato;
                free(abb);
                arbol->cant -= 1;

                return dato;
            }
            padre->der = abb->izq;
            void *dato = abb->dato;
            free(abb);
            arbol->cant -= 1;
            return dato;
        }
        abb_nodo_t *reemplazo = abb_a_izquierda(abb->der);
        void *dato = abb->dato;
        abb->clave = reemplazo->clave;
        abb->dato = reemplazo->dato;
        if (reemplazo->der) {
            padre->izq = reemplazo->der;
        }
        free(reemplazo);
        arbol->cant -= 1;
        return dato;
    }
    if (arbol->cmp(clave, abb->clave) < 0) {
        return _abb_borrar(abb->izq, clave, arbol, abb);
    } else {
        return _abb_borrar(abb->der, clave, arbol, abb);
    }
}

void *abb_borrar(abb_t *arbol, const char *clave) {
    if (!arbol->raiz) {
        return NULL;
    }

    return _abb_borrar(arbol->raiz, clave, arbol, NULL);
}

void *_abb_obtener(abb_nodo_t *abb, const char *clave, abb_comparar_clave_t cmp) {
    if (!abb) {
        printf("NULL\n");
        return NULL;
    }
    if ((cmp)(clave, abb->clave) == 0) {
        return abb->dato;
    }
    if ((cmp)(clave, abb->clave) < 0) {
        printf("izq\n");
        return _abb_obtener(abb->izq, clave, cmp);
    } else {
        printf("der\n");
        return _abb_obtener(abb->der, clave, cmp);
    }
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
    if (!arbol->raiz) {
        printf("Olasoyjuan\n");
        return NULL;
    }
    return _abb_obtener(arbol->raiz, clave, arbol->cmp);
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
    if (abb_obtener(arbol, clave)) {
        return true;
    }
    return false;
}

size_t abb_cantidad(const abb_t *arbol) {
    return arbol->cant;
}

void _abb_destruir(abb_nodo_t *abb, abb_t *arbol) {
    if (!abb) {
        return;
    }
    _abb_destruir(abb->izq, arbol);
    _abb_destruir(abb->der, arbol);
    arbol->destruir_dato(abb->dato);
    free(abb);
    return;
}

void abb_destruir(abb_t *arbol) {
    if (!arbol->raiz) {
        free(arbol);
        return;
    }
    _abb_destruir(arbol->raiz, arbol);
    free(arbol);
    return;
}
