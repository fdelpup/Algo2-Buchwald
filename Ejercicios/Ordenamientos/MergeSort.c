// Merge sort in C

#include <stdio.h>

// Merge two subarrays L and M into arr
void merge(int vector_inicial[], int inicio, int medio, int final) {

  // Create L ← A[inicio..medio] and M ← A[medio+1..r]
  int parte_inicial = medio - inicio + 1;
  int parte_final = final - medio;

  int vector_1[parte_inicial], vector_2[parte_final];

  for (int i = 0; i < parte_inicial; i++)
    vector_1[i] = vector_inicial[inicio + i];
  for (int j = 0; j < parte_final; j++)
    vector_2[j] = vector_inicial[medio + 1 + j];

  // Maintain current index of sub-vector_inicialays and main vector_inicialay
  int i, j, k;
  i = 0;
  j = 0;
  k = inicio;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < parte_inicial && j < parte_final) {
    if (vector_1[i] <= vector_2[j]) {
      vector_inicial[k] = vector_1[i];
      i++;
    } else {
      vector_inicial[k] = vector_2[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < parte_inicial) {
    vector_inicial[k] = vector_1[i];
    i++;
    k++;
  }

  while (j < parte_final) {
    vector_inicial[k] = vector_2[j];
    j++;
    k++;
  }
}

// Divide the vector_inicialay into two subvector_inicialays, sort them and merge them
void mergeSort(int vector_inicial[], int inicio, int fin) {
  if (inicio < fin) {

    // m is the point where the vector_inicialay is divided into two subvector_inicialays
    int medio = inicio + (fin - inicio) / 2;

    mergeSort(vector_inicial, inicio, medio);
    mergeSort(vector_inicial, medio + 1, fin);

    // Merge the sorted subvector_inicialays
    merge(vector_inicial, inicio, medio, fin);
  }
}

// Print the array
void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

// Driver program
int main() {
  int arr[] = {1, 5, 12, 10, 9, 1};
  int size = sizeof(arr) / sizeof(arr[0]);

  mergeSort(arr, 0, size - 1);

  printf("Sorted array: \n");
  printArray(arr, size);
}