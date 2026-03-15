#include <stdlib.h>
#include <stdio.h>
#include "errors.h"

// This program doesn't handle errors in a sophisticated way, as the memory isn't freed properly.
// To fix this, functions could return error codes and the caller would be responsible for freeing the memory.
// Other solution could be: https://stackoverflow.com/questions/368385/implementing-raii-in-pure-c

void handle_error(ErrorType error) {
    switch (error) {
        case MALLOC_ERROR:
        case NO_FILE_ERROR:
            perror("System error");
            break;
        case EMPTY_SECTION_ERROR:
            printf("Error: There is an empty section in the file!\n");
            break;
        case NO_SECTION_ERROR:
            printf("Error: No section at the start of a file!\n");
            break;
        case INVALID_NAME_ERROR:
            printf("Error: Invalid section or parameter name!\n");
            break;
        case ARGUMENTS_ERROR:
            printf("Error: Invalid number of arguments!\n");
            break;
            // Handle more error types as needed
    }
    exit(1);
}
