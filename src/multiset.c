#include "multiset.h"

#include "utils.h"

#include <stdlib.h>
#include <string.h>

struct trie {
    int cantidad;
    struct trie *siguiente[26];
};

multiset_t *multiset_crear() {
    multiset_t *t = (multiset_t *) malloc(sizeof(multiset_t));
    t->cantidad = 0;
    for (int i = 0; i < TAMANIO_ALFABETO; i++) {
        t->siguiente[i] = NULL;
    }
    return t;
}

void multiset_insertar(multiset_t *m, char *s) {
    if (m == NULL || s == NULL) return;

    unsigned int len = strlen(s);
    multiset_t *nodo_actual = m;

    for (int i = 0; i < len; i++) {
        int index = (int)(s[i] - 'a');

        if (nodo_actual->siguiente[index] == NULL) {
            nodo_actual->siguiente[index] = malloc(sizeof(multiset_t));
            nodo_actual->siguiente[index]->cantidad = 0;
            memset(nodo_actual->siguiente[index]->siguiente, 0, sizeof(nodo_actual->siguiente[index]->siguiente));
        }

        nodo_actual = nodo_actual->siguiente[index];
    }

    nodo_actual->cantidad++;
}

int multiset_cantidad(multiset_t *m, char *s) {
    if (m == NULL || s == NULL) return 0;

    unsigned int length = strlen(s);
    multiset_t *current = m;
    for (int i = 0; i < length; i++) {
        int index = (int)(s[i] - 'a');
        if (current->siguiente[index] == NULL) {
            return 0;
        }
        current = current->siguiente[index];
    }
    return current->cantidad;
}

void multiset_elementos_aux(multiset_t *m, lista_t* elementos, char *prefijo) {
    if (m == NULL || elementos == NULL) {
        return;
    }

    // Si cantidad > 0 es porque hay una palabra, la agregamos a la lista.
    if (m->cantidad > 0) {
        elemento_t *elemento = (elemento_t *)malloc(sizeof(elemento_t));
        if (elemento == NULL) {
            return;
        }

        elemento->a = m->cantidad;
        elemento->b = strdup(prefijo);
        // Fallo el prefijo.
        if (elemento->b == NULL) {
            free(elemento);
            return;
        }

        // Insertamos al final usaando la cantidad actual de la lista.
        unsigned int pos = lista_cantidad(elementos);
        lista_insertar(elementos, *elemento, pos);
    }

    // Recorremos recursivamente todos los hijos
    for (int i = 0; i < TAMANIO_ALFABETO; i++) {
        if (m->siguiente[i] != NULL) {
            char *prefijo_nuevo = (char *)malloc(strlen(prefijo) + 2);
            if (prefijo_nuevo == NULL) {
                return;
            }
            strcpy(prefijo_nuevo, prefijo);
            prefijo_nuevo[strlen(prefijo)] = 'a' + i;
            prefijo_nuevo[strlen(prefijo) + 1] = '\0';

            // Recursion con el prefijo nuevo
            multiset_elementos_aux(m->siguiente[i], elementos, prefijo_nuevo);
            free(prefijo_nuevo);
        }
    }
}

lista_t multiset_elementos(multiset_t *m, int (*f)(elemento_t, elemento_t)) {
    lista_t* lista = lista_crear();
    if (m == NULL)
        return *lista;

    multiset_elementos_aux(m, lista, "");
    lista_ordenar(lista, (comparacion_resultado_t (*)(elemento_t *, elemento_t *)) f);

    return *lista;
}

void multiset_eliminar(multiset_t **m) {
    if (m == NULL || *m == NULL) return;

    for (int i = 0; i < TAMANIO_ALFABETO; i++) {
        multiset_eliminar(&((*m)->siguiente[i]));
    }
    free(*m);
    *m = NULL;
}