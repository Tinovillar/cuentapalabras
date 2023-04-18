#include "listaordenada.h"

#include "cuentapalabras.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

void test()
{
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

    comparacion_resultado_t comparar_enteros(elemento_t * e1, elemento_t * e2)
    {
        if (e1->b > e2->b)
        {
            return ELEM1_MAYOR_QUE_ELEM2;
        }
        else if (e1->b == e2->b)
        {
            return ELEM1_IGUAL_QUE_ELEM2;
        }
        else
        {
            return ELEM1_MENOR_QUE_ELEM2;
        }
    }

    lista_ordenar(lista, comparar_enteros);

    printf("\nORDENAR LISTA:\n");
    mostrar_elementos(lista);
}

void mostrar_ayuda()
{
    printf("===========================================================================\n");
    printf("Bienvenido a Cuenta Palabras\n");
    printf("\n");
    printf("El programa debera contar la cantidad de veces que aparece cada\n");
    printf("palabra en cada uno de los archivos y generar dos archivos de salida: \n");
    printf("\n");
    printf("    - cadauno.out: contendra la cantidad de veces que aparece cada\n");
    printf("palabra en cada archivo de texto procesado, ordenado alfabeticamente\n");
    printf("y por cantidad de apariciones de forma ascendente.\n");
    printf("\n");
    printf("    - totales.out: incluira la cantidad de veces que aparece cada\n");
    printf("palabra en todos los archivos de texto procesados, tambi�n ordenado\n");
    printf(" alfabeticamente y por cantidad de apariciones de forma descendente.\n");
    printf("\n");
    printf("Metodo de uso: \n");
    printf("Para usar el programa, debe ingresar como primer parametro la direccion\n");
    printf("del directorio donde se encuentran los archivos a analizar.\n");
    printf("===========================================================================\n");
}

// Funcion que agrega un slash (/) al final del directorio si el usuario no lo puso.
void agregar_slash_directorio(char *directorio)
{
    unsigned int directorio_len = strlen(directorio);
    int tiene_slash = directorio[directorio_len - 1] == '/';
    if (tiene_slash == FALSE)
    {
        directorio[directorio_len] = '/';
        directorio[directorio_len + 1] = '\0';
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1 || (argc > 1 && strcmp(argv[1], PARAMETRO_AYUDA) == 0))
    {
        mostrar_ayuda();
        return 0;
    }

    char *directorio = argv[1];
    agregar_slash_directorio(directorio);

    printf("Directorio a analizar: %s\n", directorio);
    leer_archivos_de_directorio(directorio);
    return 0;
}
