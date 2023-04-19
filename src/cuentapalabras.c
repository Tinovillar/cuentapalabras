#include "utils.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Condicion para mostrar cartel de ayuda.
    if (argc == 1 || (argc > 1 && strcmp(argv[1], PARAMETRO_AYUDA) == 0))
    {
        mostrar_ayuda();
        return 0;
    }

    // Parseo de ruta de directorio
    char *ruta_directorio = argv[1];
    agregar_slash_directorio(ruta_directorio);

    // Metodos principales.
    resultado_directorio_t* resultado_directorio = parsear_archivos_directorio(ruta_directorio);
    int resultado = crear_archivo_resultados(resultado_directorio, ruta_directorio);
    if (resultado == TRUE) {
        printf("Se escribio el archivo exitosamente!\n");
    }
    return resultado;
}
