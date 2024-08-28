#include "shell.h" // Include your header file

#define BUFFER_SIZE 1024

void my_prompt(void) {
    printf("simple_shell> ");
}

void excute_command(char **args, char **envp) {
    if (strcmp(args[0], "env") == 0) {
        print_env(envp);
        return;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return;
    }

    if (pid == 0) { // Child process
        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    } else { // Parent process
        wait(NULL);
    }
}

void parse_command(char *command, char **args) {
    char *token;
    int i = 0;

    token = strtok(command, " \n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL; // Null-terminate the array of arguments
}

void print_env(char **envp) {
    while (*envp) {
        printf("%s\n", *envp);
        envp++;
    }
}

int main(int argc, char **argv, char **envp) {
    char buffer[BUFFER_SIZE];
    char *args[BUFFER_SIZE / 2 + 1];

    while (1) {
        display_prompt();

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }

        parse_command(buffer, args);

        if (args[0] != NULL && strcmp(args[0], "exit") == 0) {
            break;
        }

        execute_command(args, envp);
    }

    return 0;
}
