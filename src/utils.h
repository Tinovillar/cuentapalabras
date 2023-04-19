#ifndef UTILS_H
#define UTILS_H

#define FALSE 0
#define TRUE 1

#define PARAMETRO_AYUDA "-h"
#define PALABRA_LONGITUD_MAXIMA 256

#define EXTENSION_VALIDA ".txt"

#define ARCHIVO_CADAUNO "cadauno.out"
#define ARCHIVO_TOTALES "totales.out"

#define ARCHIVOS_MAXIMOS 100

#include "multiset.h"

struct resultado_archivo {
    char* nombre_archivo;
    multiset_t * multiset;
};

typedef struct resultado_archivo resultado_archivo_t;

struct resultado_directorio {
    resultado_archivo_t* archivos[100];
    multiset_t * totales;
};

typedef struct resultado_directorio resultado_directorio_t;

/**
 * Funcion de comparacion entre dos elementos. Primero compara la cantidad de
 * apariciones, y si esta coincide se compara alfabeticaamente el nombre.
 * @param e1 Elemento 1.
 * @param e2 Elemento 2.
 * @return El resultado de la comparacion.
 */
comparacion_resultado_t comparar_enteros(elemento_t * e1, elemento_t * e2);

/**
 * Funcion que toma dos char* y los concatena.
 * @param str1 String 1 a concatenar.
 * @param str2 String 2 a concatenar.
 * @return La string concatenada
 */
char* concatenar_strings(char* str1, char* str2);

/**
 * Funcion que muestra el cartel de ayuda del programa.
 */
void mostrar_ayuda();

/**
 * Funcion que toma un directorio y si no tiene slash (/) al
 * final se lo agrega.
 * @param ruta_directorio Directorio a modificar
 */
void agregar_slash_directorio(char *ruta_directorio);

/**
 * Funcion que lee los archivos de un directorio dado y realiza toda la logica
 * de parsearlos y crear la informacion neceesaria para luego crear los
 * archivos de salida.
 * @param ruta_directorio Directorio a analizar.
 * @return La struct conteniendo los datos obtenidos.
 */
resultado_directorio_t* parsear_archivos_directorio(char *ruta_directorio);

/**
 * Funcion que parsea un archivo y agrega sus palabras a los multisets correspondientes.
 * @param multiset_archivo Multiset del archivo en si.
 * @param multiset_totales Multiset de los totales.
 * @param ruta_archivo Ruta del archivo a analizar.
 * @return True o false si fue exitoso o no.
 */
int parsear_contenido_archivo(multiset_t* multiset_archivo, multiset_t* multiset_totales, char *ruta_archivo);

/**
 * Funcion que crea el archivo cadauno.out conteniendo los resultados del parseo previo.
 * @param resultado_directorio Struct conteniendo los datos del parseo.
 * @param ruta_directorio La ruta del directorio a crear el archivo.
 * @return True o false si fue exitoso o no.
 */
int crear_archivo_resultados(resultado_directorio_t* resultado_directorio, char* ruta_directorio);

#endif
