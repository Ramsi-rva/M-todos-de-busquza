#include "algoritmos.h"
#include <stdlib.h>
#include <string.h>

/* Emitir progreso seguro */
static void _prog_emit(progress_cb_t cb, void *ud, double p) {
    if (cb) {
        if (p < 0.0) p = 0.0;
        if (p > 1.0) p = 1.0;
        cb(p, ud);
    }
}

/* ===================== BURBUJA MEJORADO ====================== */
void sort_burbuja_mejorado(int *a, size_t n, progress_cb_t cb, void *ud){
    if (!a || n <= 1){
        _prog_emit(cb, ud, 1.0);
        return;
    }

    for (size_t i = 0; i < n - 1; i++){
        int swapped = 0;
        for (size_t j = 0; j < n - i - 1; j++){
            if (a[j] > a[j+1]){
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
                swapped = 1;
            }
        }
        _prog_emit(cb, ud, (double)i / (n - 1));

        if (!swapped)
            break;
    }

    _prog_emit(cb, ud, 1.0);
}

/* ===================== QUICKSORT ====================== */
static void _qs(int *a, int lo, int hi){
    if (lo >= hi) return;

    int pivot = a[(lo + hi) / 2];
    int i = lo, j = hi;

    while (i <= j){
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;

        if (i <= j){
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            i++;
            j--;
        }
    }

    if (lo < j) _qs(a, lo, j);
    if (i < hi) _qs(a, i, hi);
}

void sort_quicksort(int *a, size_t n, progress_cb_t cb, void *ud){
    if (!a || n <= 1){
        _prog_emit(cb, ud, 1.0);
        return;
    }

    _qs(a, 0, (int)n - 1);
    _prog_emit(cb, ud, 1.0);
}

/* ===================== SHELL SORT ====================== */
void sort_shellsort(int *a, size_t n, progress_cb_t cb, void *ud){
    if (!a || n <= 1){
        _prog_emit(cb, ud, 1.0);
        return;
    }

    for (size_t gap = n/2; gap > 0; gap /= 2){
        for (size_t i = gap; i < n; i++){
            int temp = a[i];
            size_t j = i;

            while (j >= gap && a[j - gap] > temp){
                a[j] = a[j - gap];
                j -= gap;
            }

            a[j] = temp;
        }
    }

    _prog_emit(cb, ud, 1.0);
}

/* ===================== RADIX SORT (base 10) ====================== */
static int _max_val(int *a, size_t n){
    int m = a[0];
    for (size_t i = 1; i < n; i++)
        if (a[i] > m) m = a[i];
    return m;
}

void sort_radix(int *a, size_t n, progress_cb_t cb, void *ud){
    if (!a || n <= 1){
        _prog_emit(cb, ud, 1.0);
        return;
    }

    int maxv = _max_val(a, n);

    int *out = malloc(sizeof(int) * n);
    if (!out) return;

    for (int exp = 1; maxv / exp > 0; exp *= 10){
        int count[10] = {0};

        for (size_t i = 0; i < n; i++)
            count[(a[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--){
            out[count[(a[i] / exp) % 10] - 1] = a[i];
            count[(a[i] / exp) % 10]--;
        }

        memcpy(a, out, n * sizeof(int));
    }

    free(out);

    _prog_emit(cb, ud, 1.0);
}