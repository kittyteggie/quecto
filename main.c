#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_LINES 1000

int main(int argc, char *argv[]) {
    FILE *file;
    char line[BUFFER_SIZE];

    char lines[MAX_LINES][BUFFER_SIZE];
    int line_count = 0;
    int edit_previous = 0;

    // --version & -v
    if(argc > 1 &&
        (strcmp(argv[1], "--version") == 0 ||
        strcmp(argv[1], "-v") == 0)){
        printf("quecto text editor v0.04\nRepo: https://github.com/kittyteggie/quecto\n");
        return 0;
    }

    if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Check if a file already exists
    // TODO: Edit already existing files
    file = fopen(argv[1], "r");

    if(file != NULL){
        fclose(file);
        printf("ERROR: This file already exists, we'll add a file edit option soon\n");
        return 1;
    }

    // Make the file
    file = fopen(argv[1], "w");

    if(file == NULL){
        printf("ERROR: Could not create file\n");
        return 1;
    }

    printf("\033[?1049h");

    // The editor starts
    printf("\033[2J");
    printf("\033[H");

    printf("\033[30;47m");
    printf(" quecto text editor v0.04 \n");
    printf("\033[0m\n");

    printf("Type :w on an empty line to save and exit, :q to exit without saving and :f to go to previous line\n\n");

    while(1){
        if(fgets(line, sizeof(line), stdin) == NULL){
            break;
        }

        // :w to save the file
        if(strcmp(line, ":w\n") == 0){

            for(int i = 0; i < line_count; i++){
                fputs(lines[i], file);
            }

            break;
        }

        // :q to quit without saving
        // TODO: REMAKE IT WHEN ALREADY EXISTING FILES CAN BE READ
        if(strcmp(line, ":q\n") == 0){
            fclose(file);
            remove(argv[1]);
            printf("\033[?1049l");
            return 0;
        }

        // :f to go to the previous line
        if(strcmp(line, ":f\n") == 0){
            if(line_count > 0){
                edit_previous = 1;
            }
            continue;
        }

        if(edit_previous){
            strcpy(lines[line_count - 1], line);
            edit_previous = 0;
            continue;
        }

        if(line_count < MAX_LINES){
            strcpy(lines[line_count], line);
            line_count++;
        }
    }

    fclose(file);
    printf("\033[?1049l");

   return 0;
}
