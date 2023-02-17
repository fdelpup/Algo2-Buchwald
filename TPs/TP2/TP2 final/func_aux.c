#include "main.h"

int int_cmp(int a, int b) {
    int num_a = a;
    int num_b = b;

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

int post_cmp(const void* dato_1, const void* dato_2) {
    const posts_t* post1 = dato_1;
    const posts_t* post2 = dato_2;

    datos_u_t* dato = hash_obtener(post1->hash_original, pila_ver_tope(post1->pila_aux));
    int pos_duenio = dato->pos;

    datos_u_t* dato1 = hash_obtener(post2->hash_original, post1->nombre);
    int pos1 = dato1->pos;
    datos_u_t* dato2 = hash_obtener(post2->hash_original, post2->nombre);
    int pos2 = dato2->pos;

    int afinidad1 = post1->cant_usuarios - abs(pos1 - pos_duenio);
    int afinidad2 = post2->cant_usuarios - abs(pos2 - pos_duenio);

    int comparacion = int_cmp(afinidad1, afinidad2);
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