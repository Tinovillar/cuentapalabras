#include "utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

comparacion_resultado_t comparar_enteros(elemento_t * e1, elemento_t * e2)
{
    if (e1->a > e2->a)
        return ELEM1_MAYOR_QUE_ELEM2;
    if (e1->a == e2->a) {
        if (e1->b > e2->b) return ELEM1_MAYOR_QUE_ELEM2;
        if (e1->b == e2->b) return ELEM1_IGUAL_QUE_ELEM2;

        return ELEM1_MENOR_QUE_ELEM2;
    }
    return ELEM1_MENOR_QUE_ELEM2;
}

char *concatenar_strings(char *str1, char *str2)
{
    unsigned int len1 = strlen(str1);
    unsigned int len2 = strlen(str2);
    char *result = (char *)malloc(len1 + len2 + 1); // add 1 for the null terminator
    if (result == NULL)
    {
        return NULL;
    }
    strcpy(result, str1);
    strcpy(result + len1, str2);
    return result;
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

void agregar_slash_directorio(char *ruta_directorio)
{
    unsigned int directorio_len = strlen(ruta_directorio);
    int tiene_slash = ruta_directorio[directorio_len - 1] == '/';
    if (tiene_slash == FALSE)
    {
        ruta_directorio[directorio_len] = '/';
        ruta_directorio[directorio_len + 1] = '\0';
    }
}

resultado_directorio_t* parsear_archivos_directorio(char *ruta_directorio)
{
    DIR *directorio = opendir(ruta_directorio);
    if (directorio == NULL)
    {
        printf("Error: No se pudo leer el directorio '%s'\n", ruta_directorio);
        return FALSE;
    }

    // Creacion de multisets, tanto para cada archivo como para los totales
    multiset_t* totals_multiset = multiset_crear();
    multiset_t *multiset_array[ARCHIVOS_MAXIMOS];
    for (int i = 0; i < ARCHIVOS_MAXIMOS; i++)
    {
        multiset_array[i] = NULL;
    }

    resultado_directorio_t* resultado_directorio =(resultado_directorio_t*) malloc(sizeof(resultado_directorio_t));
    resultado_directorio->totales = NULL;
    for (int i = 0; i < ARCHIVOS_MAXIMOS; i++)
    {
        resultado_directorio->archivos[i] = NULL;
    }

    int indice = 0;
    struct dirent *archivo;
    while ((archivo = readdir(directorio)) != NULL)
    {
        // Ignorar . y ..
        if (strcmp(archivo->d_name, ".") == 0 || strcmp(archivo->d_name, "..") == 0)
            continue;

        // Validar extension del archivo.
        char *extension_archivo = strrchr(archivo->d_name, '.');
        if (strcmp(extension_archivo, EXTENSION_VALIDA) != 0)
        {
            continue;
        }

        // Create a multiset for the file
        multiset_t *multiset = multiset_crear();
        if (multiset == NULL)
        {
            printf("Error: No se pudo crear multiset para archivo!'\n");
            continue;
        }

        // Leemos el archivo
        char *ruta_archivo = concatenar_strings(ruta_directorio, archivo->d_name);
        int resultado = parsear_contenido_archivo(multiset, totals_multiset, ruta_archivo);
        if (resultado == FALSE) {
            printf("Error: No se pudo parsear el archivo!'\n");
            continue;
        }

        // Guardamos el multiset en el array
        if (multiset_array[indice] == NULL)
        {
            multiset_array[indice] = multiset;

            // Agregamos el resultado del procesamiento del archivo
            resultado_archivo_t * resultado_archivo = (resultado_archivo_t*)malloc(sizeof (resultado_archivo_t));
            resultado_archivo->multiset = multiset_array[indice];

            char* nombre_archivo = (char*) malloc(strlen(archivo->d_name) * sizeof (char));
            strcpy(nombre_archivo, archivo->d_name);

            resultado_archivo->nombre_archivo = nombre_archivo;
            resultado_directorio->archivos[indice] = resultado_archivo;

            indice++;
        }
    }

    resultado_directorio->totales = totals_multiset;

    closedir(directorio);
    return resultado_directorio;
}

int parsear_contenido_archivo(multiset_t *multiset_archivo, multiset_t* multiset_totales, char *ruta_archivo)
{
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL)
    {
        printf("Error: No se pudo leer el archivo: '%s'\n", ruta_archivo);
        return FALSE;
    }

    char buffer[PALABRA_LONGITUD_MAXIMA];
    while (fgets(buffer, PALABRA_LONGITUD_MAXIMA, archivo) != NULL)
    {
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }
        // Inserto la palabra en el multiset del archivo y el de los totales
        multiset_insertar(multiset_archivo, buffer);
        multiset_insertar(multiset_totales, buffer);
    }

    fclose(archivo);
    return TRUE;
}

int crear_archivo_resultados(resultado_directorio_t* resultado_directorio, char* ruta_directorio) {
    char* ruta_archivo = concatenar_strings(ruta_directorio, ARCHIVO_CADAUNO);
    FILE *archivo = fopen(ruta_archivo, "w");
    if (archivo == NULL)
    {
        printf("Error: No se pudo crear el archivo: '%s'\n", ruta_archivo);
        return FALSE;
    }

    for (int i = 0; i < ARCHIVOS_MAXIMOS; i++) {
        if (resultado_directorio->archivos[i] != NULL) {
            // Nombre archivo
            fprintf(archivo, "%s\n", resultado_directorio->archivos[i]->nombre_archivo);
            // Palabras
            lista_t *elementos = multiset_elementos(resultado_directorio->archivos[i]->multiset,
                                                    (int (*)(elemento_t, elemento_t)) comparar_enteros);
            // Meto las palabras con su apariciones
            unsigned int cantidad_elementos = lista_cantidad(elementos);
            for (int j = 0; j <cantidad_elementos; j++) {
                elemento_t* elemento = lista_elemento(elementos, j);
                fprintf(archivo, "%d    %s\n", elemento->a, elemento->b);
            }
        }
    }

    fclose(archivo);
    return TRUE;
}