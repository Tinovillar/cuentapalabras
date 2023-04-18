#include "cuentapalabras.h"

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void leer_archivos_de_directorio(char *directorio)
{
    DIR *directory = opendir(directorio);
    if (directory == NULL)
    {
        printf("No se pudo leer el directorio '%s'\n", directorio);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL)
    {
        // Ignorar . y ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char *extension_archivo = strrchr(entry->d_name, '.');
        if (strcmp(extension_archivo, EXTENSION_VALIDA) != 0)
        {
            free(extension_archivo);
            continue;
        }

        printf("%s %s\n", entry->d_name, extension_archivo);
        char *ruta_archivo = concatenar_strings(directorio, entry->d_name);
        leer_contenido_archivo(ruta_archivo);
    }
    closedir(directory);
}

void leer_contenido_archivo(char *archivo)
{
    FILE *fp = fopen(archivo, "r");
    if (fp == NULL)
    {
        printf("No se pudo leer el archivo '%s'\n", archivo);
        return;
    }

    printf("==========================\n");
    printf("Contenido del archivo\n");

    char buffer[PALABRA_LONGITUD_MAXIMA];
    while (fgets(buffer, PALABRA_LONGITUD_MAXIMA, fp))
    {
        printf("%s", buffer);
    }

    printf("\n");
    printf("==========================\n");
    fclose(fp);
}
