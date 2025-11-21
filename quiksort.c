#include <stdio.h>

// Función para intercambiar dos elementos
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Función de partición que coloca el pivote en su posición correcta
// y coloca elementos menores a la izquierda y mayores a la derecha
int partition(int arr[], int low, int high) {
    // Elegimos el último elemento como pivote
    int pivot = arr[high];
    int i = low - 1; // Índice del elemento más pequeño
    
    for (int j = low; j < high; j++) {
        // Si el elemento actual es menor o igual al pivote
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Función principal de Quicksort
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        // pi es el índice de partición
        int pi = partition(arr, low, high);
        
        // Ordenar recursivamente los elementos antes y después de la partición
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Función para imprimir el arreglo
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Función principal para demostrar el uso
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Arreglo original:\n");
    printArray(arr, n);
    
    quicksort(arr, 0, n - 1);
    
    printf("\nArreglo ordenado:\n");
    printArray(arr, n);
    
    return 0;
}