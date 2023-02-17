#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agregado.h"

int main(int argc, char* argv[]){

    if(argc == 1 || argc > 3 || !atoi(argv[1])){ 
        fprintf(stderr, "Error: Cantidad erronea de parametros");
        return -1;
    }

    if(argc == 2){
        fixcol_con_input(atoi(argv[1]));
    }
    if(argc == 3){
        fixcol_con_archivo(atoi(argv[1]), argv[2]);
    }


    return 0;
}