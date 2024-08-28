#include <stdio.h>
#include <string.h>

int main() {
    char command[] ="Your,name,is,mokua";
    char *token;
    char *delim = ",";
   

    token = strtok(command, delim);
   
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim); 
    }

    return 0;
}
