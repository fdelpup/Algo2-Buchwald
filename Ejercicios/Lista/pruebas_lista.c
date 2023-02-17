#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "pila.h"
#include "testing.h"

// Chequea que al crear una lista esta arranca vacia.

static void prueba_lista_vacia(void) {
    lista_t *lista = lista_crear();
    print_test("Lista esta vacia .. ", lista_esta_vacia(lista));
    print_test("No se puede eliminar elemento de lista vacia", lista_borrar_primero(lista) == NULL);
    print_test("Lista vacia no tiene primero (NULL)", lista_ver_primero(lista) == NULL);
    lista_destruir(lista, NULL);
    printf("\n");
}

// Se pueda crear y destruir correctamente la estructura.

static void prueba_crear_destruir_lista(void) {
    lista_t *lista = lista_crear();
    print_test("Crear lista vacia ", lista != NULL);
    lista_destruir(lista, NULL);
    // PRUEBA DE DESTRUCCION DE COLA CON VALGRIND "OK"
    printf("\n");
}

static void prueba_insertar_eliminar_lista(void) {
    lista_t *lista = lista_crear();
    void *direc_int_1 = malloc(sizeof(int));
    void *direc_int_2 = malloc(sizeof(int));
    void *direc_int_3 = malloc(sizeof(int));
    void *direc_int_4 = malloc(sizeof(int));
    void *direc_int_5 = malloc(sizeof(int));
    void *direc_int_6 = malloc(sizeof(int));

    print_test("Insertar primero funciona correctamente en 1", lista_insertar_primero(lista, direc_int_1));
    print_test("Primero es 1", (lista_ver_primero(lista) == direc_int_1));
    print_test("Ultimo es 1", (lista_ver_ultimo(lista) == direc_int_1));
    print_test("Insertar primero funciona correctamente en 2", lista_insertar_primero(lista, direc_int_2));
    print_test("Primero es 2", (lista_ver_primero(lista) == direc_int_2));
    print_test("Ultimo es 1", (lista_ver_ultimo(lista) == direc_int_1));
    print_test("Insertar primero funciona correctamente en 3", lista_insertar_primero(lista, direc_int_3));
    print_test("Primero es 3", (lista_ver_primero(lista) == direc_int_3));
    print_test("Ultimo es 1", (lista_ver_ultimo(lista) == direc_int_1));

    print_test("Insertar ultimo funciona correctamente en 4", lista_insertar_ultimo(lista, direc_int_4));
    print_test("Primero es 3", (lista_ver_primero(lista) == direc_int_3));
    print_test("Ultimo es 4", lista_ver_ultimo(lista) == direc_int_4);
    print_test("Insertar ultimo funciona correctamente en 5", lista_insertar_ultimo(lista, direc_int_5));
    print_test("Primero es 3", (lista_ver_primero(lista) == direc_int_3));
    print_test("Ultimo es 5", (lista_ver_ultimo(lista) == direc_int_5));
    print_test("Insertar ultimo funciona correctamente en 6", lista_insertar_ultimo(lista, direc_int_6));
    print_test("Primero es 3", (lista_ver_primero(lista) == direc_int_3));
    print_test("Ultimo es 6", (lista_ver_ultimo(lista) == direc_int_6));

    void *dato_3 = lista_borrar_primero(lista);
    print_test("Valor del elemento borrado 3", dato_3 == direc_int_3);

    print_test("2 es primero al eliminar 3", lista_ver_primero(lista) == direc_int_2);
    void *dato_2 = lista_borrar_primero(lista);
    print_test("Valor del elemento eliminado 2", dato_2 == direc_int_2);

    print_test("1 es primero al eliminar 2", lista_ver_primero(lista) == direc_int_1);
    void *dato_1 = lista_borrar_primero(lista);
    print_test("Valor del elemento desencolado 1", dato_1 == direc_int_1);

    free(dato_3);
    free(dato_2);
    free(dato_1);

    lista_destruir(lista, free);

    printf("\n");
}

