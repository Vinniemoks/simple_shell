#include "shell.h" // Include your existing header file

void recognise_comments(FILE *file) {
    char c;
    int in_single_line_comment = 0;
    int in_multi_line_comment = 0;

    while ((c = fgetc(file)) != EOF) {
        if (in_single_line_comment) {
            // If we're inside a single-line comment, print until the end of the line
            if (c == '\n') {
                in_single_line_comment = 0;
                printf("\n");
            } else {
                putchar(c);
            }
        } else if (in_multi_line_comment) {
            // If we're inside a multi-line comment, print until we find the closing */
            if (c == '*' && (c = fgetc(file)) == '/') {
                in_multi_line_comment = 0;
                printf("*/\n");
            } else {
                putchar(c);
            }
        } else {
            // Not in a comment, look for the start of a comment
            if (c == '/') {
                char next = fgetc(file);
                if (next == '/') {
                    in_single_line_comment = 1;
                    printf("//");
                } else if (next == '*') {
                    in_multi_line_comment = 1;
                    printf("/*");
                } else {
                    // Not a comment, just print the characters
                    putchar(c);
                    putchar(next);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Could not open file");
        return 1;
    }

    recognise_comments(file);

    fclose(file);
    return 0;
}
