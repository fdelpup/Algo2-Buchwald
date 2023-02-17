#include "abb.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "pila.h"

typedef struct abb_nodo abb_nodo_t;

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

struct abb_iter {
    abb_nodo_t *abb_actual;
    pila_t *pila;
};

// -------------------------------- # FUNCIONES AUX # ------------------------------

abb_nodo_t *abb_a_izquierda(abb_nodo_t *abb, pila_t *pila) {
    if (!abb) {
        return NULL;
    }
    if (pila) {
        pila_apilar(pila, abb);
    }
    if (!abb->izq) {
        return abb;
    }
    return abb_a_izquierda(abb->izq, pila);
}

abb_nodo_t *abb_a_izquierda_padre(abb_nodo_t *abb, abb_nodo_t *padre) {
    if (!abb) {
        return NULL;
    }
    if (!abb->izq) {
        return padre;
    }
    return abb_a_izquierda_padre(abb->izq, abb);
}

void *abb_nodo_destruir(abb_nodo_t *nodo) {
    if (!nodo) {
        return NULL;
    }
    void *dato_nodo = nodo->dato;
    free((void *)nodo->clave);
    free(nodo);
    return dato_nodo;
}

void *borrar_un_hijo(abb_nodo_t *abb, abb_nodo_t *abb_h, abb_t *arbol, abb_nodo_t *padre, int lado) {
    if (padre == NULL) {
        arbol->raiz = abb_h;
        void *dato = abb_nodo_destruir(abb);
        arbol->cant -= 1;
        return dato;
    }
    if (lado == -1) {
        padre->izq = abb_h;
    }
    if (lado == 1) {
        padre->der = abb_h;
    }
    void *dato = abb_nodo_destruir(abb);
    arbol->cant -= 1;
    return dato;
}

void *_abb_buscar(abb_nodo_t *abb, const char *clave, const abb_t *arbol, abb_nodo_t **padre) {
    if (!abb) {
        return NULL;
    }
    if ((arbol->cmp)(clave, abb->clave) == 0) {
        return abb;
    }
    *padre = abb;
    if ((arbol->cmp)(clave, abb->clave) < 0) {
        return _abb_buscar(abb->izq, clave, arbol, padre);
    } else {
        return _abb_buscar(abb->der, clave, arbol, padre);
    }
}
// -------------------------------- # PRIMITIVAS DEL ARBOL # ------------------------------

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

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    abb_nodo_t *abb_aux_padre = NULL;
    abb_nodo_t *abb_aux = _abb_buscar(arbol->raiz, clave, arbol, &abb_aux_padre);
    if (!abb_aux) {
        abb_nodo_t *abb_nuevo = malloc(sizeof(abb_nodo_t));
        if (!abb_nuevo) {
            return false;
        }
        const char *clave_1 = strdupp(clave);
        if (clave_1 == NULL) {
            return false;
        }
        abb_nuevo->clave = clave_1;
        abb_nuevo->dato = dato;
        arbol->cant += 1;
        abb_nuevo->izq = NULL;
        abb_nuevo->der = NULL;
        if (abb_aux_padre == NULL) {
            arbol->raiz = abb_nuevo;
            return true;
        }
        if (arbol->cmp(clave, abb_aux_padre->clave) < 0) {
            abb_aux_padre->izq = abb_nuevo;
        } else {
            abb_aux_padre->der = abb_nuevo;
        }

        return true;
    }
    void *dato_a_borrar = abb_aux->dato;
    abb_aux->dato = dato;
    if (arbol->destruir_dato) {
        arbol->destruir_dato(dato_a_borrar);
    }
    return true;
}

// ........................................................................

void *_abb_borrar_nodo(abb_nodo_t *abb, const char *clave, abb_t *arbol, abb_nodo_t *padre, int lado) {
    if (!abb->der && !abb->izq) {
        if (!padre) {
            arbol->raiz = NULL;
        }
        void *dato = abb_nodo_destruir(abb);
        arbol->cant -= 1;
        if (lado == -1) {
            padre->izq = NULL;
        }
        if (lado == 1) {
            padre->der = NULL;
        }

        return dato;
    }
    if (abb->izq && !abb->der) {
        return borrar_un_hijo(abb, abb->izq, arbol, padre, lado);
    }
    if (abb->der && !abb->izq) {
        return borrar_un_hijo(abb, abb->der, arbol, padre, lado);
    }
    return NULL;
}

