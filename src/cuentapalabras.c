#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Condicion para mostrar cartel de ayuda.
    if (argc == 1 || (argc > 1 && strcmp(argv[1], PARAMETRO_AYUDA) == 0)) {
        mostrar_ayuda();
        return 0;
    }

    // Parseo de ruta de directorio
    char *ruta_directorio = argv[1];
    agregar_slash_directorio(ruta_directorio);

    // Metodos principales.
    resultado_directorio_t *resultado_directorio = parsear_archivos_directorio(ruta_directorio);
    if (resultado_directorio == NULL) {
        return 0;
    }
    int resultado = crear_archivo_resultados(resultado_directorio, ruta_directorio);
    if (resultado == TRUE) {
        printf("Se escribieron los archivos!\n");
    }

    // Cleanup totales
    multiset_eliminar(&resultado_directorio->totales);
    // Cleanup cadauno.
    for (int i = 0; i < resultado_directorio->cantidad_archivos; i++) {
        multiset_eliminar(&resultado_directorio->archivos[i]->multiset);
        // TODO: hacer un free del nombre del archivo por alguna razon rompe tood.
        // free(resultado_directorio->archivos[i]->nombre_archivo);
        free(resultado_directorio->archivos[i]);
        resultado_directorio->archivos[i] = NULL;
    }
    // Cleanup final.
    free(resultado_directorio);
    resultado_directorio = NULL;

    return resultado;
}
