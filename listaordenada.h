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

typedef comparacion_resultado_t (funcion_comparacion_t) (
    elemento_t *elem1, elemento_t *elem2
);

typedef struct lista lista_t;

// Metodos

lista t *lista crear();

int lista insertar(lista t *l, elemento t elem, unsigned int pos);

elemento t *lista eliminar(lista t *l, unsigned int pos);

elemento t *lista elemento(lista t *l, unsigned int pos);

int lista ordenar(lista t *l, funcion comparacion t comparar)

unsigned int lista cantidad(lista t *l);

int lista vacia(list t lista);

