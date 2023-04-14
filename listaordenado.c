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

lista t *lista crear() {
    lista_t *lista = (*lista_t) malloc(sizeof(lista_t));
    lista->cantidad = 0;
    lista->primera = NULL;
    return lista;
}

int lista insertar(lista t *l, elemento_t elem, unsigned int pos) {
    if(l != NULL) return FALSE; // CHEQUEO QUE NO SEA NULA

    if(l->cantidad == 0){
        l->primera = (*celda_t) malloc(sizeof(celda_t));
        l->primera->elem = elem;
        l->primera->siguiente = NULL;
    } else {
        celda_t *cursor = l->primera;
        for(int i = 0; i < l->cantidad; i++) {
            cursor = cursor->siguiente;
        }
        cursor->siguiente = (*celda_t) malloc(sizeof(celda_t));
        cursor->siguiente->elem = elem;
        cursor->siguiente->siguiente = NULL;
    }
}

elemento t *lista eliminar(lista t *l, unsigned int pos) {

}

elemento t *lista elemento(lista t *l, unsigned int pos) {

}

int lista ordenar(lista t *l, funcion comparacion t comparar) {

}

unsigned int lista cantidad(lista t *l) {

}

int lista vacia(list t lista) {

}
