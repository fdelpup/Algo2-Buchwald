#include "heap.h"

#include <stdlib.h>
#include <string.h>

#include "stdio.h"
#define TAM_INICIAL 1000
#define COEFICIENTE_REDIMENSION1 9
#define AUMENTO 2
#define COEFICIENTE_REDIMENSION2 4
#define DISMINUCION 2

struct heap {
    void **vector;
    cmp_func_t cmp;
    size_t cantidad;
    size_t tam;
};

/***********************
 *                    FUNCIONES AUXILIARES                         *
 ***********************/

void swap(void **vector, size_t x, size_t y) {
    void *aux = vector[x];
    void *aux2 = vector[y];
    vector[x] = aux2;
    vector[y] = aux;
}

bool upheap(void **vector, size_t pos, cmp_func_t cmp) {
    if (pos == 0) return false;

    size_t pos_padre = (pos - 1) / 2;
    size_t pos_actual = pos;

    if (cmp(vector[pos_actual], vector[pos_padre]) > 0) {
        swap(vector, pos_actual, pos_padre);
        pos_actual = pos_padre;
        pos_padre = (pos_actual - 1) / 2;
        upheap(vector, pos_actual, cmp);
    }
    return true;
}

size_t buscar_max(size_t pos, size_t izquierda, size_t cantidad, cmp_func_t cmp, void **vector) {
    size_t derecha = izquierda + 1;
    if (derecha >= cantidad) return izquierda;
    if ((cmp(vector[izquierda], vector[derecha]) > 0)) return izquierda;
    return derecha;
}

void downheap(void **vector, size_t pos, cmp_func_t cmp, size_t cantidad) {
    size_t max = pos, izquierda = (pos * 2) + 1;
    if (izquierda >= cantidad) return;

    max = buscar_max(pos, izquierda, cantidad, cmp, vector);

    if (cmp(vector[pos], vector[max]) < 0) swap(vector, pos, max);

    downheap(vector, max, cmp, cantidad);
}

void heapify(void **vector, size_t cantidad, cmp_func_t cmp) {
    for (size_t i = 0; i < cantidad; i++) {
        downheap(vector, (cantidad - 1 - i), cmp, cantidad);
    }
}

bool heap_redimensionar(heap_t *heap, size_t nuevo_tam) {
    if (!heap) return false;
    void *vector_nuevo = realloc(heap->vector, sizeof(void *) * nuevo_tam);
    if (!vector_nuevo) return false;
    heap->vector = vector_nuevo;
    heap->tam = nuevo_tam;
    return true;
}

/***********************
 *                    PRIMITIVAS DEL HEAP                          *
 ***********************/

heap_t *heap_crear(cmp_func_t cmp) {
    if (!cmp) return NULL;

    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap) return NULL;

    heap->cmp = cmp;
    heap->cantidad = 0;
    heap->tam = TAM_INICIAL;

    heap->vector = malloc(sizeof(void *) * TAM_INICIAL);
    if (!heap->vector) {
        free(heap);
        return NULL;
    }
    return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heap_t *heap = heap_crear(cmp);
    if (!heap) return NULL;

    heapify(arreglo, n, cmp);

    if (n >= heap->tam) {
        if (!heap_redimensionar(heap, n)) return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        heap->vector[i] = arreglo[i];
        heap->cantidad++;
    }
    return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
    if (destruir_elemento) {
        for (size_t i = 0; i < heap->cantidad; i++) destruir_elemento(heap->vector[i]);
    }
    free(heap->vector);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap) {
    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap) {
    return (heap->cantidad == 0);
}

void *heap_ver_max(const heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;
    return heap->vector[0];
}

bool heap_encolar(heap_t *heap, void *elem) {
    if (!elem || !heap) return false;

    if (heap->cantidad >= (heap->tam) / COEFICIENTE_REDIMENSION1) {
        if (!heap_redimensionar(heap, heap->tam * AUMENTO)) return false;
    }
    void **vector = heap->vector;
    size_t posicion_actual = heap->cantidad;
    vector[posicion_actual] = elem;
    heap->cantidad++;
    upheap(vector, posicion_actual, heap->cmp);
    return true;
}

void *heap_desencolar(heap_t *heap) {
    if (!heap || heap_esta_vacio(heap)) return NULL;

    if (heap->cantidad < (heap->tam / COEFICIENTE_REDIMENSION2)) {
        heap_redimensionar(heap, heap->tam / DISMINUCION);
    }

    void **vector = heap->vector;
    size_t cantidad = heap->cantidad;

    void *elemento = vector[0];
    swap(vector, 0, cantidad - 1);
    vector[cantidad - 1] = NULL;
    heap->cantidad--;
    downheap(vector, 0, heap->cmp, heap->cantidad);
    return elemento;
}

/***********************
 *                           HEAPSORT                              *
 ***********************/

void heap_sort(void *elementos[], size_t cantidad, cmp_func_t cmp) {
    heapify(elementos, cantidad, cmp);
    for (size_t i = 0; i < cantidad; i++) {
        swap(elementos, 0, cantidad - 1 - i);
        downheap(elementos, 0, cmp, cantidad - 1 - i);
    }
}