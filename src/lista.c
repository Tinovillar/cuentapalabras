#include "lista.h"

#include "utils.h"

#include <stdlib.h>
#include <string.h>

struct celda {
    elemento_t *elem;
    struct celda *siguiente;
};

lista_t *lista_crear() {
    lista_t *lista = (lista_t *) malloc(sizeof(lista_t));
    if (lista != NULL) {
        lista->primera = NULL;
        lista->cantidad = 0;
    }
    return lista;
}

int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos) {
    if (l == NULL || pos > l->cantidad) {
        return FALSE;
    }
    celda_t *nueva_celda = (celda_t *)malloc(sizeof(celda_t));
    // Fallo la allocacion
    if (nueva_celda == NULL)
        return FALSE;

    nueva_celda->elem = (elemento_t *)malloc(sizeof(elemento_t));
    // Fallo la allocacion
    if (nueva_celda->elem == NULL) {
        free(nueva_celda);
        return FALSE;
    }

    nueva_celda->elem->a = elem.a;
    nueva_celda->elem->b = strdup(elem.b);
    // Fallo la allocacion
    if (nueva_celda->elem->b == NULL) {
        free(nueva_celda->elem);
        free(nueva_celda);
        return FALSE;
    }

    if (pos == 0) {
        nueva_celda->siguiente = l->primera;
        l->primera = nueva_celda;
    } else {
        celda_t *anterior = l->primera;
        for (unsigned int i = 0; i < pos - 1; i++) {
            anterior = anterior->siguiente;
        }
        nueva_celda->siguiente = anterior->siguiente;
        anterior->siguiente = nueva_celda;
    }

    l->cantidad++;
    return TRUE;
}

elemento_t *lista_eliminar(lista_t *l, unsigned int pos) {
    if (pos >= l->cantidad)
        return NULL;

    elemento_t *elem_eliminado = NULL;
    if (pos == 0) {
        celda_t *celda_eliminada = l->primera;
        l->primera = l->primera->siguiente;
        elem_eliminado = celda_eliminada->elem;
        free(celda_eliminada);
    } else {
        celda_t *anterior = l->primera;
        for (unsigned int i = 0; i < pos - 1; i++) {
            anterior = anterior->siguiente;
        }
        celda_t *celda_eliminada = anterior->siguiente;
        anterior->siguiente = celda_eliminada->siguiente;
        elem_eliminado = celda_eliminada->elem;
        free(celda_eliminada);
    }

    l->cantidad--;
    return elem_eliminado;
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

    return current->elem;
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
            if (comparar(current->elem, cursor->elem) == ELEM1_MAYOR_QUE_ELEM2) {
                intercambiar(current->elem, cursor->elem);
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