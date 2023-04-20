#include "listaordenada.h"

#include "utils.h"

#include <stdio.h>
#include <string.h>

void test() {
    lista_t *lista = lista_crear();
    printf("Cantidad de elementos: %u\n", lista_cantidad(lista));

    elemento_t elem1;
    elem1.a = 1;
    elem1.b = "a";
    lista_insertar(lista, elem1, 0);
    printf("Cantidad de elementos: %u\n", lista_cantidad(lista));

    elemento_t elem2;
    elem2.a = 2;
    elem2.b = "b";
    lista_insertar(lista, elem2, 1);
    printf("Cantidad de elementos: %u\n", lista_cantidad(lista));
    mostrar_elementos(lista);

    elemento_t elem3;
    elem3.a = 3;
    elem3.b = "c";
    lista_insertar(lista, elem3, 2);
    printf("Cantidad de elementos: %u\n", lista_cantidad(lista));
    mostrar_elementos(lista);

    elemento_t elem4;
    elem4.a = 4;
    elem4.b = "d";
    lista_insertar(lista, elem4, 3);
    printf("Cantidad de elementos: %u\n", lista_cantidad(lista));
    mostrar_elementos(lista);

    elemento_t elem5;
    elem5.a = 5;
    elem5.b = "e";
    lista_insertar(lista, elem5, 4);
    printf("Cantidad de elementos: %u\n\n", lista_cantidad(lista));
    mostrar_elementos(lista);

    comparacion_resultado_t comparar_enteros(elemento_t *e1, elemento_t *e2) {
        if (e1->b > e2->b) {
            return ELEM1_MAYOR_QUE_ELEM2;
        } else if (e1->b == e2->b) {
            return ELEM1_IGUAL_QUE_ELEM2;
        } else {
            return ELEM1_MENOR_QUE_ELEM2;
        }
    }

    lista_ordenar(lista, comparar_enteros);

    printf("\nORDENAR LISTA:\n");
    mostrar_elementos(lista);
}
