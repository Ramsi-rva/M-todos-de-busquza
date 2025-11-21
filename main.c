#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "algoritmos.h"

// ----------------------------------------------------------
// Callback VACÍO porque no usaremos barras de progreso aquí
// ----------------------------------------------------------
void progreso(double p, void *ud) {
    // Se podría imprimir avance, pero lo dejamos vacío
}

// ----------------------------------------------------------
// Función para imprimir un arreglo
// ----------------------------------------------------------
void imprimirArreglo(int *a, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// ----------------------------------------------------------
// Medir tiempo
// ----------------------------------------------------------
double medir_tiempo(void (*fn)(int*, size_t, progress_cb_t, void*),
                    int *arr, size_t n)
{
    clock_t inicio = clock();
    fn(arr, n, progreso, NULL);
    clock_t fin = clock();

    return (double)(fin - inicio) / CLOCKS_PER_SEC;
}

int main() {
    size_t n;
    printf("Tamaño del arreglo: ");
    scanf("%zu", &n);

    int *original = malloc(n * sizeof(int));
    if (!original) return 1;

    // Llenar arreglo aleatorio
    srand(time(NULL));
    for (size_t i = 0; i < n; i++)
        original[i] = rand() % 1000000;

    printf("\nArreglo original:\n");
    imprimirArreglo(original, n);

    // Crear copias
    int *A = malloc(n * sizeof(int));
    int *B = malloc(n * sizeof(int));
    int *C = malloc(n * sizeof(int));
    int *D = malloc(n * sizeof(int));

    memcpy(A, original, n * sizeof(int));
    memcpy(B, original, n * sizeof(int));
    memcpy(C, original, n * sizeof(int));
    memcpy(D, original, n * sizeof(int));

    // ------------------------------
    // EJECUCIÓN Y MEDICIÓN DE TIEMPO
    // ------------------------------
    double t_bubble  = medir_tiempo(sort_burbuja_mejorado, A, n);
    double t_quick   = medir_tiempo(sort_quicksort, B, n);
    double t_shell   = medir_tiempo(sort_shellsort, C, n);
    double t_radix   = medir_tiempo(sort_radix, D, n);

    // ------------------------------
    // TABLA ORDENADA (Radix)
    // ------------------------------
    printf("\nTabla ordenada (RadixSort):\n");
    imprimirArreglo(D, n);

    // ------------------------------
    // TABLA COMPARATIVA
    // ------------------------------
    printf("\n================ COMPARATIVA DE TIEMPOS ================\n");
    printf("Método              Tiempo (segundos)\n");
    printf("---------------------------------------------------------\n");
    printf("Burbuja mejorado     %f\n", t_bubble);
    printf("QuickSort            %f\n", t_quick);
    printf("ShellSort            %f\n", t_shell);
    printf("RadixSort            %f\n", t_radix);
    printf("=========================================================\n");

    // Encontrar el más rápido
    double min = t_bubble;
    const char *metodo = "Burbuja mejorado";

    if (t_quick < min) { min = t_quick; metodo = "QuickSort"; }
    if (t_shell < min) { min = t_shell; metodo = "ShellSort"; }
    if (t_radix < min) { min = t_radix; metodo = "RadixSort"; }

    printf("\nMétodo más rápido: \033[1;32m%s\033[0m\n\n", metodo);

    free(original);
    free(A); free(B); free(C); free(D);

    return 0;
}