static void insertar_elemento_null(void) {
    lista_t *lista = lista_crear();
    print_test("Insertar el elemento NULL --> VALIDO (en primero)", (lista_insertar_primero(lista, NULL)));
    print_test("Insertar el elemento NULL --> VALIDO (en ultimo)", (lista_insertar_ultimo(lista, NULL)));
    print_test("Primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("Ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Lista no esta vacia", lista_esta_vacia(lista) == false);
    print_test("Eliminar elementos devuelve NULL", lista_borrar_primero(lista) == NULL);
    lista_destruir(lista, NULL);
    printf("\n");
}

static void prueba_volumen_lista(void) {
    lista_t *lista = lista_crear();
    int numero_a_insertar = 1000;
    int numeros[numero_a_insertar];

    // Lleno el vector con numeros para insertar
    for (int i = 0; i < numero_a_insertar; i++) {
        numeros[i] = i;
    }
    bool res_insertar_primero = true;
    // Inserto al principio n/2 veces
    for (int i = 0; i < (numero_a_insertar) / 2; i++) {
        if (!lista_insertar_primero(lista, &numeros[i])) {
            res_insertar_primero = false;
        }
    }
    print_test("lista_insertar_primero funciona correctamente", res_insertar_primero);

    bool res_insertar_ultimo = true;
    for (int i = (numero_a_insertar) / 2; i < numero_a_insertar; i++) {
        if (!lista_insertar_ultimo(lista, &numeros[i])) {
            res_insertar_ultimo = false;
        }
    }
    print_test("lista_insertar_ultimo funciona correctamente", res_insertar_ultimo);

    lista_destruir(lista, NULL);
    printf("\n");
}

void pila_destruir_wrapper(void *elem) {
    pila_destruir(elem);
}

static void pruebas_con_pilas(void) {
    lista_t *lista = lista_crear();
    pila_t *pila = pila_crear();
    int valor = 1;
    int valor2 = 2;
    int valor3 = 3;
    int valor4 = 4;
    print_test("Apilo correctamente", pila_apilar(pila, &valor));
    print_test("Apilo correctamente", pila_apilar(pila, &valor2));
    print_test("Apilo correctamente", pila_apilar(pila, &valor3));
    print_test("Apilo correctamente", pila_apilar(pila, &valor4));

    print_test("Insertar primero funciona para estructuras", lista_insertar_primero(lista, pila));
    print_test("Insertar ultimo funciona para estructuras", lista_insertar_ultimo(lista, pila));
    print_test("Se puede borrar una estructura de la lista", lista_borrar_primero(lista));
    print_test("Se puede ver el primero", lista_ver_primero(lista) == pila);
    print_test("Se puede ver el ultimo", lista_ver_ultimo(lista) == pila);
    lista_destruir(lista, pila_destruir_wrapper);
    printf("\n");
}

static void prueba_igual_nueva(void) {
    lista_t *lista = lista_crear();
    int valor = 1;
    print_test("Inserto primero correctamente", lista_insertar_primero(lista, &valor));
    print_test("Borro el primero correctamente", lista_borrar_primero(lista) == &valor);
    print_test("La lista tiene 0 elementos", lista_largo(lista) == 0 && lista_esta_vacia(lista));
    print_test("Lista vacia no se vale eliminar elementos && Se comporta como recien creada", (lista_borrar_primero(lista) == NULL));
    print_test("Lista vacia no se vale pedir el primer elemento && Se comporta como recien creada", (lista_ver_primero(lista) == NULL));

    lista_destruir(lista, NULL);
    printf("\n");
}

// Al insertar un elemento en la posición en la que se crea el iterador, efectivamente se inserta al principio.

static void insertar_en_principio(void) {
    lista_t *lista = lista_crear();
    int valor = 1;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor));
    lista_iter_t *lista_iter = lista_iter_crear(lista);
    int valor_iter = 2;
    print_test("Se inserto correctamente en el iter", lista_iter_insertar(lista_iter, &valor_iter));
    print_test("Se inserto correctamente en la primera posicion", lista_ver_primero(lista) == &valor_iter);
    lista_destruir(lista, NULL);
    lista_iter_destruir(lista_iter);
    printf("\n");
}

