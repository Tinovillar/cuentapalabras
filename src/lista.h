#ifndef LISTA_H
#define LISTA_H

typedef enum {
    ELEM1_MAYOR_QUE_ELEM2,
    ELEM1_IGUAL_QUE_ELEM2,
    ELEM1_MENOR_QUE_ELEM2
} comparacion_resultado_t;

struct elemento {
    int a;
    char *b;
};

typedef struct elemento elemento_t;

typedef comparacion_resultado_t(funcion_comparacion_t)(
        elemento_t *elem1, elemento_t *elem2);

typedef struct celda celda_t;

struct lista {
    celda_t* primera; //puntero a la primera celda de la lista
    int cantidad; // cantidad de elementos de la lista
};

typedef struct lista lista_t;

/* Crea una lista vaciıa y la devuelve */
lista_t *lista_crear();

/* Inserta el elemento elem en la posicion pos de la lista */
int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos);

/* Elimina el elemento de la posicion pos de la lista */
elemento_t *lista_eliminar(lista_t *l, unsigned int pos);

/* Devuelve un puntero al elemento que ocupa la posicion pos de la lista. */
elemento_t *lista_elemento(lista_t *l, unsigned int pos);

/* Dada la lista y la funcion comparar ordena la lista de acuerdo al criterio de dicha funcion. */
int lista_ordenar(lista_t *l, funcion_comparacion_t comparar);

/* Devuelve la cantidad de elementos de la lista l. */
unsigned int lista_cantidad(lista_t *l);

/* Devuelve verdadero (!= 0) si la lista esta vacia, y falso (= 0) si la lista contiene al menos un elemento. */
int lista_vacia(lista_t lista);

#endif
