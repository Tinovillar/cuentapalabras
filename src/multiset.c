#include "multiset.h"

#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
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
    /*
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
     */

    if (m != NULL) {
        int index;
        multiset_t *cursor = m;
        for (int i = 0; s[i] != '\0'; i++) {
            index = s[i] - 'a';
            if (cursor->siguiente[index] == NULL) {
                cursor->siguiente[index] = multiset_crear();
            }
            cursor = cursor->siguiente[index];
        }
        cursor->cantidad = cursor->cantidad + 1;
    }

}

int multiset_cantidad(multiset_t *m, char *s) {
    /*
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
     */

    int toReturn = 0;
    if (m != NULL) {
        multiset_t *cursor = m;
        int index;
        for (int i = 0; (s[i] != '\0') && (cursor->siguiente[s[i] - 'a'] == NULL); i++) {
            index = s[i] - 'a';
            cursor = cursor->siguiente[index];
        }
        toReturn = cursor->cantidad;
    }
    return toReturn;

}


void listar_palabras(multiset_t *trie, lista_t *lista, char *prefijo, int nivel, int index) {
    // Si cantidad es > 0 es porque hay una palabra
    if (trie->cantidad > 0) {
        elemento_t elem;
        elem.a = trie->cantidad;
        // Creamos un nuevo char* que va a teneer el mismo contenido que prefijo y se lo ponemos a elem.
        char *palabra = malloc(strlen(prefijo) * sizeof(char));
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

/*
lista_t* multiset_elementos(multiset_t *m, int (*f)(elemento_t,elemento_t)) {
    lista_t *lista = lista_crear();
    for(int i = 0; i < 26; i++) {
        char palabra[2];
        palabra[0] = i + 'a';
        palabra[1] = '\0';
        if(m->siguiente[i] != NULL && m->siguiente[i]->cantidad != 0) {
            elemento_t *elem = (elemento_t*) malloc(sizeof(elemento_t));
            elem->a = m->siguiente[i]->cantidad;
            elem->b = palabra;
            printf("%s", elem->b);
            lista_insertar(lista, *elem, 0);
            free(elem);
        }
        if(m->siguiente[i] != NULL) {
            //insertar_palabras(m->siguiente[i], lista, palabra);
        }
    }
    comparacion_resultado_t comparar(elemento_t *e1, elemento_t *e2) {
        if (f(*e1, *e2) == 2) {
            return ELEM1_MAYOR_QUE_ELEM2;
        } else if (f(*e1,*e2) == 1) {
            return ELEM1_MENOR_QUE_ELEM2;
        } else {
            return ELEM1_MENOR_QUE_ELEM2;
        }
    }
    mostrar_elementos(lista);
    lista_ordenar(lista, comparar);
    return lista;
}

void insertar_palabras(multiset_t *m, lista_t *lista, char *caracteres) {
    for(int i = 0; i < 26; i++) {
        char palabra[strlen(caracteres) + 1];
        strcpy(palabra, caracteres);
        palabra[strlen(caracteres)] = i + 'a';
        palabra[strlen(caracteres) + 1] = '\0';
        printf("%s\n", palabra);
        if(m->cantidad != 0) {
            elemento_t *elem = (elemento_t*) malloc(sizeof(elemento_t));
            elem->a = m->cantidad;
            elem->b = palabra;
            lista_insertar(lista, *elem, 0);
            free(elem);
        }
        if(m->siguiente[i] != NULL) {
            insertar_palabras(m->siguiente[i], lista, palabra);
        }
    }
}
*/

void multiset_eliminar(multiset_t **m) {

}