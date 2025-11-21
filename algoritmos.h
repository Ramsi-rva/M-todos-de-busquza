#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <stddef.h>

/*Callback de progreso (0.0 - 1.0)*/
typedef void (*progress_cb_t)(double progress, void *user_data);

void sort_burbuja_mejorado(int *a, size_t n, progress_cb_t cb, void *ud);
void sort_quicksort(int *a, size_t n, progress_cb_t cb, void *ud);
void sort_shellsort(int *a, size_t n, progress_cb_t cb, void *ud);
void sort_radix(int *a, size_t n, progress_cb_t cb, void *ud);

#endif