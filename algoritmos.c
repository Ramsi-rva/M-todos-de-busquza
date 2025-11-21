#include "algoritmos.h"
#include <string.h>
#include <stdlib.h>

//--------------- Utilidad progreso ---------------
static void _prog_emit(progress_cb_t cb, void *ud, double p) {
    if (cb) {
        if (p < 0.0) p = 0.0;
        if (p > 1.0) p = 1.0;
        cb(p, ud);
    }
}

/*--------------- Bubble Mejorado ---------------*/
void sort_burbuja_mejorado(int *a, size_t n, progress_cb_t cb, void *ud){
    if (!a || n <= 1) {
        _prog_emit(cb, ud, 1.0);
        return;
    }

    size_t total_pass = n - 1;
}