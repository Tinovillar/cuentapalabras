#include "cuentapalabras.h"

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

void print_cwd()
{
    char cwd[1024]; // Allocate a buffer for the cwd
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        // Successfully retrieved the cwd, print it to stdout
        printf("Current working directory: %s\n", cwd);
    }
    else
    {
        // Error occurred while retrieving the cwd, print an error message to stderr
        fprintf(stderr, "Failed to get current working directory\n");
    }
}

void leer_archivos_de_directorio(char *directorio)
{
    DIR *directory = opendir(directorio);
    if (directory == NULL)
    {
        fprintf(stderr, "No se pudo leer el directorio '%s'\n", directorio);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL)
    {
        // Ignorar . y ..
        if (entry->d_name[0] != '.')
        {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(directory);
}
