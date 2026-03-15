#ifndef CALLP_INI_PARSER_ERRORS_H
#define CALLP_INI_PARSER_ERRORS_H

typedef enum {
    MALLOC_ERROR,
    NO_FILE_ERROR,
    EMPTY_SECTION_ERROR,
    NO_SECTION_ERROR,
    INVALID_NAME_ERROR,
    ARGUMENTS_ERROR,
    // Add more error types as needed
} ErrorType;

void handle_error(ErrorType error);

#endif //CALLP_INI_PARSER_ERRORS_H
