#include <stdlib.h>
#include "list.h"
#include "errors.h"

// The list works by copying all the data passed to it, so it's *safe*.
// It's not performance optimal, though. For a high-performance solution, the data should be passed by reference.

/* ADDS AN ELEMENT TO A LIST */
void append_to_list(List* list, void* data, size_t dataSize, void (*copy_func)(void*, void*)) {
    // CREATE A NEW NODE
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) handle_error(MALLOC_ERROR);

    // COPY THE DATA
    newNode->data = malloc(dataSize);
    if (newNode->data == NULL) handle_error(MALLOC_ERROR);
    copy_func(newNode->data, data);
    // memcpy(list->tail->data, data, dataSize); // high performance, but it's not safe and maintainable

    // CONNECT TO THE LIST
    newNode->next = NULL;
    if(list->head == NULL) {
        // If the list is empty, the new node becomes the head
        list->head = newNode;
    } else {
        // Otherwise, the new node is connected to the tail
        list->tail->next = newNode;
    }
    list->tail = newNode;
}

/* append_to_list copy function for integers */
void copy_int(void* dest, void* src) {
    int* destInt = (int*)dest;
    int* srcInt = (int*)src;
    *destInt = *srcInt;
}

/* FREES THE INSIDES OF THE LIST */
static void clear_list(List* list, void (*free_func)(void*)) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free_func(current->data);
        free(current);
        current = next;
    }
}

/* RESETS THE LIST */
void reset_list(List* list, void (*free_func)(void*)) {
    clear_list(list, free_func);
    list->head = NULL;
    list->tail = NULL;
}

void free_list(List* list, void (*free_func)(void*)) {
    clear_list(list, free_func);
    free(list);
}