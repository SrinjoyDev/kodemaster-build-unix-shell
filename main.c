#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // fork, execvp
#include <sys/types.h>   // pid_t
#include <sys/wait.h>    // waitpid

#define BUFFER_SIZE 1024
#define MAX_ARGS 64

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

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

        /* Skip empty input */
        if (input[0] == '\0') {
            continue;
        }

        /* 3. TOKENIZE input */
        char *args[MAX_ARGS];
        int i = 0;

        char *token = strtok(input, " \t");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " \t");
        }
        args[i] = NULL;  // execvp requires NULL-terminated argv

        /* 4. FORK */
        pid_t pid = fork();

        if (pid == 0) {
            /* Child process */
            execvp(args[0], args);

            /* execvp returns only on failure */
            perror(args[0]);
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            /* Parent process */
            int status;
            waitpid(pid, &status, 0);
        } else {
            /* Fork failed */
            perror("fork");
        }
    }

    return 0;
}

