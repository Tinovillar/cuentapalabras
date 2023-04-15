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

    if (pos > l->cantidad)
        return FALSE;

    celda_t *celda_nueva = (celda_t *)malloc(sizeof(celda_t));
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
}

int lista_ordenar(lista_t *l, funcion_comparacion_t comparar)
{
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