void *abb_borrar(abb_t *arbol, const char *clave) {
    if (!arbol) {
        return NULL;
    }
    if (!arbol->raiz) {
        return NULL;
    }
    abb_nodo_t *abb_aux_padre = NULL;
    abb_nodo_t *abb_aux = _abb_buscar(arbol->raiz, clave, arbol, &abb_aux_padre);
    if (!abb_aux) {
        return NULL;
    }
    if (abb_aux->der && abb_aux->izq) {
        abb_nodo_t *reemplazo = abb_a_izquierda(abb_aux->der, NULL);
        abb_nodo_t *padre_reemplazo = abb_a_izquierda_padre(abb_aux->der, abb_aux);
        const char *clave_reemplazante = strdupp(reemplazo->clave);
        if (!clave_reemplazante) {
            return NULL;
        }
        void *dato_reemplazante;
        if (reemplazo == abb_aux->der) {
            dato_reemplazante = _abb_borrar_nodo(reemplazo, clave_reemplazante, arbol, padre_reemplazo, 1);

        } else {
            dato_reemplazante = _abb_borrar_nodo(reemplazo, clave_reemplazante, arbol, padre_reemplazo, -1);
        }
        free((char *)abb_aux->clave);
        abb_aux->clave = clave_reemplazante;
        void *dato_borrado = abb_aux->dato;
        abb_aux->dato = dato_reemplazante;
        return dato_borrado;
    }
    if (abb_aux_padre && (abb_aux_padre->izq == abb_aux)) {
        return _abb_borrar_nodo(abb_aux, clave, arbol, abb_aux_padre, -1);
    }
    if (abb_aux_padre && (abb_aux_padre->der == abb_aux)) {
        return _abb_borrar_nodo(abb_aux, clave, arbol, abb_aux_padre, 1);
    } else {
        return _abb_borrar_nodo(abb_aux, clave, arbol, abb_aux_padre, 0);
    }
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
    if (!arbol->raiz) {
        return NULL;
    }
    abb_nodo_t *abb_aux_padre = NULL;
    abb_nodo_t *abb_aux = _abb_buscar(arbol->raiz, clave, arbol, &abb_aux_padre);
    if (abb_aux) {
        return abb_aux->dato;
    }
    return NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
    if (!arbol->raiz) {
        return false;
    }
    abb_nodo_t *abb_aux_padre = NULL;
    return _abb_buscar(arbol->raiz, clave, arbol, &abb_aux_padre);
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
    void *dato_nodo = abb_nodo_destruir(abb);
    if (arbol->destruir_dato) {
        arbol->destruir_dato(dato_nodo);
    }
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

bool _abb_in_order(abb_nodo_t *abb, bool visitar(const char *clave, void *dato, void *extra), void *extra) {
    if (!abb) {
        return true;
    }
    bool estado;
    estado = _abb_in_order(abb->izq, visitar, extra);
    if (estado == false) {
        return false;
    }
    if (!visitar(abb->clave, abb->dato, extra)) {
        return false;
    }
    estado = _abb_in_order(abb->der, visitar, extra);
    if (estado == false) {
        return false;
    }
    return true;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *clave, void *dato, void *extra), void *extra) {
    _abb_in_order(arbol->raiz, visitar, extra);
}

// -------------------------------- # PRIMITIVAS DEL ITERADOR # ------------------------------

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
    abb_iter_t *iter = calloc(1, sizeof(abb_iter_t));
    if (!iter) {
        return NULL;
    }

    iter->pila = pila_crear();
    if (!iter->pila) {
        free(iter);
        return NULL;
    }
    iter->abb_actual = NULL;
    if (arbol->raiz) {
        iter->abb_actual = abb_a_izquierda(arbol->raiz, iter->pila);
    }

    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
    if (abb_iter_in_al_final(iter)) {
        return false;
    }
    pila_desapilar(iter->pila);
    if (!iter->abb_actual->der) {
        iter->abb_actual = pila_ver_tope(iter->pila);
        return true;
    }
    iter->abb_actual = abb_a_izquierda(iter->abb_actual->der, iter->pila);
    return true;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
    return pila_esta_vacia(iter->pila);
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
    if (abb_iter_in_al_final(iter)) {
        return NULL;
    }
    return iter->abb_actual->clave;
}

void abb_iter_in_destruir(abb_iter_t *iter) {
    pila_destruir(iter->pila);
    free(iter);
}