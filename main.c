#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "algoritmos.h"

void dummy_callback(double p, void *ud) {
    // Puedes imprimir progreso si quieres
}

double medir(void (*f)(int*, size_t, progress_cb_t, void*), int *arr, size_t n) {
    int *copia = malloc(n * sizeof(int));
    memcpy(copia, arr, n * sizeof(int));

    clock_t ini = clock();
    f(copia, n, dummy_callback, NULL);
    clock_t fin = clock();

    free(copia);

    return (double)(fin - ini) * 1000.0 / CLOCKS_PER_SEC;
}

int main() {
    size_t n;
    printf("Cantidad de elementos: ");
    scanf("%zu", &n);

    int *arr = malloc(n * sizeof(int));

    srand(time(NULL));
    for (size_t i = 0; i < n; i++)
        arr[i] = rand() % 100000;

    printf("\nMidiendo tiempos...\n");

    double t1 = medir(sort_burbuja_mejorado, arr, n);
    double t2 = medir(sort_quicksort, arr, n);
    double t3 = medir(sort_shellsort, arr, n);
    double t4 = medir(sort_radix, arr, n);

    printf("\nResultados:\n");
    printf("Burbuja Mejorado: %.2f ms\n", t1);
    printf("Quicksort: %.2f ms\n", t2);
    printf("Shellsort: %.2f ms\n", t3);
    printf("Radix: %.2f ms\n", t4);

    free(arr);

    return 0;
}