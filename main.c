#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    // Guardar la terminal actual para luego ponerla de nuevo al cerrar
    printf("\033[?1049h");

    FILE *file;
    char line[BUFFER_SIZE];

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Checar si un archivo ya existe
    // TODO: Poder editar archivos existentes
    file = fopen(argv[1], "r");

    if (file != NULL) {
        fclose(file);
        printf("ERROR: This file already exists, we'll add a file edit option soon\n");
        return 1;
    }

    // Crear archivo
    file = fopen(argv[1], "w");

    if (file == NULL) {
        printf("ERROR: Could not create file\n");
        return 1;
    }

    // Comienza el editor :0
    printf("\033[2J");
    printf("\033[H");
    printf("\033[30;47m");
    printf(" quecto text editor v0.01 \n");
    printf("\033[0m\n");
    printf("Type :w on an empty line to save and exit.\n\n");

    while (1) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
      
        // El :w para guardar el archivo
        if (strcmp(line, ":w\n") == 0) {
            break;
        }

        fputs(line, file);
    }
    printf("\033[?1049l");

    fclose(file);
    return 0;
}