// Insertar un elemento cuando el iterador está al final efectivamente es equivalente a insertar al final.

static void insertar_en_final(void) {
    lista_t *lista = lista_crear();
    int valor_1 = 1;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor_1));
    int valor_2 = 2;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor_2));

    lista_iter_t *lista_iter = lista_iter_crear(lista);

    int valor_iter = 3;
    print_test("Avanzo correctamente", lista_iter_avanzar(lista_iter));
    print_test("Avanzo correctamente", lista_iter_avanzar(lista_iter));

    print_test("Se inserto correctamente en el iter", lista_iter_insertar(lista_iter, &valor_iter));
    print_test("Se inserto correctamente en la ultima posicion", lista_ver_ultimo(lista) == &valor_iter);
    lista_destruir(lista, NULL);
    lista_iter_destruir(lista_iter);
    printf("\n");
}

// Insertar un elemento en el medio se hace en la posición correcta.

static void elemento_en_medio(void) {
    lista_t *lista = lista_crear();
    int valor_1 = 1;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor_1));
    int valor_2 = 2;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor_2));

    lista_iter_t *lista_iter = lista_iter_crear(lista);
    int valor_iter = 3;

    print_test("Avanzo correctamente", lista_iter_avanzar(lista_iter));
    print_test("Largo correcto == 2", lista_largo(lista) == 2);
    print_test("Se inserto correctamente en el iter", lista_iter_insertar(lista_iter, &valor_iter));

    print_test("Primero es 1", lista_ver_ultimo(lista) == &valor_1);
    print_test("Ultimo es 2", lista_ver_primero(lista) == &valor_2);
    print_test("Se inserto correctamente en el medio", lista_largo(lista) == 3);

    lista_destruir(lista, NULL);
    lista_iter_destruir(lista_iter);
    printf("\n");
}

// Al remover el elemento cuando se crea el iterador, cambia el primer elemento de la lista.

static void eliminar_primero_con_iter(void) {
    lista_t *lista = lista_crear();
    int valor_1 = 1;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor_1));
    int valor_2 = 2;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor_2));

    lista_iter_t *lista_iter = lista_iter_crear(lista);
    print_test("Se elimino correctamente el primer elemento", lista_iter_borrar(lista_iter) == &valor_2);

    lista_destruir(lista, NULL);
    lista_iter_destruir(lista_iter);
    printf("\n");
}

// Remover el último elemento con el iterador cambia el último de la lista.

static void eliminar_ultimo_con_iter(void) {
    lista_t *lista = lista_crear();
    int valor_1 = 1;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor_1));
    int valor_2 = 2;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor_2));

    lista_iter_t *lista_iter = lista_iter_crear(lista);

    print_test("Avanzo correctamente", lista_iter_avanzar(lista_iter));

    print_test("Se elimino correctamente el ultimo elemento", lista_iter_borrar(lista_iter) == &valor_1);

    lista_destruir(lista, NULL);
    lista_iter_destruir(lista_iter);
    printf("\n");
}

// Verificar que al remover un elemento del medio, este no está.

static void eliminar_medio_con_iter(void) {
    lista_t *lista = lista_crear();
    int valor_1 = 1;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor_1));
    int valor_2 = 2;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor_2));
    int valor_3 = 3;
    print_test("Se inserto correctamente en la lista", lista_insertar_primero(lista, &valor_3));

    lista_iter_t *lista_iter = lista_iter_crear(lista);

    print_test("Avanzo correctamente", lista_iter_avanzar(lista_iter));

    print_test("Se elimino correctamente el ultimo elemento", lista_iter_borrar(lista_iter) == &valor_2);

    lista_destruir(lista, NULL);
    lista_iter_destruir(lista_iter);
    printf("\n");
}

