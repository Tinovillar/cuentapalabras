#include "multiset.h"

#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct trie
{
    int cantidad;
    struct trie *siguiente[26];
};

multiset_t *multiset_crear()
{
    multiset_t *t = (multiset_t *)malloc(sizeof(multiset_t));
    t->cantidad = 0;
    for (int i = 0; i < 26; i++)
    {
        t->siguiente[i] = NULL;
    }
    return t;
}

void multiset_insertar(multiset_t *m, char *s)
{
    if (m != NULL)
    {
        int index;
        multiset_t *cursor = m;
        for (int i = 0; s[i] != '\0'; i++)
        {
            index = s[i] - 'a';
            if (cursor->siguiente[index] == NULL)
            {
                cursor->siguiente[index] = multiset_crear();
            }
            cursor = cursor->siguiente[index];
        }
        cursor->cantidad = cursor->cantidad + 1;
    }
}

int multiset_cantidad(multiset_t *m, char *s)
{
    int toReturn = 0;
    if (m != NULL)
    {
        multiset_t *cursor = m;
        int index;
        for (int i = 0; (s[i] != '\0') && (cursor->siguiente[s[i] - 'a'] == NULL); i++)
        {
            index = s[i] - 'a';
            cursor = cursor->siguiente[index];
        }
        toReturn = cursor->cantidad;
    }
    return toReturn;
}

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

void multiset_eliminar(multiset_t **m);
