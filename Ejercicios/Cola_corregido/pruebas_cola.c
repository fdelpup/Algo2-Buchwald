#include <stdio.h>
#include <stdlib.h>

#include "cola.h"
#include "testing.h"

void eliminar_dato(void *dato) {
    free(dato);
}

// Chequea que al crear una cola esta arranca vacia.

static void prueba_cola_vacia(void) {
    cola_t *cola = cola_crear();
    print_test("Cola esta vacia .. ", cola_esta_vacia(cola));
    print_test("Cola vacia no se desencola", cola_desencolar(cola) == NULL);
    print_test("Cola vacia no se ve el primero", cola_ver_primero(cola) == NULL);
    cola_destruir(cola, NULL);
    printf("\n");
}

// Se pueda crear y destruir correctamente la estructura.

static void prueba_crear_destruir_cola(void) {
    cola_t *cola = cola_crear();
    print_test("Crear cola vacia ", cola != NULL); 
    cola_destruir(cola, NULL);
    // PRUEBA DE DESTRUCCION DE COLA CON VALGRIND "OK"
    printf("\n");
}

static void prueba_encolar_desencolar_cola(void){
     cola_t *cola = cola_crear();
    void *direc_int_1 = malloc(sizeof(int));
    void *direc_int_2 = malloc(sizeof(int));
    void *direc_int_3 = malloc(sizeof(int));

    print_test("Encolar funciona correctamente en 1" , cola_encolar(cola, direc_int_1));
    print_test("Primero es 1 (Encolando)", (cola_ver_primero(cola) == direc_int_1));
    print_test("Encolar funciona correctamente en 2", cola_encolar(cola, direc_int_2));
    print_test("Encolar funciona correctamente en 3" , cola_encolar(cola, direc_int_3));

    print_test("Cola no esta vacia (Encolando) ", !(cola_esta_vacia(cola)));

    void *dato_1 = cola_desencolar(cola);
    print_test("Valor del elemento desencolado 3", dato_1 == direc_int_1);
    
    
    print_test("2 es primero al desencolar 1 (Desencolando)", (cola_ver_primero(cola) == direc_int_2));
    void *dato_2 = cola_desencolar(cola);
    print_test("Valor del elemento desencolado 2", dato_2 == direc_int_2);
    
    
    print_test("3 es primero al desencolar 2 (Desencolando)", (cola_ver_primero(cola) == direc_int_3));
    void *dato_3 = cola_desencolar(cola);
    print_test("Valor del elemento desencolado 1", dato_3 == direc_int_3);
    
    
    print_test("Cola esta vacia (Desencolando)", cola_esta_vacia(cola));

    print_test("Cola vacia no se vale desencolar && Se comporta como recien creada", (cola_desencolar(cola) == NULL));
    print_test("COla vacia no se vale pedir el primero && Se comporta como recien creada", (cola_ver_primero(cola) == NULL));

    eliminar_dato(dato_1);
    eliminar_dato(dato_2);
    eliminar_dato(dato_3);

    cola_destruir(cola, eliminar_dato);
    
    printf("\n");
}

// El encolar el elemento NULL es válido.

static void encolar_elemento_null(void){
    cola_t *cola = cola_crear();
    print_test("Encolar el elemento NULL --> VALIDO", (cola_encolar(cola, NULL)));
    print_test("Primero devuelve NULL", cola_ver_primero(cola) == NULL);
    print_test("Cola no esta vacia", cola_esta_vacia(cola) == false);
    print_test("Desencolar devuelve NULL", cola_desencolar(cola) == NULL);
    cola_destruir(cola, eliminar_dato); 
    printf("\n");
}



static void prueba_destruir_dato_con_funcion(void) {  // Pruebas con funcion en destruir
    cola_t *cola = cola_crear();
    void *direc_int_1 = malloc(sizeof(int));
    void *direc_int_2 = malloc(sizeof(int));
    print_test("cola_encolar funciono correctamente 1", cola_encolar(cola, direc_int_1)); 
    print_test("cola_encolar funciono correctamente 2", cola_encolar(cola, direc_int_2));
    print_test("Cola llena al encolar", cola_esta_vacia(cola) == false);
    cola_destruir(cola, eliminar_dato);
    printf("\n");
}


static void prueba_volumen_cola(void){
    cola_t *cola = cola_crear();
    int numero_a_encolar = 1000;
    int numeros[numero_a_encolar];

    // Lleno el vector con numeros para encolar
    for(int i = 0; i < numero_a_encolar; i++){
        numeros[i] = i;
    }

    // Encolo n veces
    for(int i = 0; i < numero_a_encolar; i++){

        bool res_encolar = cola_encolar(cola, &numeros[i]);

        if(!res_encolar){
            print_test("cola_encolar funciona incorrectamente", res_encolar);
        }
       
    }

    // Desencolo n veces
    void* primero;
    void* desencolado;
    for(int i = 0; i < numero_a_encolar; i++){

        primero = cola_ver_primero(cola);
        desencolado = cola_desencolar(cola);
        bool res_desencolar = primero != desencolado;

        if(res_desencolar){
            print_test("cola_desencolar funciona incorrectamente", res_desencolar);
        }
    }
    
    print_test("Cola vacia en volumen (desencolando)", cola_esta_vacia(cola));

    cola_destruir(cola, NULL);
    printf("\n");

}

void pruebas_cola_estudiante() {
    printf("\n");
    printf("-- Pruebas cola vacia --\n");
    prueba_cola_vacia();
    printf("-- Pruebas cola crear y destruir --\n");
    prueba_crear_destruir_cola();
    printf("-- Pruebas encolar y desencolar cola --\n");
    prueba_encolar_desencolar_cola();
    printf("-- Pruebas encolar elemento NULL --\n");
    encolar_elemento_null();
    printf("-- Pruebas destruir cola con funcion --\n");
    prueba_destruir_dato_con_funcion();
    printf("-- Pruebas volumen --\n");
    prueba_volumen_cola();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}
#endif