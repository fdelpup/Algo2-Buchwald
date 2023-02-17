#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>



// Chequea que al crear una pila esta arranca vacia.

static void prueba_pila_vacia(void) {
    pila_t *pila = pila_crear(); 
    print_test("Pila esta vacia ", pila_esta_vacia(pila));
    pila_destruir(pila);
    printf("\n");
}


// Se pueda crear y destruir correctamente la estructura.

static void prueba_crear_destruir_pila(void) {
    pila_t *pila = pila_crear(); 
    print_test("Crear pila vacia ", pila != NULL); 
    pila_destruir(pila);
    // PRUEBA DE DESTRUCCION DE PILA CON VALGRIND "OK"
    printf("\n");
}

// Se puedan apilar elementos, que al desapilarlos se mantenga el invariante de pila.

static void prueba_apilar_desapilar_pila(void){
    pila_t *pila = pila_crear();
    int direc_int_1 = 1;
    int direc_int_2 = 2;
    int direc_int_3 = 3;
    print_test("Apilar funciona correctamente en 1" , pila_apilar(pila, &direc_int_1));
    print_test("Invariante de pila 1 (Apilando)", (pila_ver_tope(pila) == &direc_int_1));
    print_test("Apilar funciona correctamente en 2", pila_apilar(pila, &direc_int_2));
    print_test("Invariante de pila 2 (Apilando)", (pila_ver_tope(pila) == &direc_int_2));
    print_test("Apilar funciona correctamente en 3" ,pila_apilar(pila, &direc_int_3));

    print_test("Invariante de pila 3 (Apilando)", (pila_ver_tope(pila) == &direc_int_3));
    print_test("Pila no esta vacia (apilar)", (pila_esta_vacia(pila) == false));

    print_test("Valor del tope correcto al desapilar 3", pila_desapilar(pila) == &direc_int_3);
    print_test("Invariante de pila 2 (Desapilando)", (pila_ver_tope(pila) == &direc_int_2));
    print_test("Valor del tope correcto al desapilar 2", pila_desapilar(pila) == &direc_int_2);
    print_test("Invariante de pila 1 (Desapilando)", (pila_ver_tope(pila) == &direc_int_1));
    print_test("Valor del tope correcto al desapilar 1", pila_desapilar(pila) == &direc_int_1);
    print_test("Pila esta vacia (desapilar)", (pila_esta_vacia(pila) == true));

    pila_destruir(pila);
    printf("\n");
}


static void prueba_volumen(void){
    pila_t *pila = pila_crear();
    int numero_a_apilar = 1000;
    int numeros[numero_a_apilar];
    bool apilo = true;
    bool desapilo = true;

    for(int i = 0; i < numero_a_apilar; i++){
        numeros[i] = i;
    }

    for(int i = 0; i < numero_a_apilar; i++){
        if(!pila_apilar(pila, &numeros[i])){
            print_test("pila_apilar funciona incorrectamente", true);
        }
        if(pila_ver_tope(pila) != &numeros[i]){
            apilo = false;
            break;
        }
    }
    // Al ser igual el tope no deberia entrar aca entonces se prueba el invariante de pila y no corta la funcion
    print_test("Invariante de pila en volumen (apilando)", apilo);
    
    for(int i = 1; i <= numero_a_apilar; i++){
        if(pila_ver_tope(pila) != pila_desapilar(pila)){
            print_test("pila_desapilar funciona incorrectamente", true);
        }
        if(pila_ver_tope(pila) == &numeros[numero_a_apilar - i]){
            desapilo = false;
        }
    }
    // Al ser igual el tope no deberia entrar aca entonces se prueba el invariante de pila y no corta la funcion
    print_test("Pila vacia en volumen (desapilando)", (pila_esta_vacia(pila) == true));
    print_test("Invariante de pila en volumen (apilando)", desapilo);

    pila_destruir(pila);
    printf("\n");

}


// El apilamiento del elemento NULL es válido.

static void apilamiento_null(void){
    pila_t *pila = pila_crear();
    print_test("Apilamiento de NULL --> VALIDO", (pila_apilar(pila, NULL) == true));
    pila_destruir(pila);
    printf("\n");
}


// Condición de borde: las acciones de desapilar y ver_tope en una pila recién creada son inválidas.

static void condicion_borde_desapilar_en_nueva(void){
    pila_t *pila = pila_crear();
    print_test("Pila vacia no se desapila", (pila_desapilar(pila) == NULL));
    print_test("Pila vacia no se ve el tope", (pila_ver_tope(pila) == NULL));
    pila_destruir(pila);
    printf("\n");
}


// Condición de borde: la acción de esta_vacía en una pila recién creada es verdadero.

static void condicion_borde_esta_vacia_verdadera(void){
    pila_t *pila = pila_crear();
    print_test("Pila recien creada --> esta_vacia es verdadero", (pila_esta_vacia(pila) == true));
    pila_destruir(pila);
    printf("\n");
}


//Condición de borde: las acciones de desapilar y ver_tope en una pila a la que se le apiló y desapiló hasta estar vacía son inválidas.

static void condicion_borde_desapilar_tope_invalida(void){
    pila_t *pila = pila_crear();

    int direc_int_1 = 1;
    int direc_int_2 = 2;
    int direc_int_3 = 3;
    pila_apilar(pila, &direc_int_1);
    pila_apilar(pila, &direc_int_2);
    pila_apilar(pila, &direc_int_3);

    pila_desapilar(pila);
    pila_desapilar(pila);
    pila_desapilar(pila);

    print_test("Pila vacia no se vale desapilar", (pila_desapilar(pila) == NULL));
    print_test("Pila vacia no se vale pedir el tope", (pila_ver_tope(pila) == NULL));
    pila_destruir(pila);
    printf("\n");
}


//Condición de borde: comprobar que al desapilar hasta que está vacía hace que la pila se comporte como recién creada.

static void condicion_borde_desapilar_recien_creada(void){
    pila_t *pila = pila_crear();

    int direc_int_1 = 1;
    int direc_int_2 = 2;
    int direc_int_3 = 3;
    pila_apilar(pila, &direc_int_1);
    pila_apilar(pila, &direc_int_2);
    pila_apilar(pila, &direc_int_3);

    pila_desapilar(pila);
    pila_desapilar(pila);
    pila_desapilar(pila);

    print_test("Pila desapilada se comporta como recien creada (tope = NULL)", (pila_ver_tope(pila) == NULL));
    print_test("Pila desapilada se comporta como recien creada (pila esta vacia)", (pila_esta_vacia(pila) == true));

    pila_destruir(pila);
    printf("\n");
}



void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_crear_destruir_pila();
    prueba_apilar_desapilar_pila();
    prueba_volumen();
    apilamiento_null();
    condicion_borde_desapilar_en_nueva();
    condicion_borde_esta_vacia_verdadera();
    condicion_borde_desapilar_tope_invalida();
    condicion_borde_desapilar_recien_creada();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
