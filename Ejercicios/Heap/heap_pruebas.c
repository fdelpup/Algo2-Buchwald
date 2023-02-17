#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "testing.h"

int num_random() {
    return rand() % 100000;
}

int int_cmp(const void *a, const void *b) {
    int *num_a = (int *)a;
    int *num_b = (int *)b;

    if (num_a < num_b) {
        return -1;
    }
    if (num_a > num_b) {
        return 1;
    }
    return 0;
}

void pruebas_heap_vacio() {
    heap_t *heap = heap_crear(int_cmp);

    print_test("Heap vacio se creo correctamente", heap_cantidad(heap) == 0);
    print_test("Max de heap vacio es NULL", heap_ver_max(heap) == NULL);
    print_test("Desencolar un elemento del heap vacio es NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
}

void pruebas_heap_encolar_desencolar() {
    heap_t *heap = heap_crear(int_cmp);

    int elementos[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bool error = false;
    for (int i = 0; i < 10; i++) {
        if (!heap_encolar(heap, &elementos[i])) {
            error = true;
            break;
        }
    }

    print_test("Se encolaron correctamente todos los elementos en el heap", error == false);
    print_test("Cantidad de elementos en heap = 10", heap_cantidad(heap) == 10);
    print_test("Ver el maximo del heap es correcto", heap_ver_max(heap) == &elementos[9]);

    for (int i = 10; i >= 1; i--) {
        int *elemento = heap_desencolar(heap);
        error = !(*elemento == i);
        if (error) break;
    }
    print_test("Los elementos del heap se desencolaron correctamente", error == false);
    print_test("Cantidad de elementos en el heap = 0", heap_cantidad(heap) == 0);
    print_test("El maximo del heap es NULL (heap vacio)", heap_ver_max(heap) == NULL);

    heap_destruir(heap, NULL);
}

void pruebas_heap_volumen(void) {
    heap_t *heap = heap_crear(int_cmp);
    int elementos[1000][1];
    bool error_encolar = false;
    bool error_desencolar = false;

    for (int i = 0; i < 1000; i++) {
        *elementos[i] = num_random();
        if (!heap_encolar(heap, elementos[i])) {
            error_encolar = true;
            break;
        }
    }
    print_test("Todos los elementos se encolaron en el heap correctamente", error_encolar == false);
    print_test("Cantidad de elementos en el heap = 1000", heap_cantidad(heap) == 1000);

    for (int i = 999; i >= 0; i--) {
        if (!heap_desencolar(heap)) {
            error_desencolar = true;
            break;
        }
    }
    print_test("Los elementos se desencolaron correctamente", error_desencolar == false);
    print_test("Cantidad de elementos en el heap es 0", heap_cantidad(heap) == 0);
    print_test("Ver el max del heap es correcto", heap_ver_max(heap) == NULL);
    heap_destruir(heap, NULL);
}

static void prueba_heap_borrar() {
    heap_t *heap = heap_crear(int_cmp);

    char *dato1 = "perro";
    char *dato2 = "gato";
    char *dato3 = "vaca";

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba heap insertar dato1", heap_encolar(heap, dato1));
    print_test("Prueba heap insertar dato2", heap_encolar(heap, dato2));
    print_test("Prueba heap insertar dato3", heap_encolar(heap, dato3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba heap ver max devuelve dato3", heap_ver_max(heap) == dato3);
    print_test("Prueba heap desencolar, desencola el dato3", heap_desencolar(heap) == dato3);
    print_test("Prueba heap ver max difiere de dato3", heap_ver_max(heap) != dato3);
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);

    print_test("Prueba heap ver max devuelve dato2", heap_ver_max(heap) == dato2);
    print_test("Prueba heap desencolar, desencola el dato2", heap_desencolar(heap) == dato2);
    print_test("Prueba heap ver max difiere de dato2", heap_ver_max(heap) != dato2);
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);

    print_test("Prueba heap ver max devuelve dato1", heap_ver_max(heap) == dato1);
    print_test("Prueba heap desencolar, desencola el dato1", heap_desencolar(heap) == dato1);
    print_test("Prueba heap ver max difiere de dato1", heap_ver_max(heap) != dato1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    print_test("Prueba heap desencolar heap vacio devuelve NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
}

static void prueba_heap_destruir_con_free() {
    heap_t *heap = heap_crear(int_cmp);

    char *valor1;
    char *valor2;
    char *valor3;

    /* Pide memoria para 2 valores */
    valor1 = malloc(10 * sizeof(char));
    valor2 = malloc(10 * sizeof(char));
    valor3 = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba heap insertar clave1", heap_encolar(heap, valor1));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);

    print_test("Prueba heap insertar clave1", heap_encolar(heap, valor2));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);

    print_test("Prueba heap insertar clave1", heap_encolar(heap, valor3));
    print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);

    /* Se destruye el hash (se debe liberar lo que quedó dentro) */
    heap_destruir(heap, free);
}

static void prueba_heap_encolar_null() {
    heap_t *heap = heap_crear(int_cmp);

    // Encolar NULL y Encolar mismos elementos

    char *valor = NULL;

    // Inserta varias veces NULL
    print_test("Prueba heap encolar NULL", heap_encolar(heap, valor));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver max es valor NULL", heap_ver_max(heap) == valor);

    print_test("Prueba heap encolar NULL", heap_encolar(heap, valor));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);

    print_test("Prueba heap encolar NULL", heap_encolar(heap, valor));
    print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);

    print_test("Prueba heap borrar valor vacia, es valor NULL", heap_desencolar(heap) == valor);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 2);

    print_test("Prueba heap borrar valor vacia, es valor NULL", heap_desencolar(heap) == valor);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 1);

    heap_destruir(heap, NULL);
}

void pruebas_heap_crear_arr() {
    int vector[5] = {20, 50, -3, 1, 7};
    void *aux[5];
    for (int i = 0; i < 5; i++) aux[i] = &vector[i];

    heap_t *heap = heap_crear_arr((void **)aux, 5, int_cmp);
    bool ok = true;

    heap_sort((void **)aux, 5, int_cmp);

    for (int i = 4; i >= 0; i--) {
        ok = heap_ver_max(heap) == aux[i];
        heap_desencolar(heap);
        if (!ok) break;
    }
    print_test("EL heap se creo correctamente desde el arreglo asignado", ok);
    heap_destruir(heap, NULL);
}

void pruebas_heap_estudiante(void) {
    pruebas_heap_vacio();
    pruebas_heap_encolar_desencolar();
    pruebas_heap_volumen();
    prueba_heap_borrar();
    prueba_heap_destruir_con_free();
    prueba_heap_encolar_null();
    pruebas_heap_crear_arr();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}
#endif