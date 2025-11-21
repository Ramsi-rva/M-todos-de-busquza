#include "algoritmos.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*---------------------------------------------------
  UTILIDAD DE PROGRESO
---------------------------------------------------*/
static void _prog_emit(progress_cb_t cb, void *ud, double p) {
    if (cb) {
        if (p < 0.0) p = 0.0;
        if (p > 1.0) p = 1.0;
        cb(p, ud);
    }
}

/*---------------------------------------------------
  IMPLEMENTACIÓN DE UNA COLA (para RADIX)
---------------------------------------------------*/
typedef struct Nodo {
    int valor;
    struct Nodo *sig;
} Nodo;

typedef struct Cola {
    Nodo *frente;
    Nodo *final;
} Cola;

static Cola *crearCola() {
    Cola *c = (Cola*)malloc(sizeof(Cola));
    c->frente = c->final = NULL;
    return c;
}

static int estaVacia(Cola *c) {
    return c->frente == NULL;
}

static void encolar(Cola *c, int valor) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->sig = NULL;
    if (c->final == NULL) {
        c->frente = c->final = nuevo;
    } else {
        c->final->sig = nuevo;
        c->final = nuevo;
    }
}

static int desencolar(Cola *c) {
    if (estaVacia(c)) return -1;

    Nodo *tmp = c->frente;
    int v = tmp->valor;
    c->frente = tmp->sig;
    if (c->frente == NULL)
        c->final = NULL;
    free(tmp);
    return v;
}

/*---------------------------------------------------
  BUBBLE SORT MEJORADO
---------------------------------------------------*/
void sort_burbuja_mejorado(int *a, size_t n, progress_cb_t cb, void *ud){
    if (!a || n <= 1) {
        _prog_emit(cb, ud, 1.0);
        return;
    }

    for (size_t i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (size_t j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                swapped = 1;
            }
        }

        _prog_emit(cb, ud, (double)i / (n - 1));

        if (!swapped) break;
    }

    _prog_emit(cb, ud, 1.0);
}

/*---------------------------------------------------
  QUICKSORT
---------------------------------------------------*/
static void _qs(int *a, int lo, int hi) {
    if (lo >= hi) return;

    int pivot = a[hi];
    int i = lo;

    for (int j = lo; j < hi; j++) {
        if (a[j] < pivot) {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            i++;
        }
    }

    int t = a[i];
    a[i] = a[hi];
    a[hi] = t;

    _qs(a, lo, i - 1);
    _qs(a, i + 1, hi);
}

void sort_quicksort(int *a, size_t n, progress_cb_t cb, void *ud){
    _qs(a, 0, n - 1);
    _prog_emit(cb, ud, 1.0);
}

/*---------------------------------------------------
  SHELLSORT
---------------------------------------------------*/
void sort_shellsort(int *a, size_t n, progress_cb_t cb, void *ud){
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i++) {
            int temp = a[i];
            size_t j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
        _prog_emit(cb, ud, 1.0 - ((double)gap / n));
    }
    _prog_emit(cb, ud, 1.0);
}

/*---------------------------------------------------
  RADIX SORT COMO EN TU FOTO
---------------------------------------------------*/

static int encontrarMaximo(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}

static int contarDigitos(int num) {
    int d = 0;
    while (num > 0) {
        num /= 10;
        d++;
    }
    return d;
}

static int obtenerDigito(int num, int pos) {
    while (pos--) num /= 10;
    return num % 10;
}

void sort_radix(int arr[], size_t n, progress_cb_t cb, void *ud) {
    int max = encontrarMaximo(arr, n);
    int digitos = contarDigitos(max);

    Cola *colas[10];
    for (int i = 0; i < 10; i++)
        colas[i] = crearCola();

    for (int d = 0; d < digitos; d++) {

        for (size_t i = 0; i < n; i++) {
            int digito = obtenerDigito(arr[i], d);
            encolar(colas[digito], arr[i]);
        }

        int index = 0;
        for (int i = 0; i < 10; i++) {
            while (!estaVacia(colas[i])) {
                arr[index++] = desencolar(colas[i]);
            }
        }

        _prog_emit(cb, ud, (double)(d + 1) / digitos);
    }

    _prog_emit(cb, ud, 1.0);
}