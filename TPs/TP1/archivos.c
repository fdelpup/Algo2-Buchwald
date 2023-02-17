
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Pre: Recibe el numero de chars a dividir en fixcol y el archivo a abrir.
// Post: Imprime el texto dado en forma de n columnas pasada por tamanio.

int dividir_lineas_fixcol(int tamanio, FILE* nombre){
    size_t size_linea =  (size_t)(tamanio);   

    int char_por_linea = (int)size_linea;

            
    char *leido = malloc((size_linea * sizeof(char)) + 1);
        if(leido == NULL){
        fprintf(stderr, "Error: malloc fallo");
        return -1;
    }

    while(!feof(nombre)){
        
        if(fgets(leido, char_por_linea + 1 , nombre) != NULL){
            int cantidad = (int)strlen(leido);

            if(leido[0] == '\n'){
                continue;
            }else if(leido[cantidad - 1] == '\n'){
                printf("%s",leido);   
            }else{
                printf("%s\n",leido);
            }
        }
    }
    free(leido);
    return 0;
}


int fixcol_con_archivo(int tamanio, char* nombre_archivo){

    FILE* arch_info = fopen(nombre_archivo, "r");
    if(!arch_info){
        fprintf(stderr, "Error: archivo fuente inaccesible");
        return -1;
    }

    int res = dividir_lineas_fixcol(tamanio, arch_info);
    if(res == -1){
        return -1;
        fprintf(stderr, "Error: dividir_lineas_fixcol fallo");
    }

    fclose(arch_info);
    

    return 0;
}


// Pre: Recibe el numero de chars a dividir en fixcol
// Post: Imprime el texto dado en forma de n columnas pasada por tamanio.

int fixcol_con_input(int tamanio){

    int res = dividir_lineas_fixcol(tamanio, stdin);
    if(res == -1){
        return -1;
        fprintf(stderr, "Error: dividir_lineas_fixcol fallo");
    }

    return 0;
}