#ifndef CALLP_INI_PARSER_LIST_H
#define CALLP_INI_PARSER_LIST_H

#include <stdio.h>

typedef struct Node
{
    void* data;
    struct Node* next;
} Node;

typedef struct List
{
    Node* head;
    Node* tail;
} List;

void append_to_list(List* list, void* data, size_t dataSize, void (*copy_func)(void*, void*));
void reset_list(List* list, void (*free_func)(void*));
void free_list(List* list, void (*free_func)(void*));

#endif //CALLP_INI_PARSER_LIST_H
