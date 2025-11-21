#ifndef METODOSORDENAMIENTO_H
#define METODOSORDENAMIENTO_H


#include <stdbool.h>
#include <stddef.h>

typedef struct Nodo {
    int valor;
    struct Nodo *sig;
} Nodo;

typedef struct Cola {
    Nodo *frente;
    Nodo *fondo;
    size_t tam;
} Cola;

/* Crea una cola vacía. Devuelve puntero válido o NULL si falla. */
Cola *cola_crear(void);

/* Libera todos los nodos y la cola. */
void cola_destruir(Cola *c);

/* Devuelve true si está vacía. */
bool cola_vacia(const Cola *c);

/* Encola un valor. Devuelve false si falla memoria. */
bool cola_encolar(Cola *c, int valor);

/* Desencola: escribe en *out el valor. Devuelve false si está vacía. */
bool cola_desencolar(Cola *c, int *out);

/* Tamaño actual. */
size_t cola_tamano(const Cola *c);

// Prototipo de la función
int *burbuja(int arr[]);
void quicksort(int arr[], int low, int high);
void swap(int* a, int* b);
int partition(int arr[], int low, int high);


#endif
// // Prototipo de la función
// int *burbuja(int arr[]);
// void quicksort(int arr[], int low, int high);
// void swap(int* a, int* b);
// int partition(int arr[], int low, int high);


// #endif
// int *burbuja(int arr[]) {
//     int aux;
//     int flag = 1;  // Iniciar en 1 para entrar al while
    
//     // Continuar mientras haya intercambios
//     while(flag == 1) {
//         flag = 0;  // Asumir que no habrá intercambios
//         int k = 0;
        
//         // Recorrer el arreglo hasta el centinela
//         while(arr[k + 1] != -1) {  // Verificar k+1 para evitar salirse
//             if(arr[k] > arr[k + 1]) {
//                 // Intercambiar
//                 aux = arr[k];
//                 arr[k] = arr[k + 1];
//                 arr[k + 1] = aux;
//                 flag = 1;  // Hubo intercambio, necesitamos otra pasada
//             }
//             k++;
//         }
//     }
    
//     return arr;
// }

// // Función para intercambiar dos elementos
// void swap(int* a, int* b) {
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }

// // Función de partición que coloca el pivote en su posición correcta
// // y coloca elementos menores a la izquierda y mayores a la derecha
// int partition(int arr[], int low, int high) {
//     // Elegimos el último elemento como pivote
//     int pivot = arr[high];
//     int i = low - 1; // Índice del elemento más pequeño
    
//     for (int j = low; j < high; j++) {
//         // Si el elemento actual es menor o igual al pivote
//         if (arr[j] <= pivot) {
//             i++;
//             swap(&arr[i], &arr[j]);
//         }
//     }
//     swap(&arr[i + 1], &arr[high]);
//     return i + 1;
// }

// // Función principal de Quicksort
// void quicksort(int arr[], int low, int high) {
//     if (low < high) {
//         // pi es el índice de partición
//         int pi = partition(arr, low, high);
        
//         // Ordenar recursivamente los elementos antes y después de la partición
//         quicksort(arr, low, pi - 1);
//         quicksort(arr, pi + 1, high);
//     }
// }