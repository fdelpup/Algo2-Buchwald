#ifndef AGREGADO_H
#define AGREGADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ******************************************************************
 *                          PRIMITIVAS 
 * *****************************************************************/


int fixcol_con_input(int tamanio);

int fixcol_con_archivo(int tamanio, char* nombre_archivo);

int dividir_lineas_fixcol(int tamanio, FILE* nombre);

#endif // AGREGADO_H

