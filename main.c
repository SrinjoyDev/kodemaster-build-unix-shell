#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char input[BUFFER_SIZE];

    while (1) {
        /* 1. PRINT prompt */
        printf("$ ");
        fflush(stdout);

        /* 2. READ input */
        if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
            /* EOF (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove trailing newline */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        /* 3. EVAL (for now: echo input) */
        printf("%s\n", input);

        /* 4. LOOP continues automatically */
    }

    return 0;
}

