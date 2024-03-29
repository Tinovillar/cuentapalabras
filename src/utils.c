#include "utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

comparacion_resultado_t comparar_elementos(elemento_t *e1, elemento_t *e2) {
    if (e1->a > e2->a)
        return ELEM1_MAYOR_QUE_ELEM2;
    else if (e1->a < e2->a)
        return ELEM1_MENOR_QUE_ELEM2;
    else {
        int result = strcmp(e1->b, e2->b);
        if (result > 0)
            return ELEM1_MAYOR_QUE_ELEM2;
        else if (result < 0)
            return ELEM1_MENOR_QUE_ELEM2;
        else
            return ELEM1_IGUAL_QUE_ELEM2;
    }
}

char *concatenar_strings(char *str1, char *str2) {
    unsigned int len1 = strlen(str1);
    unsigned int len2 = strlen(str2);
    char *result = (char *) malloc(len1 + len2 + 1);
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, str1);
    strcpy(result + len1, str2);
    return result;
}

void mostrar_ayuda() {
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

void agregar_slash_directorio(char *ruta_directorio) {
    unsigned int directorio_len = strlen(ruta_directorio);
    int tiene_slash = ruta_directorio[directorio_len - 1] == '/';
    if (tiene_slash == FALSE) {
        ruta_directorio[directorio_len] = '/';
        ruta_directorio[directorio_len + 1] = '\0';
    }
}

int calcular_archivos_en_directorio(char *ruta_directorio) {
    DIR *directorio = opendir(ruta_directorio);
    if (directorio == NULL) {
        printf("Error: No se pudo leer el directorio '%s'\n", ruta_directorio);
        return FALSE;
    }

    int cantidad_archivos = 0;
    struct dirent *archivo;
    while ((archivo = readdir(directorio)) != NULL) {
        // Ignorar . y ..
        if (strcmp(archivo->d_name, ".") == 0 || strcmp(archivo->d_name, "..") == 0)
            continue;

        // Validar extension del archivo.
        char *extension_archivo = strrchr(archivo->d_name, '.');
        if (strcmp(extension_archivo, EXTENSION_VALIDA) != 0) {
            continue;
        }

        cantidad_archivos++;
    }

    closedir(directorio);
    return cantidad_archivos;
}

resultado_directorio_t *parsear_archivos_directorio(char *ruta_directorio) {
    DIR *directorio = opendir(ruta_directorio);
    if (directorio == NULL) {
        printf("Error: No se pudo leer el directorio '%s'\n", ruta_directorio);
        return FALSE;
    }

    int archivos_en_directorio = calcular_archivos_en_directorio(ruta_directorio);
    if (archivos_en_directorio <= 0) {
        printf("Informe: No se encontraron archivos a leer el directorio '%s'\n", ruta_directorio);
        return FALSE;
    }

    // Creacion de multisets, tanto para cada archivo como para los totales
    multiset_t *totals_multiset = multiset_crear();
    multiset_t *multiset_array[archivos_en_directorio];
    for (int i = 0; i < archivos_en_directorio; i++) {
        multiset_array[i] = NULL;
    }

    // Creamos el struct de retorno
    resultado_directorio_t *resultado_directorio = (resultado_directorio_t *) malloc(
            sizeof(resultado_directorio_t) + sizeof(resultado_archivo_t *) * archivos_en_directorio);
    resultado_directorio->cantidad_archivos = archivos_en_directorio;
    resultado_directorio->totales = NULL;
    for (int i = 0; i < archivos_en_directorio; i++) {
        resultado_directorio->archivos[i] = NULL;
    }

    int indice = 0;
    struct dirent *archivo;
    while ((archivo = readdir(directorio)) != NULL) {
        // Ignorar . y ..
        if (strcmp(archivo->d_name, ".") == 0 || strcmp(archivo->d_name, "..") == 0)
            continue;

        // Validar extension del archivo.
        char *extension_archivo = strrchr(archivo->d_name, '.');
        if (strcmp(extension_archivo, EXTENSION_VALIDA) != 0) {
            continue;
        }

        // Create a multiset for the file
        multiset_t *multiset = multiset_crear();
        if (multiset == NULL) {
            printf("Error: No se pudo crear multiset para archivo!'\n");
            continue;
        }

        // Leemos el archivo
        char *ruta_archivo = concatenar_strings(ruta_directorio, archivo->d_name);
        int resultado = parsear_contenido_archivo(multiset, totals_multiset, ruta_archivo);
        if (resultado == FALSE) {
            printf("Error: No se pudo parsear el archivo!'\n");
            free(ruta_archivo);
            continue;
        }

        // Guardamos el multiset en el array
        if (multiset_array[indice] == NULL) {
            multiset_array[indice] = multiset;

            // Agregamos el resultado del procesamiento del archivo
            resultado_archivo_t *resultado_archivo = (resultado_archivo_t *) malloc(sizeof(resultado_archivo_t));
            resultado_archivo->multiset = multiset_array[indice];

            char *nombre_archivo = (char *) malloc((strlen(archivo->d_name) + 1) * sizeof(char));
            strcpy(nombre_archivo, archivo->d_name);
            resultado_archivo->nombre_archivo = nombre_archivo;

            resultado_directorio->archivos[indice] = resultado_archivo;
            indice++;
        }
        free(ruta_archivo);
    }

    resultado_directorio->totales = totals_multiset;

    closedir(directorio);
    return resultado_directorio;
}

int parsear_contenido_archivo(multiset_t *multiset_archivo, multiset_t *multiset_totales, char *ruta_archivo) {
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo leer el archivo: '%s'\n", ruta_archivo);
        return FALSE;
    }

    char buffer[PALABRA_LONGITUD_MAXIMA];
    while (fgets(buffer, PALABRA_LONGITUD_MAXIMA, archivo) != NULL) {
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        // Inserto la palabra en el multiset del archivo y el de los totales
        multiset_insertar(multiset_archivo, buffer);
        multiset_insertar(multiset_totales, buffer);
    }

    fclose(archivo);
    return TRUE;
}

