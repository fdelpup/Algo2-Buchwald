#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.

#include "abb.h"
#include "testing.h"

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/
// void swap(char* x, char* y) {
//     char auxiliar = *x;
//     *x = *y;
//     *y = auxiliar;
// }
// void swap_st(size_t* x, size_t* y) {
//     size_t auxiliar = *x;
//     *x = *y;
//     *y = auxiliar;
// }
// void swap_int(unsigned int* x, unsigned int* y) {
//     unsigned int auxiliar = *x;
//     *x = *y;
//     *y = auxiliar;
// }

static void prueba_crear_abb_vacio() {
    abb_t *abb = abb_crear(strcmp, NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}

// static void prueba_iterar_abb_vacio() {
//     abb_t* abb = abb_crear(strcmp, NULL);
//     abb_iter_t* iter = abb_iter_in_crear(abb);
//     print_test("Prueba abb iter crear iterador abb vacio", iter);
//     print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
//     print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

//     abb_iter_in_destruir(iter);
//     abb_destruir(abb);
// }

static void prueba_abb_insertar() {
    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    if (strcmp(clave2, clave3) > 0) {
        printf("mayor clave2\n");
    }
    if (strcmp(clave1, clave3) > 0) {
        printf("mayor clave1\n");
    }
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    //    printf("%p\n", abb_obtener(abb, clave5));
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
}

static void prueba_abb_reemplazar() {
    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir() {
    abb_t *abb = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}

static void prueba_abb_borrar() {
    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_clave_vacia() {
    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_valor_null() {
    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

// int intcmp(const char* a, const char* b) {
//     int nuevo_a = atoi(a);
//     int nuevo_b = atoi(b);

//     if (nuevo_a < nuevo_b) return -1;
//     if (nuevo_a > nuevo_b) return 1;
//     return 0;
// }

// static ssize_t buscar(const char* clave, char* claves[], size_t largo) {
//     for (size_t i = 0; i < largo; i++) {
//         if (strcmp(clave, claves[i]) == 0) return (ssize_t)i;
//     }
//     return -1;
// }

// static void prueba_abb_iterar() {
//     abb_t* abb = abb_crear(strcmp, NULL);

//     char* claves[] = {"perro", "gato", "vaca"};
//     char* valores[] = {"guau", "miau", "mu"};

//     /* Inserta 3 valores */
//     print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
//     print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
//     print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

//     // Prueba de iteración sobre las claves almacenadas.
//     abb_iter_t* iter = abb_iter_in_crear(abb);
//     const char* clave;
//     ssize_t indice;

//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

//     /* Primer valor */
//     clave = abb_iter_in_ver_actual(iter);
//     indice = buscar(clave, claves, sizeof(claves) / sizeof(char*));
//     print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
//     print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
//     print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

//     /* Segundo valor */
//     clave = abb_iter_in_ver_actual(iter);
//     indice = buscar(clave, claves, sizeof(claves) / sizeof(char*));
//     print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
//     print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
//     print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

//     /* Tercer valor */
//     clave = abb_iter_in_ver_actual(iter);
//     indice = buscar(clave, claves, sizeof(claves) / sizeof(char*));
//     print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
//     print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
//     /* Se anula esta prueba por diferencias de criterios */
//     abb_iter_in_avanzar(iter);
//     print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

//     /* Vuelve a tratar de avanzar, por las dudas */
//     print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
//     print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

//     abb_iter_in_destruir(iter);
//     abb_destruir(abb);
// }

// static void prueba_abb_iterar_volumen(size_t largo) {
//     abb_t* abb = abb_crear(intcmp, NULL);

//     const size_t largo_clave = 10;
//     char(*claves)[largo_clave] = malloc(largo * largo_clave);

//     size_t valores[largo];
//     /* Inserta 'largo' parejas en el abb */
//     bool ok = true;
//     for (size_t i = 0; i < largo; i++) {
//         // printf("%lu--",i );printf("%lu\n", ((i+(size_t)rand())%largo));
//         sprintf(claves[i], "%lu", (i + (size_t)rand()) % largo);
//         valores[i] = i;
//         ok = abb_guardar(abb, claves[i], &valores[i]);
//         if (!ok) break;
//     }

//     // Prueba de iteración sobre las claves almacenadas.
//     abb_iter_t* iter = abb_iter_in_crear(abb);
//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));
//     ok = true;
//     unsigned k = 0;
//     const char* clave;
//     size_t* valor;

//     while (!abb_iter_in_al_final(iter)) {
//         if (abb_iter_in_al_final(iter)) {
//             ok = false;
//             break;
//         }
//         clave = abb_iter_in_ver_actual(iter);
//         if (clave == NULL) {
//             ok = false;
//             break;
//         }
//         valor = abb_obtener(abb, clave);
//         if (valor == NULL) {
//             ok = false;
//             break;
//         }
//         *valor = largo;
//         abb_iter_in_avanzar(iter);
//         k++;
//     }
//     abb_iter_in_avanzar(iter);
//     print_test("Prueba abb iteración en volumen", ok);
//     print_test("Prueba abb iteración en volumen, recorrio todo el largo", k == abb_cantidad(abb));
//     print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

//     free(claves);
//     abb_iter_in_destruir(iter);
//     abb_destruir(abb);
// }

// bool visitar(const char* clave, void* valor, void* extra) {
//     if (atoi(valor) == 0) return false;
//     printf("clave: %s - valor : %d \n", clave, atoi(valor));
//     return true;
// }

// static void prueba_iter_in_order() {
//     abb_t* abb = abb_crear(intcmp, NULL);
//     print_test("Prueba abb, se creo el arbol correctamente", abb);

//     const size_t largo_clave = 10;
//     char(*claves)[largo_clave] = malloc(10 * largo_clave);
//     size_t numeros[10];

//     for (size_t i = 0; i < 10; i++) {
//         sprintf(claves[i], "%lu", i);
//         numeros[i] = i;
//     }

//     swap(claves[3], claves[9]);
//     swap_st(&numeros[3], &numeros[9]);

//     swap(claves[1], claves[5]);
//     swap_st(&numeros[1], &numeros[5]);

//     swap(claves[8], claves[0]);
//     swap_st(&numeros[8], &numeros[0]);

//     swap(claves[4], claves[2]);
//     swap_st(&numeros[4], &numeros[2]);

//     for (int i = 0; i < 10; i++) {
//         abb_guardar(abb, claves[i], &numeros[i]);
//     }
//     print_test("Prueba abb se guardaron todos los elementos", 10 == (int)abb_cantidad(abb));
//     free(claves);
//     abb_in_order(abb, visitar, NULL);
//     abb_destruir(abb);
// }

// void prueba_lok() {
//     abb_t* abb = abb_crear(intcmp, NULL);
//     print_test("Prueba abb, se creo el arbol correctamente", abb);

//     char* abb_valores[5] = {"5", "ad-eave.ded", "6", "8", "9"};

//     abb_guardar(abb, "5", abb_valores[0]);
//     abb_guardar(abb, "3", abb_valores[1]);
//     abb_guardar(abb, "6", abb_valores[2]);
//     abb_guardar(abb, "8", abb_valores[3]);
//     abb_guardar(abb, "9", abb_valores[4]);

//     abb_in_order(abb, visitar, NULL);
//     abb_destruir(abb);
// }
// void prueba_lok_2() {
//     abb_t* abb = abb_crear(intcmp, NULL);
//     print_test("Prueba abb, se creo el arbol correctamente", abb);

//     abb_guardar(abb, "5", "5");
//     abb_guardar(abb, "3", "3");
//     abb_guardar(abb, "6", "6");
//     abb_guardar(abb, "8", "8");
//     abb_guardar(abb, "9", "9");

//     abb_in_order(abb, visitar, NULL);
//     abb_destruir(abb);
// }

void pruebas_abb_alumno() {
    /* Ejecuta todas las pruebas unitarias. */

    prueba_crear_abb_vacio();
    // prueba_iterar_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_borrar();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
    //     prueba_abb_iterar();
    //     prueba_abb_iterar_volumen(5000);
    //     prueba_iter_in_order();
    //     prueba_lok();
    //     prueba_lok_2();
}

/*
void pruebas_volumen_catedra(size_t largo){
    prueba_abb_volumen(largo, false);
}
*/
/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_abb_alumno();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}
#endif