#ifndef CALLP_INI_PARSER_SECTION_H
#define CALLP_INI_PARSER_SECTION_H

typedef struct Parameter
{
    char* key;
    char* value;
} Parameter;

typedef struct Section
{
    char* name;
    int size;
    Parameter* parameters;
} Section;

void copy_section(Section* dest, const Section* src);
void copy_section_wrapper(void* dest, void* src);
void reset_section(Section* section);
void free_section(Section* section);
void free_section_wrapper(void* section);

#endif //CALLP_INI_PARSER_SECTION_H
