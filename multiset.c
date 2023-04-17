#include "multiset.h"
#include "listaordenada.h"
#include "cuentapalabras.h"
#include <stdio.h>

struct trie{
    int cantidad;
    struct trie *siguiente[26];
};

// Metodos

multiset_t* multiset_crear() {
    multiset_t* t = (multiset_t*) malloc(sizeof(multiset_t));
    t->cantidad = 0;
    for(int i = 0; i < 26; i++) {
        t->siguiente[i] = NULL;
    }
    return t;
}

void multiset_insertar(multiset_t *m, char *s) {
    if(m != NULL) {
        int index;
        multiset_t *cursor = m;
        for(int i = 0; s[i] != '\0'; i++) {
            index = s[i] - 'a';
            if(cursor->siguiente[index] == NULL) {
                cursor->siguiente[index] = multiset_crear();
            }
            cursor = cursor->siguiente[index];
        }
        cursor->cantidad = cursor->cantidad + 1;
    }
}

int multiset_cantidad(multiset_t *m, char *s) {
    int toReturn = 0;
    if(m != NULL) {
        multiset_t *cursor = m;
        int index;
        for(int i = 0; (s[i] != '\0') && (cursor->siguiente[s[i] - 'a'] == NULL); i++) {
            index = s[i] - 'a';
            cursor = cursor->siguiente[index];
        }
        toReturn = cursor->cantidad;
    }
    return toReturn;
}

lista_t multiset_elementos(multiset_t *m, int (*f)(elemento_t,elemento_t));

void multiset_eliminar(multiset_t **m);
