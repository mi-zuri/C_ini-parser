#include <string.h>
#include <stdlib.h>
#include "search.h"
#include "section.h"

/* SEARCHES FOR THE KEY IN THE LIST OF SECTIONS AND PRINTS ITS VALUE */
void search(const List sections, char* search_key) {
    char* section_name = strtok(search_key, ".");
    char* parameter_name = strtok(NULL, ".");
    Node* current = sections.head;
    while (current != NULL) {
        Section* section = (Section*)current->data;
        if (strcmp(section->name, section_name) == 0) {
            for (int i = 0; i < section->size; i++) {
                if (strcmp(section->parameters[i].key, parameter_name) == 0) {
                    printf("Value of [%s].%s is %s\n", section_name, parameter_name, section->parameters[i].value);
                    return;
                }
            }
            printf("Failed to find key \"%s\" in section [%s]\n", parameter_name, section_name);
            exit(1);
        }
        current = current->next;
    }
    printf("Failed to find section [%s]\n", search_key);
    exit(1);
}