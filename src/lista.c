#include "lista.h"

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

lista_t *lista_crear() {
    lista_t *lista = (lista_t *) malloc(sizeof(lista_t));
    lista->cantidad = 0;
    lista->primera = NULL;
    return lista;
}

int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos) {
    if (l == NULL || pos > l->cantidad) {
        return FALSE;
    }
    celda_t *celda_nueva = (celda_t *) malloc(sizeof(celda_t));
    celda_nueva->siguiente = NULL;
    if (celda_nueva == NULL)
        return FALSE;
    celda_nueva->elem = elem;

    celda_t *anterior = NULL;
    celda_t *actual = l->primera;
    unsigned int i = 0;
    while (actual != NULL && i < pos) {
        anterior = actual;
        actual = actual->siguiente;
        i++;
    }
    if (anterior == NULL) { // Se inserta al inicio de la lista
        celda_nueva->siguiente = l->primera;
        l->primera = celda_nueva;
    } else { // Se inserta en medio o al final de la lista
        celda_nueva->siguiente = actual;
        anterior->siguiente = celda_nueva;
    }

    l->cantidad++;
    return TRUE;
}

elemento_t *lista_eliminar(lista_t *l, unsigned int pos) {
    if (l == NULL || pos > l->cantidad) {
        return NULL;
    }

    celda_t *anterior = NULL;
    celda_t *actual = l->primera;
    unsigned int i = 0;
    while (actual != NULL && i < pos) {
        anterior = actual;
        actual = actual->siguiente;
        i++;
    }
    if (anterior == NULL) { // Se elimino el primero
        l->primera = actual->siguiente;
    } else { // Se elimino en el medio o al final
        anterior->siguiente = actual->siguiente;
    }

    /*
     * TODO: devolvemos el puntero del elemento original, o creamos uno nuevo pero con los mismos
     * valores?
    // Creamos un puntero para poder retornar el elemento eliminado
    elemento_t *elem = (elemento_t *)malloc(sizeof(elemento_t));
    if (elem == NULL) {
        return NULL;
    }
    elem->a = actual->elem.a;
    elem->b = actual->elem.b;
    l->cantidad--;
    free(actual);
     */
    l->cantidad--;
    return &actual->elem;
}

elemento_t *lista_elemento(lista_t *l, unsigned int pos) {
    if (l == NULL || pos > l->cantidad) {
        return NULL;
    }

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
    if (l == NULL) {
        return FALSE;
    }

    celda_t *current = l->primera;
    celda_t *cursor = NULL;

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

    return TRUE;
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
    return l->cantidad == 0 ? TRUE : FALSE;
}