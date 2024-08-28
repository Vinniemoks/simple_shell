#include <stdio.h>
#include <string.h>

int main() {
    char command[] ="Your,name,is,mokua";

    // Initialize variables for tokenization
    char *token;
    char *delim = ",";
   
    // Tokenize the input command
    token = strtok(command, delim);
   
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim); // Pass NULL to continue tokenization
    }

    return 0;
}
