#include "shell.h" 

#define BUFFER_SIZE 1024

ssize_t my_getline(char **lineptr, size_t *n, int fd) {
    static char buffer[BUFFER_SIZE];
    static size_t buffer_pos = 0;
    static ssize_t bytes_in_buffer = 0;

    size_t total_read = 0;
    char *current_pos;

    if (lineptr == NULL || n == NULL) {
        return -1;
    }

    if (*lineptr == NULL) {
        *n = BUFFER_SIZE;
        *lineptr = malloc(*n);
        if (*lineptr == NULL) {
            return -1;
        }
    }

    current_pos = *lineptr;

    while (1) {
        if (buffer_pos >= bytes_in_buffer) {
            bytes_in_buffer = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;

            if (bytes_in_buffer <= 0) {
                return total_read > 0 ? total_read : bytes_in_buffer;
            }
        }

        while (buffer_pos < bytes_in_buffer) {
            if (total_read >= *n - 1) {
                *n *= 2;
                *lineptr = realloc(*lineptr, *n);
                if (*lineptr == NULL) {
                    return -1;
                }
                current_pos = *lineptr + total_read;
            }

            *current_pos = buffer[buffer_pos];
            total_read++;
            buffer_pos++;
            current_pos++;

            if (*(current_pos - 1) == '\n') {
                *current_pos = '\0';
                return total_read;
            }
        }
    }
}
