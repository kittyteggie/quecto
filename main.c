#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *file;
    char line[BUFFER_SIZE];

    // --version
    if(argc > 1 &&
        (strcmp(argv[1], "--version") == 0 ||
         strcmp(argv[1], "-v") == 0)){
        printf("quecto text editor v0.03\nRepo: https://github.com/kittyteggie/quecto\n");
        return 0;
    }

    if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Checar si un archivo ya existe
    // TODO: Poder editar archivos existentes
    file = fopen(argv[1], "r");

    if(file != NULL){
        fclose(file);
        printf("ERROR: This file already exists, we'll add a file edit option soon\n");
        return 1;
    }

    // Crear archivo
    file = fopen(argv[1], "w");

    if(file == NULL){
        printf("ERROR: Could not create file\n");
        return 1;
    }

    printf("\033[?1049h");

    // Comienza el editor
    printf("\033[2J");
    printf("\033[H");

    printf("\033[30;47m");
    printf(" quecto text editor v0.03 \n");
    printf("\033[0m\n");

    printf("Type :w on an empty line to save and exit or :q to exit without saving\n\n");

    while(1){
        if(fgets(line, sizeof(line), stdin) == NULL){
            break;
        }

	// El :w para guardar el archivo
        if(strcmp(line, ":w\n") == 0){
            break;
        }
    // el :q para quitar
	// TODO: REHACERLO CUANDO SE PUEDAN EDITAR ARCHIVOS EXISTENTES
        if(strcmp(line, ":q\n") == 0){
            fclose(file);
            remove(argv[1]);
            printf("\033[?1049l");
            return 0;
		}
        fputs(line, file);
    }

    fclose(file);
    printf("\033[?1049l");

    return 0;
}
