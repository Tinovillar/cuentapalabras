#include "listaordenada.h"

#include "utils.h"

#include <stdlib.h>

typedef struct celda {
    elemento_t elem;
    struct celda *siguiente;
} celda_t;

typedef struct celda celda_t;

struct lista {
    celda_t *primera;
    int cantidad;
};

// Implementacion de metodos

lista_t *lista_crear() {
    lista_t *lista = (lista_t *) malloc(sizeof(lista_t));
    lista->cantidad = 0;
    lista->primera = NULL;
    return lista;
}

int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos) {
    if (l == NULL)
        return FALSE;

    if (pos < 0 || pos > l->cantidad)
        return FALSE;

    celda_t *celda_nueva = (celda_t *) malloc(sizeof(celda_t));
    celda_nueva->siguiente = NULL;
    if (celda_nueva == NULL)
        return FALSE;
    celda_nueva->elem = elem;

    celda_t *current = l->primera;
    celda_t *prev = NULL;
    unsigned int i = 0;

    while (current != NULL && i < pos) {
        prev = current;
        current = current->siguiente;
        i++;
    }
    if (prev == NULL) { // Se inserta al inicio de la lista
        celda_nueva->siguiente = l->primera;
        l->primera = celda_nueva;
    } else { // Se inserta en medio o al final de la lista
        celda_nueva->siguiente = current;
        prev->siguiente = celda_nueva;
    }

    l->cantidad++;
    return TRUE;
}

elemento_t *lista_eliminar(lista_t *l, unsigned int pos) {
    if (l == NULL || pos >= l->cantidad) {
        return NULL;  // invalid list or position
    }

    celda_t *anterior = NULL;
    celda_t *actual = l->primera;
    for (unsigned int i = 0; i < pos; i++) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (anterior == NULL) {
        l->primera = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    elemento_t *elem = (elemento_t *)malloc(sizeof(elemento_t));
    if (elem == NULL) {
        return NULL;  // memory allocation failed
    }
    *elem = actual->elem;
    free(actual);

    l->cantidad--;
    return elem;
}

elemento_t *lista_elemento(lista_t *l, unsigned int pos) {
    if (l == NULL)
        return NULL;

    if (pos > l->cantidad)
        return NULL;

    celda_t *current = l->primera;
    unsigned int i = 0;

    while (current != NULL && i < pos) {
        current = current->siguiente;
        i++;
    }

    return &(current->elem);
}

void intercambiar(elemento_t *e1, elemento_t *e2) {
    elemento_t aux = *e1;
    e1->a = e2->a;
    e1->b = e2->b;
    e2->a = aux.a;
    e2->b = aux.b;
}

int lista_ordenar(lista_t *l, funcion_comparacion_t comparar) {
    celda_t *current = l->primera;
    celda_t *cursor;
    int toReturn = FALSE;
    if (l->cantidad > 0) {
        while (current->siguiente != NULL) {
            cursor = current;
            while (cursor->siguiente != NULL) {
                cursor = cursor->siguiente;
                if (comparar(&current->elem, &cursor->elem) == ELEM1_MAYOR_QUE_ELEM2) {
                    intercambiar(&current->elem, &cursor->elem);
                }
            }
            current = current->siguiente;
        }
        toReturn = TRUE;
    }
    return toReturn;
}

unsigned int lista_cantidad(lista_t *l) {
    if (l == NULL)
        return 0;
    return l->cantidad;
}

int lista_vacia(lista_t lista) {
    lista_t *l = &lista;
    if (l == NULL)
        return FALSE;
    int vacia = l->cantidad == 0 ? TRUE : FALSE;
    return vacia;
}