#include "listaordenada.h"

#include <stdio.h>

int main()
{
    lista_t *lista = lista_crear();
    printf("Cantidad de elementos: %u\n", lista_cantidad(lista));
    elemento_t elem1;
    elem1.a = 1;
    elem1.b = "Prueba";
    lista_insertar(lista, elem1, 0);
    printf("Cantidad de elementos: %u\n", lista_cantidad(lista));

    elemento_t elem2;
    elem2.a = 2;
    elem2.b = "Segunda";
    lista_insertar(lista, elem2, 1);
    printf("Cantidad de elementos: %u\n", lista_cantidad(lista));
    mostrar_elementos(lista);

    elemento_t *primero = lista_elemento(lista, 0);
    elemento_t *segundo = lista_elemento(lista, 1);

    printf("Primero: %s, Segundo: %s\n", primero->b, segundo->b);
    return 0;
}
