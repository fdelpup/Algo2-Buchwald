#include "heap.h"

#include <stdio.h>
#include <stdlib.h>
#define AGRANDAR 2
#define REDIMENSION_DESENCOLAR 4
#define ACHICAR 2

struct heap {
    void **datos;
    size_t tam;
    size_t cant;
    cmp_func_t cmp;
};

heap_t *heap_crear(cmp_func_t cmp) {
    if (!cmp) {
        return NULL;
    }

    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap) {
        return NULL;
    }
    heap->tam = 10;
    heap->datos = malloc(sizeof(void *) * heap->tam);
    if (!heap->datos) {
        return NULL;
    }
    heap->cant = 0;
    heap->cmp = cmp;
    return heap;
}
void swap(void *elementos[], size_t x, size_t y) {
    void *auxiliar_1 = elementos[x];
    void *auxiliar_2 = elementos[y];

    elementos[x] = auxiliar_2;
    elementos[y] = auxiliar_1;
}

size_t maximo(size_t h_izq, size_t cantidad, cmp_func_t cmp, void *elementos[]) {
    size_t h_der = h_izq + 1;
    if (h_der >= cantidad) {
        return h_izq;
    }
    if ((cmp(elementos[h_izq], elementos[h_der]) > 0)) {
        return h_izq;
    }
    return h_der;
}
void downheap(void *elementos[], cmp_func_t cmp, size_t indice, size_t cantidad) {
    size_t max = indice;
    size_t h_izq = (indice * 2) + 1;
    if (h_izq >= cantidad) {
        return;
    }

    max = maximo(h_izq, cantidad, cmp, elementos);

    if (cmp(elementos[indice], elementos[max]) < 0) {
        swap(elementos, indice, max);
    }
    downheap(elementos, cmp, max, cantidad);
}
void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
    if (destruir_elemento) {
        for (int i = 0; i < heap->cant; i++) {
            destruir_elemento(heap->datos[i]);
        }
    }
    free(heap->datos);
    free(heap);
    return;
}

size_t heap_cantidad(const heap_t *heap) {
    return heap->cant;
}
bool heap_esta_vacio(const heap_t *heap) {
    return heap->cant == 0;
}
void upheap(void *elementos[], cmp_func_t cmp, size_t indice) {
    if (indice == 0) {
        return;
    }
    size_t pos_padre = (indice - 1) / 2;

    if (cmp(elementos[indice], elementos[pos_padre]) > 0) {
        swap(elementos, indice, pos_padre);
        upheap(elementos, cmp, pos_padre);
    }
    return;
}

bool redimensionar_heap(heap_t *heap, size_t nuevo_tam) {
    heap->tam = nuevo_tam;
    void **nuevo_arreglo = malloc(sizeof(void *) * heap->tam);
    if (!nuevo_arreglo) {
        return false;
    }
    for (int i = 0; i < heap->cant; i++) {
        nuevo_arreglo[i] = heap->datos[i];
    }
    free(heap->datos);
    heap->datos = nuevo_arreglo;
    return true;
}

bool heap_encolar(heap_t *heap, void *elem) {
    if (heap->cant == heap->tam) {
        if (!redimensionar_heap(heap, heap->tam * AGRANDAR)) {
            return false;
        }
    }
    heap->datos[heap->cant] = elem;
    upheap(heap->datos, heap->cmp, heap->cant);
    heap->cant += 1;
    return true;
}
void *heap_ver_max(const heap_t *heap) {
    if (heap->cant == 0) {
        return NULL;
    }
    return heap->datos[0];
}
void *heap_desencolar(heap_t *heap) {
    if (heap_esta_vacio(heap)) {
        return NULL;
    }
    if (heap->cant < (heap->tam / REDIMENSION_DESENCOLAR)) {
        redimensionar_heap(heap, heap->tam / ACHICAR);
    }
    void *elemento = heap->datos[0];
    swap(heap->datos, 0, heap->cant - 1);
    heap->datos[heap->cant - 1] = NULL;

    heap->cant--;

    downheap(heap->datos, heap->cmp, 0, heap->cant);
    return elemento;
}

void heapify(void *elementos[], size_t cantidad, cmp_func_t cmp) {
    for (size_t i = cantidad; i > 0; i--) {
        downheap(elementos, cmp, i - 1, cantidad);
    }
}

heap_t *heap_crear_arr(void *elementos[], size_t n, cmp_func_t cmp) {
    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap) {
        return NULL;
    }
    heap->tam = n * 2;
    heap->datos = malloc(sizeof(void *) * heap->tam);
    if (!heap->datos) {
        return NULL;
    }
    for (size_t i = 0; i < n; i++) {
        heap->datos[i] = elementos[i];
    }
    heapify(heap->datos, n, cmp);

    heap->cmp = cmp;
    heap->cant = n;
    return heap;
}

void heap_sort(void *elementos[], size_t cantidad, cmp_func_t cmp) {
    heapify(elementos, cantidad, cmp);
    for (size_t i = 0; i < cantidad; i++) {
        swap(elementos, 0, (cantidad - 1 - i));
        downheap(elementos, cmp, 0, (cantidad - 1 - i));
    }
}