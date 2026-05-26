#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol {

    char name[100];
    char type[50];

    char category[50];
    char file[100];

    int line;

    int scope_level;

    char scope_name[100];

    struct Symbol* next;

} Symbol;

int insert_symbol(
    char* name,
    char* type,
    char* category,
    char* file,
    int line
);

Symbol* lookup_symbol(char* name);

void print_symbol_table();

void enter_scope(char* scope_name);

void exit_scope();

extern int current_scope_level;

extern char current_scope_name[100];

#endif