static void pruebas_lista_iter_vacia(void) {
    lista_t *lista = lista_crear();
    lista_iter_t *lista_iter = lista_iter_crear(lista);

    print_test("El actual del iter es NULL", lista_iter_ver_actual(lista_iter) == NULL);
    print_test("No se puede avanzar al estar vacia", lista_iter_avanzar(lista_iter) == false);
    print_test("Devuelve NULL al intentar borrar lista iter vacia", lista_iter_borrar(lista_iter) == NULL);

    lista_destruir(lista, NULL);
    lista_iter_destruir(lista_iter);
    printf("\n");
}

bool visitar_valores(void *dato, void *extra) {  // suma mayores
    if (*(size_t *)extra < (size_t) * ((int *)dato)) {
        *(size_t *)extra += (size_t) * ((int *)dato);
    }
    return true;
}
bool visitar_pares_anteriores(void *dato, void *extra) {  // suma pares
    if (*(size_t *)extra % 2 == 0) {
        *(size_t *)extra += (size_t) * ((int *)dato);
        return true;
    }
    return false;
}
static void pruebas_iter_interno(void) {
    lista_t *lista = lista_crear();
    int valor_1 = 1;
    int valor_2 = 2;
    int valor_3 = 3;
    int valor_4 = 1;
    int valor_5 = 4;
    print_test("Inserto en la ultima posicion correctamente", lista_insertar_ultimo(lista, &valor_1));
    print_test("Inserto en la ultima posicion correctamente", lista_insertar_ultimo(lista, &valor_2));
    print_test("Inserto en la ultima posicion correctamente", lista_insertar_ultimo(lista, &valor_3));
    print_test("Inserto en la ultima posicion correctamente", lista_insertar_ultimo(lista, &valor_4));
    print_test("Inserto en la ultima posicion correctamente", lista_insertar_ultimo(lista, &valor_5));

    size_t sumados = 0;
    lista_iterar(lista, visitar_valores, &sumados);
    print_test("El iterador interno sumo correctamente los valores mayores", sumados == 7);
    sumados = 0;
    lista_iterar(lista, visitar_pares_anteriores, &sumados);
    print_test("El iterador interno se corto porque la suma de los anteriores no son pares", sumados == 1);
    lista_destruir(lista, NULL);
}

void pruebas_lista_estudiante() {
    printf("\n");
    printf("-- Pruebas cola vacia --\n");
    prueba_lista_vacia();
    printf("-- Prueba destruir lista --\n");
    prueba_crear_destruir_lista();
    printf("-- Pruebas cola crear y destruir --\n");
    prueba_insertar_eliminar_lista();
    printf("-- Pruebas encolar elemento NULL --\n");
    insertar_elemento_null();
    printf("-- Pruebas destruir cola con funcion --\n");
    prueba_volumen_lista();
    printf("--Prueba insertar pila --\n");
    pruebas_con_pilas();
    printf("-- Prueba lista funciona como nueva --\n");
    prueba_igual_nueva();
    printf("-- Prueba iter inserta en principio --\n");
    insertar_en_principio();
    printf("-- Prueba iter inserta en ultimo --\n");
    insertar_en_final();
    printf("-- Prueba iter inserta en medio --\n");
    elemento_en_medio();
    printf("-- Prueba eliminar primero con iter --\n");
    eliminar_primero_con_iter();
    printf("-- Prueba eliminar ultimo con iter --\n");
    eliminar_ultimo_con_iter();
    printf("-- Prueba eliminar medio con iter --\n");
    eliminar_medio_con_iter();
    printf("-- Prueba lista iter vacia --\n");
    pruebas_lista_iter_vacia();
    printf("-- Prueba iter interno --\n");
    pruebas_iter_interno();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}
#endif