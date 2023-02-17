#include <stdio.h>
#include <stdlib.h>

int input(char *s,int length);

int main()
{
    char *linea;
    size_t bufsize = 1;
    size_t characters;

    linea = malloc(bufsize * sizeof(char));
    if( linea == NULL){
        perror("Unable to allocate linea");
        exit(1);
    }

    printf("Type something: ");
    characters = getline(&linea,&bufsize,stdin);
    printf("%zu characters were read.\n",characters);
    printf("You typed: '%s'\n",linea);

    return(0);
}