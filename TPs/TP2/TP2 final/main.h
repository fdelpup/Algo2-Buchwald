#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datos_u.h"
#include "posts.h"

// Funciones auxiliares
int post_cmp(const void* dato_1, const void* dato_2);
int int_cmp(int a, int b);
int int_cmp_aux(int a, int b);
char* strdupp(const char* clave);

// Funciones dentro de tp2.c
int agregar_usuarios(char* nombre_archivo, hash_t* hash_original, hash_t* hash_usuarios);
const char** agrega_arreglo(const char* arr[], char* nombre_archivo, hash_t* hash_original);
void guardar_datos_usuarios(hash_t* hash_original, datos_u_t** datos, int n, const char* arr[]);

int recibir_parametro(hash_t* hash_original, int id, hash_t* hash_posts, pila_t* pila_aux, hash_t* hash_usuarios, int cant_usuarios);

char* funcion_login(hash_t* hash_original, char** chequeo, size_t n_2, hash_t* hash_usuarios);
char* funcion_logout(char* chequeo, size_t n_2, char* usuario_logueado);
int funcion_publicar(hash_t* hash_original, char** chequeo, size_t n_2, int id, hash_t* hash_posts, pila_t* pila_aux, char* usuario_logueado, int cant_usuarios);
int funcion_siguiente(datos_u_t* datos, char* chequeo, pila_t* pila_aux, char* usuario_logueado);
int funcion_likear(hash_t* hash_posts, char* chequeo, size_t n_2, char* usuario_logueado);
int mostrar_likes(hash_t* hash_posts, char* chequeo, size_t n_2);
bool func_visitar(const char* clave, void* dato, void* extra);

#endif  // MAIN_H
