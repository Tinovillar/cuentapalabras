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
    lista_t *lista = (*lista_t) malloc(sizeof(lista_t));
    lista->cantidad = 0;
    lista->primera = NULL;
    return lista;
}

int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos) {
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

elemento_t *lista_eliminar(lista_t *l, unsigned int pos) {

}

int lista_ordenar(lista_t *l, funcion_comparacion_t comparar) {

}

unsigned int lista_cantidad(lista_t *l) {

}

int lista_vacia(list_t lista) {

}