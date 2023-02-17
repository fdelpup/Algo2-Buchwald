// Function to swap the the position of two elements

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void swap(void** a, void** b) {
    void* temp = *a;

    *a = *b;

    *b = temp;
}

void heapify(void* arr[], size_t n, size_t i) {
    // Find largest among root, left child and right child

    size_t largest = i;

    size_t left = 2 * i + 1;

    size_t right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])

        largest = left;

    if (right < n && arr[right] > arr[largest])

        largest = right;

    // Swap and continue heapifying if root is not largest

    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        heapify(arr, n, largest);
    }
}

// Main function to do heap sort

void heapSort(void* arr[], size_t n) {
    // Build max heap

    for (size_t i = n; i > 0; i--) {
        printf("%li\n", i);
        heapify(arr, n, i);
    }

    // Heap sort

    for (size_t i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        printf("%li\n", i);
        // Heapify root element to get highest element at root again

        heapify(arr, i, 0);
    }
}

void pruebas_heapsort() {
    int vector[10] = {20, 50, -3, 1, 7, 5, 0, 16, 27, -7};
    int* aux[10];

    for (int i = 0; i < 10; i++) aux[i] = &vector[i];

    int vector_ordenado[10] = {-7, -3, 0, 1, 5, 7, 16, 20, 27, 50};

    heapSort((void**)aux, 10);

    for (int i = 0; i < 10; i++) {
        // if (*aux[i] != vector_ordenado[i]) {
        //     printf("%i\n", i);
        //     error = false;
        //     break;
        // }
        printf("1:%i, 2:%i\n", *aux[i], vector_ordenado[i]);
    }
}

int main() {
    pruebas_heapsort();
    return 0;
}