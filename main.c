#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_LINES 1000

int main(int argc, char *argv[]){
    FILE *file;
    char line[BUFFER_SIZE];
    char lines[MAX_LINES][BUFFER_SIZE];
    int line_count = 0;
    int current_line = 0;
    int existing_file = 0;
    // --version & -v
    if(argc > 1 &&
       (strcmp(argv[1], "--version") == 0 ||
        strcmp(argv[1], "-v") == 0)){
        printf("quecto text editor v0.05\n");
        printf("Repo: https://github.com/kittyteggie/quecto\n");
        return 0;
    }
    if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    // Load file if exists
    file = fopen(argv[1], "r");
    if(file != NULL){
        existing_file = 1;
        while(fgets(line, sizeof(line), file) != NULL &&
              line_count < MAX_LINES){
            strcpy(lines[line_count], line);
            line_count++;
        }
        fclose(file);
        // Start since last line
        current_line = line_count;
    }
    printf("\033[?1049h");
    printf("\033[2J");
    printf("\033[H");
    printf("\033[30;47m");
    printf(" quecto text editor v0.05 \n");
    printf("\033[0m\n");
    printf("Commands:\n");
    printf(":w      Save and exit\n");
    printf(":q      Exit without saving\n");
    printf(":f      Previous line\n");
    printf(":f N    Go to line N\n\n");
    if(existing_file){
        printf("Loaded %d lines from %s\n\n",
               line_count, argv[1]);
    }
    while(1){
        printf("%d~ ", current_line + 1);
        fflush(stdout);
        if(fgets(line, sizeof(line), stdin) == NULL){
            break;
        }
        // Save
        if(strcmp(line, ":w\n") == 0){
            file = fopen(argv[1], "w");
            if(file == NULL){
                printf("ERROR: Could not save file\n");
                continue;
            }
            for(int i = 0; i < line_count; i++){
                fputs(lines[i], file);
            }
            fclose(file);
            break;
        }
        // Quit without saving
        if(strcmp(line, ":q\n") == 0){
            printf("\033[?1049l");
            return 0;
        }
        // :f (Former line)
        if(strcmp(line, ":f\n") == 0){
            if(current_line > 0){
                current_line--;
            }
            continue;
        }
        // :f <number>
        if(strncmp(line, ":f ", 3) == 0){
            int target = atoi(line + 3);
            if(target > 0 && target <= MAX_LINES){
                current_line = target - 1;
                if(current_line > line_count){
                    line_count = current_line;
                }
            }
            continue;
        }
        // Write/Replace current line
        if(current_line < MAX_LINES){
            strcpy(lines[current_line], line);
            if(current_line >= line_count){
                line_count = current_line + 1;
            }
            current_line++;
        }
    }
    printf("\033[?1049l");
    return 0;
}
