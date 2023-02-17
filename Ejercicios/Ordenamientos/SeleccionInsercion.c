// Seleccion
void ordenar_seleccion(int vector[MAX], int tope){
    int aux;
    int minimo;

    for(int i = 0; i < tope - 1; i++){
        minimo = i;
        for(int j = i+1; j < tope; j++){
            if (vector[minimo] > vector[j]){
                minimo = j;
            }
        }
        aux = vector[minimo];
        vector[minimo] = vector[i];
        vector[i] = aux;
    }
}

// Insercion
void ordenar_insercion(int vector[MAX], int tope){
    int aux;
    int j;

    for(int i = 1; i < tope; i++){
        j = i;
        aux = vector[i];

        while (j > 0 && aux < vector[j-1]){
            vector[j] = vector[j-1];
            j--;
        }
        vector[j] = aux;
    }
}