int crear_archivo_resultados(resultado_directorio_t *resultado_directorio, char *ruta_directorio) {
    int resultado_cadauno = crear_archivo_cadauno(resultado_directorio, ruta_directorio);
    if (resultado_cadauno == FALSE) {
        printf("Error: No se pudo crear archivo: '%s'\n", ARCHIVO_CADAUNO);
        return FALSE;
    }
    printf("Se escribio el archivos: '%s'\n", ARCHIVO_CADAUNO);

    int resultado_totales = crear_archivo_totales(resultado_directorio, ruta_directorio);
    if (resultado_totales == FALSE) {
        printf("Error: No se pudo crear archivo: '%s'\n", ARCHIVO_TOTALES);
        return FALSE;
    }
    printf("Se escribio el archivos: '%s'\n", ARCHIVO_TOTALES);

    return TRUE;
}

int crear_archivo_cadauno(resultado_directorio_t *resultado_directorio, char *ruta_directorio) {
    char *ruta_archivo = concatenar_strings(ruta_directorio, ARCHIVO_CADAUNO);
    FILE *archivo = fopen(ruta_archivo, "w");
    if (archivo == NULL) {
        printf("Error: No se pudo crear el archivo: '%s'\n", ruta_archivo);
        free(ruta_archivo);
        return FALSE;
    }

    for (int i = 0; i < resultado_directorio->cantidad_archivos; i++) {
        if (resultado_directorio->archivos[i] != NULL) {
            // Nombre archivo
            fprintf(archivo, "%s\n", resultado_directorio->archivos[i]->nombre_archivo);
            // Palabras
            lista_t elementos = multiset_elementos(resultado_directorio->archivos[i]->multiset,
                                                    (int (*)(elemento_t, elemento_t)) comparar_elementos);
            // Meto las palabras con su apariciones
            unsigned int cantidad_elementos = lista_cantidad(&elementos);
            for (int j = 0; j < cantidad_elementos; j++) {
                elemento_t *elemento = lista_elemento(&elementos, j);
                fprintf(archivo, "%d    %s\n", elemento->a, elemento->b);
            }

            // Limpiamos la lista después de usar
            while (lista_cantidad(&elementos) > 0) {
                elemento_t *eliminado = lista_eliminar(&elementos, 0);
                free(eliminado->b);
                free(eliminado);
            }
        }
    }
    fclose(archivo);
    free(ruta_archivo);
    return TRUE;
}

int crear_archivo_totales(resultado_directorio_t *resultado_directorio, char *ruta_directorio) {
    char *ruta_archivo = concatenar_strings(ruta_directorio, ARCHIVO_TOTALES);
    FILE *archivo = fopen(ruta_archivo, "w");
    if (archivo == NULL) {
        printf("Error: No se pudo crear el archivo: '%s'\n", ruta_archivo);
        free(ruta_archivo);
        return FALSE;
    }

    if (resultado_directorio->totales == NULL) {
        printf("Error: No se encontro multiset para totales!\n");
        return FALSE;
    }
    // Palabras
    lista_t elementos = multiset_elementos(resultado_directorio->totales,
                                            (int (*)(elemento_t, elemento_t)) comparar_elementos);
    // Meto las palabras con su apariciones
    unsigned int cantidad_elementos = lista_cantidad(&elementos);
    for (int i = 0; i < cantidad_elementos; i++) {
        elemento_t *elemento = lista_elemento(&elementos, i);
        fprintf(archivo, "%d    %s\n", elemento->a, elemento->b);
    }

    // Limpiamos la lista después de usar
    while (lista_cantidad(&elementos) > 0) {
        elemento_t *eliminado = lista_eliminar(&elementos, 0);
        free(eliminado->b);
        free(eliminado);
    }

    fclose(archivo);
    free(ruta_archivo);
    return TRUE;
}

void limpiar_resultados(resultado_directorio_t* resultado_directorio){
    if (resultado_directorio == NULL) {
        return;
    }

    // Limpiar multiset de cada archivo
    for (int i = 0; i < resultado_directorio->cantidad_archivos; i++) {
        free(resultado_directorio->archivos[i]->nombre_archivo);
        multiset_eliminar(&(resultado_directorio->archivos[i]->multiset));
        free(resultado_directorio->archivos[i]);
        resultado_directorio->archivos[i] = NULL;
    }

    // Limpiar multiset totales
    multiset_eliminar(&(resultado_directorio->totales));
    resultado_directorio->totales = NULL;
    free(resultado_directorio);
    resultado_directorio = NULL;
}