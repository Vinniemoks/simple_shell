#include "shell.h"

#define BUFFER_SIZE 1024

void display_prompt(void) {
    printf("simple_shell> ");
}

void execute_command(char *command) {
    if (command == NULL || command[0] == '\0') {
        return;
    }

    /* Remove newline character from the command*/
    command[strcspn(command, "\n")] = '\0';

    /* Fork a child process*/
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return;
    }

    if (pid == 0) { 
        if (execlp(command, command, NULL) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

int main(void) {
    char buffer[BUFFER_SIZE];

    while (1) {
        display_prompt();

        // Read the command from stdin
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            // Handle EOF (Ctrl+D)
            printf("\n");
            break;
        }

        // Exit the shell if the command is "exit"
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }

        execute_command(buffer);
    }

    return 0;
}
