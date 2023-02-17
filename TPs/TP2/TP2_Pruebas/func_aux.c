#include "extra.h"

int int_cmp(const void* a, const void* b) {
    int* num_a = (int*)a;
    int* num_b = (int*)b;

    if (num_a < num_b) {
        return -1;
    }
    if (num_a > num_b) {
        return 1;
    }
    return 0;
}
int int_cmp_aux(int a, int b) {
    if (a < b) {
        return 1;
    }
    if (a > b) {
        return -1;
    }
    return 0;
}

int strcmpare(const void* dato_1, const void* dato_2) {
    const posts_t* post1 = dato_1;
    const posts_t* post2 = dato_2;

    datos_u_t* dato1 = hash_obtener(post1->hash, pila_ver_tope(post1->pila_aux));
    datos_u_t* dato2 = hash_obtener(post2->hash, pila_ver_tope(post2->pila_aux));

    int* num1 = hash_obtener(dato1->hash, post1->nombre);
    int* num2 = hash_obtener(dato2->hash, post2->nombre);

    int comparacion = int_cmp(num1, num2);
    if (comparacion == 0) {
        return int_cmp_aux(post1->id, post2->id);
    }
    return comparacion;
}

char* strdupp(const char* clave) {
    size_t tam = strlen(clave) + 1;
    char* res = malloc(tam);
    if (!res) {
        return NULL;
    }
    memcpy(res, clave, tam);
    return res;
}