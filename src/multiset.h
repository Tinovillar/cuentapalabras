#ifndef MULTISET_H
#define MULTISET_H

#define TAMANIO_ALFABETO 26

#include "listaordenada.h"

struct trie;
typedef struct trie multiset_t;

typedef struct nodo {
    char *palabra;
    struct nodo *siguiente;
} nodo_t;

multiset_t *multiset_crear();

void multiset_insertar(multiset_t *m, char *s);

int multiset_cantidad(multiset_t *m, char *s);

lista_t *multiset_elementos(multiset_t *m, int (*f)(elemento_t, elemento_t));

void multiset_eliminar(multiset_t **m);

#endif
