#include "listaordenada.h"

#include "cuentapalabras.h"

#include <stdio.h>

typedef struct celda
{
    elemento_t elem;
    struct celda *siguiente;
} celda_t;

typedef struct celda celda_t;

struct lista
{
    celda_t *primera;
    int cantidad;
};

// Implementacion de metodos

lista_t *lista_crear()
{
    lista_t *lista = (lista_t *)malloc(sizeof(lista_t));
    lista->cantidad = 0;
    lista->primera = NULL;
    return lista;
}

int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos)
{
    if (l == NULL)
        return FALSE;

    if (pos < 0 || pos > l->cantidad)
        return FALSE;

    celda_t *celda_nueva = (celda_t *)malloc(sizeof(celda_t));
    celda_nueva->siguiente = NULL;
    if (celda_nueva == NULL)
        return FALSE;
    celda_nueva->elem = elem;

    celda_t *current = l->primera;
    celda_t *prev = NULL;
    unsigned int i = 0;

    while (current != NULL && i < pos)
    {
        prev = current;
        current = current->siguiente;
        i++;
    }
    if (prev == NULL)
    { // Se inserta al inicio de la lista
        celda_nueva->siguiente = l->primera;
        l->primera = celda_nueva;
    }
    else
    { // Se inserta en medio o al final de la lista
        celda_nueva->siguiente = current;
        prev->siguiente = celda_nueva;
    }

    free(current);

    l->cantidad++;
    return TRUE;
}

elemento_t *lista_eliminar(lista_t *l, unsigned int pos)
{
    elemento_t *toReturn = NULL;
    if (l == NULL || l->cantidad == 0 || l->cantidad < pos)
        return toReturn;
    else
    {
        celda_t *cursor = l->primera;
        for (int i = 0; i < pos - 1; i++)
        {
            cursor = cursor->siguiente;
        }
        celda_t *matar = cursor->siguiente;
        cursor->siguiente = matar->siguiente;
        *toReturn = matar->elem;
        free(matar);
        return toReturn;
    }
}

elemento_t *lista_elemento(lista_t *l, unsigned int pos)
{
    if (l == NULL)
        return NULL;

    if (pos < 0 || pos > l->cantidad)
        return NULL;

    celda_t *current = l->primera;
    unsigned int i = 0;

    while (current != NULL && i < pos)
    {
        current = current->siguiente;
        i++;
    }

    return &(current->elem);
}

int lista_ordenar(lista_t *l, funcion_comparacion_t comparar) {
    celda_t *current = l->primera;
    celda_t *cursor;
    int toReturn = FALSE;
    if(l->cantidad > 0) {
        while(current->siguiente != NULL) {
        cursor = current;
        while(cursor->siguiente != NULL){
            cursor = cursor->siguiente;
            printf("\n%s || %s\n", current->elem.b, cursor->elem.b);
            if(comparar(&current->elem, &cursor->elem) == ELEM1_MAYOR_QUE_ELEM2){
                printf("ANTES DE INTERCAMBIAR: %s -- %s\n", current->elem.b, cursor->elem.b);
                intercambiar(&current->elem, &cursor->elem);
                printf("DESPUES DE INTERCAMBIAR: %s -- %s\n", current->elem.b, cursor->elem.b);
            }
            printf("\n%s || %s\n", current->elem.b, cursor->elem.b);
        }
        current = current->siguiente;
    }
    toReturn = TRUE;
    }
    return toReturn;
}

void intercambiar(elemento_t *e1, elemento_t *e2) {
    elemento_t aux = *e1;
    e1->a = e2->a;
    e1->b = e2->b;
    e2->a = aux.a;
    e2->b = aux.b;
}

unsigned int lista_cantidad(lista_t *l)
{
    if (l == NULL)
        return 0;
    return l->cantidad;
}

int lista_vacia(lista_t lista)
{
    lista_t *l = &lista;
    if (l == NULL)
        return FALSE;
    int vacia = l->cantidad == 0 ? TRUE : FALSE;
    free(l);
    return vacia;
}

void mostrar_elementos(lista_t *l)
{
    if (l != NULL)
    {
        celda_t *curr = l->primera;
        while (curr != NULL)
        {
            printf("Elemento %s\n", curr->elem.b);
            curr = curr->siguiente;
        }
    }
}
