#include <stdlib.h>
#include <string.h>
#include "section.h"
#include "errors.h"

// This file contains functions for handling sections

void copy_section(Section* dest, const Section* src) {
    dest->size = src->size;

    dest->name = malloc(strlen(src->name) + 1);
    if (dest->name == NULL) handle_error(MALLOC_ERROR);
    strcpy(dest->name, src->name);

    dest->parameters = malloc(src->size * sizeof(Parameter));
    if (dest->parameters == NULL) handle_error(MALLOC_ERROR);
    for (int i = 0; i < src->size; i++) {
        dest->parameters[i].key = malloc(strlen(src->parameters[i].key) + 1);
        if (dest->parameters[i].key == NULL) handle_error(MALLOC_ERROR);
        strcpy(dest->parameters[i].key, src->parameters[i].key);
        dest->parameters[i].value = malloc(strlen(src->parameters[i].value) + 1);
        if (dest->parameters[i].value == NULL) handle_error(MALLOC_ERROR);
        strcpy(dest->parameters[i].value, src->parameters[i].value);
    }
}

void copy_section_wrapper(void* dest, void* src) {
    copy_section((Section*)dest, (Section*)src);
}

static void clear_section(Section* section) {
    if (section->name != NULL) free(section->name);
    if (section->size > 0) {
        for (int i = 0; i < section->size; i++) {
            free(section->parameters[i].key);
            free(section->parameters[i].value);
        }
        free(section->parameters);
    }
}

void reset_section(Section* section) {
    clear_section(section);
    section->name = NULL;
    section->size = 0;
    section->parameters = NULL;
}

void free_section(Section* section) {
    clear_section(section);
    free(section);
}

void free_section_wrapper(void* section) {
    free_section((Section*)section);
}