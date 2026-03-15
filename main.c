#include <stdio.h>
#include "parser.h"
#include "errors.h"
#include "list.h"
#include "section.h"
#include "search.h"

// Use strtol to convert strings to integers to raise grade to 5.0
//
// Compile with: clang -Wall -Wextra main.c errors.c list.c parser.c search.c section.c -o main
// To check for memory leaks use Valgrind (Linux) or Leaks (macOS)
// To use Leaks type in Terminal:
// export MallocStackLogging=1
// leaks --atExit -- ./YOUR_PROGRAM_NAME

int main(int argc, char* argv[]) {
    if (argc != 3) handle_error(ARGUMENTS_ERROR);
    const char* filename = argv[1];
    char* search_key = argv[2];

    // OPEN THE FILE
    FILE* file = fopen(filename, "r");
    if (file == NULL) handle_error(NO_FILE_ERROR);

    // PARSE THE FILE
    List sections = {NULL, NULL};
    parse(file, &sections);

    // CLOSE THE FILE
    fclose(file);

    // SEARCH FOR THE KEY AND PRINT ITS VALUE
    search(sections, search_key);

    // FREE THE MEMORY
    reset_list(&sections, free_section_wrapper);
    return 0;
}
