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
    if (m == NULL) return;

    unsigned int length = strlen(s);
    multiset_t *current = m;
    for (int i = 0; i < length; i++) {
        int index = s[i] - 'a';
        if (!current->siguiente[index]) {
            current->siguiente[index] = multiset_crear();
        }
        current = current->siguiente[index];
    }
    current->cantidad++;
}

int multiset_cantidad(multiset_t *m, char *s) {
    if (m == NULL) return 0;

    unsigned int length = strlen(s);
    multiset_t *current = m;
    for (int i = 0; i < length; i++) {
        int index = s[i] - 'a';
        if (current->siguiente[index] == NULL) {
            return 0;
        }
        current = current->siguiente[index];
    }
    return current->cantidad;
}

void listar_palabras(multiset_t *trie, lista_t *lista, char *prefijo, int nivel, int index) {
    if (trie->cantidad > 0) {
        elemento_t elem;
        elem.a = trie->cantidad;
        char *palabra = malloc((strlen(prefijo) + 1) * sizeof(char));
        strcpy(palabra, prefijo);
        elem.b = palabra;
        lista_insertar(lista, elem, index);
    }
    for (int i = 0; i < TAMANIO_ALFABETO; i++) {
        if (trie->siguiente[i] != NULL) {
            prefijo[nivel] = i + 'a';
            prefijo[nivel + 1] = '\0';
            listar_palabras(trie->siguiente[i], lista, prefijo, nivel + 1, index);
        }
    }
}

lista_t *multiset_elementos(multiset_t *m, int (*f)(elemento_t, elemento_t)) {
    lista_t *lista = lista_crear();
    char prefijo[100] = "\0";
    listar_palabras(m, lista, prefijo, 0, 0);
    lista_ordenar(lista, (comparacion_resultado_t (*)(elemento_t *, elemento_t *)) f);
    return lista;
}

void multiset_eliminar(multiset_t **m) {
    if (*m == NULL) return;
    for (int i = 0; i < TAMANIO_ALFABETO; i++) {
        multiset_eliminar(&((*m)->siguiente[i]));
    }
    free(*m);
    *m = NULL;
}