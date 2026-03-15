#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "section.h"
#include "errors.h"

#define BUFFER_SIZE 256
#define ALLOC_CAPACITY 8

// PARSING INFO:
// Sections are enclosed in square brackets.
// Parameter name and value are separated by the first encountered '=' character.
// Parameter names and section names can contain only alphanumeric characters and '-'.
// Comments are marked with ';' or '#'.
// All whitespaces and tabulations are ignored.

/* REMOVES ALL THE WHITE SPACES AND TABULATIONS FROM THE TEXT */
// Source: https://stackoverflow.com/questions/1726302/remove-spaces-from-a-string-in-c
static void remove_spaces(char* text) {
    char* ptr = text;
    do {
        while (isspace(*ptr)) ptr++;
    } while ((*text++ = *ptr++)); // runs as long as read pointer is not 0 (end of the string)
}

static void remove_comments(char* text) {
    while (*text) {
        if (*text == ';' || *text == '#') {
            *text = '\0';
            return;
        }
        text++;
    }
}

static void validate_name(char* name) {
    if (name == NULL) handle_error(INVALID_NAME_ERROR);
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalnum(name[i]) && name[i] != '-') handle_error(INVALID_NAME_ERROR);
    }
}

/* PARSES THE FILE AND RETURNS STRUCTURED DATA AS THE LIST OF SECTIONS */
// --- Sections are stored in --lists-- and parameters in --arrays--.
// --- This structure is optimal for an unlimited number of sections and limited number of parameters in each section,
// --- If sections would be stored in an --array--, a huge number of them could be a bottleneck in case of reallocation.
void parse(FILE* file, List* sections) {
    // READ THE DATA LINE BY LINE UNTIL THE END OF A FILE AND PARSE IT IMMEDIATELY
    // --- For an unlimited line length: file could be read char-by-char:   while ((c = fgetc(file)) != EOF) {...}
    // --- But it's a bad design, and it would affect the performance of the program greatly - limitation is expected.
    Section newSection = {NULL, 0, NULL};
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file)) {
        // TRIM THE TEXT
        remove_spaces(buffer);
        remove_comments(buffer);
        // SKIP EMPTY LINES
        if (buffer[0] == '\0') {
            continue;
        }

        // PARSE SECTIONS
        if (buffer[0] == '[' && buffer[strlen(buffer) - 1] == ']') {

            // CHECK IF THE PREVIOUS SECTION IS EMPTY
            if (newSection.name != NULL && newSection.size == 0) handle_error(EMPTY_SECTION_ERROR);
            // ADD PREVIOUS SECTION TO THE LIST
            else if (newSection.name != NULL && newSection.size != 0) {
                append_to_list(sections, &newSection, sizeof(Section), copy_section_wrapper);
                reset_section(&newSection);
            }

            // ASSIGN NAME TO THE NEW SECTION
            newSection.name = malloc(strlen(buffer) - 1);
            if (newSection.name == NULL) handle_error(MALLOC_ERROR);
            strncpy(newSection.name, buffer + 1, strlen(buffer) - 2);
            newSection.name[strlen(buffer) - 2] = '\0';
            validate_name(newSection.name);
        }
        // PARSE PARAMETERS
        else {
            if (newSection.name == NULL) handle_error(NO_SECTION_ERROR);
            // REALLOCATE MEMORY FOR THE PARAMETERS IF NEEDED
            if (newSection.size % ALLOC_CAPACITY == 0) {
                Parameter* temp = realloc(newSection.parameters,
                                          (newSection.size + ALLOC_CAPACITY) * sizeof(Parameter));
                if (temp == NULL) {
                    reset_section(&newSection);
                    handle_error(MALLOC_ERROR);
                }
                newSection.parameters = temp;
            }
            // ADD PARAMETER TO THE SECTION
            char* key = strtok(buffer, "=");
            validate_name(key);
            char* value = strtok(NULL, "\0");
            newSection.parameters[newSection.size].key = malloc(strlen(key) + 1);
            if (newSection.parameters[newSection.size].key == NULL) handle_error(MALLOC_ERROR);
            strcpy(newSection.parameters[newSection.size].key, key);
            newSection.parameters[newSection.size].value = malloc(strlen(value) + 1);
            if (newSection.parameters[newSection.size].value == NULL) handle_error(MALLOC_ERROR);
            strcpy(newSection.parameters[newSection.size].value, value);
            newSection.size++;
        }
    }
    // ADD THE LAST SECTION TO THE LIST
    append_to_list(sections, &newSection, sizeof(Section), copy_section_wrapper);
    reset_section(&newSection);
}
