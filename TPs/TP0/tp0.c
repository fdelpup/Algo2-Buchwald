#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}


int maximo(int vector[], int n) {
    if(n == 0){
        return -1;
    }

    int pos = n-1;
    for(int i = n-1; i >= 0; i--){
        if(vector[i] >= vector[pos]){
            pos = i;
        }
    }
    return pos;
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
    
    for(int i = 0; (i < n1) && (i < n2); i++){

        if(vector1[i] > vector2[i] ){
            return 1;
        }else if(vector1[i] < vector2[i]){
            return -1;
        } 
    }

    if(n1 > n2){
        return 1;
    }else if(n1 < n2){
        return -1;
    }else{
        return 0;
    }
}


void seleccion(int vector[], int n) {

    int tope_vector = n;
    int pos_max = maximo(vector, tope_vector);
    int iteracion_max = tope_vector-1;

    for(int i = tope_vector; i > 0; i--){

        pos_max = maximo(vector, i);
        swap(&(vector[pos_max]), &(vector[iteracion_max]));
        iteracion_max--;
        
    }
}
