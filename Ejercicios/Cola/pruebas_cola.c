#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>


static void pruebas_1(void){
    cola_t *cola = cola_crear();
    print_test("Cola creada vacia .. ", (cola_esta_vacia(cola) == true));
    cola_destruir(cola);
    //printf("\n");
}

static void pruebas_2(void){
    cola_t *cola = cola_crear();
    int direc_int_1 = 1;
    int direc_int_2 = 2;
    cola_encolar(cola, &direc_int_1);
    print_test("Cola encolada bien 1 .. ", (cola_ver_primero(cola) == &direc_int_1));
    cola_encolar(cola, &direc_int_2);
    cola_destruir(cola);

}

static void pruebas_3(void){
    cola_t *cola = cola_crear();
    int direc_int_1 = 1;
    int direc_int_2 = 2;
    cola_encolar(cola, &direc_int_1);
    cola_encolar(cola, &direc_int_2);
    cola_desencolar(cola);
    cola_desencolar(cola);
    print_test("Cola vacia al desencolarla .. ", cola_esta_vacia(cola));
    cola_destruir(cola);
    printf("\n");
}




void pruebas_cola_estudiante() {
    pruebas_1();
    pruebas_2();
    pruebas_3();
}


int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}