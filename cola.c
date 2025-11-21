#include "metodosOrdenamiento.h"
#include <stdlib.h>

Cola *cola_crear(void) {
    Cola *c = (Cola *)malloc(sizeof(Cola));
    if (!c) return NULL;
    c->frente = NULL;
    c->fondo  = NULL;
    c->tam    = 0;
    return c;
}

void cola_destruir(Cola *c) {
    if (!c) return;
    Nodo *act = c->frente;
    while (act) {
        Nodo *sig = act->sig;
        free(act);
        act = sig;
    }
    free(c);
}

bool cola_vacia(const Cola *c) {
    return !c || c->tam == 0;
}

bool cola_encolar(Cola *c, int valor) {
    if (!c) return false;
    Nodo *n = (Nodo *)malloc(sizeof(Nodo));
    if (!n) return false;
    n->valor = valor;
    n->sig = NULL;

    if (c->fondo) {
        c->fondo->sig = n;
    } else {
        c->frente = n;
    }
    c->fondo = n;
    c->tam++;
    return true;
}

bool cola_desencolar(Cola *c, int *out) {
    if (!c || cola_vacia(c)) return false;
    Nodo *n = c->frente;
    if (out) *out = n->valor;
    c->frente = n->sig;
    if (!c->frente) c->fondo = NULL;
    free(n);
    c->tam--;
    return true;
}

size_t cola_tamano(const Cola *c) {
    return c ? c->tam : 0;
}