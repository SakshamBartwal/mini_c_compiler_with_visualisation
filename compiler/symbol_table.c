#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

#define TABLE_SIZE 100

Symbol* symbol_table[TABLE_SIZE];

int current_scope_level = 0;

char current_scope_name[100] = "global";

unsigned int hash(char* str) {

    unsigned int hash = 0;

    while (*str) {
        hash = (hash << 2) + *str++;
    }

    return hash % TABLE_SIZE;
}

Symbol* lookup_symbol(char* name) {

    unsigned int index = hash(name);

    Symbol* temp = symbol_table[index];

    Symbol* global_match = NULL;

    while (temp != NULL) {

        if (strcmp(temp->name, name) == 0) {

            if (
                strcmp(temp->scope_name, current_scope_name) == 0
            ) {

                return temp;
            }

            if (
                strcmp(temp->scope_name, "global") == 0
            ) {

                global_match = temp;
            }
        }

        temp = temp->next;
    }

    return global_match;
}

int insert_symbol(
    char* name,
    char* type,
    char* category,
    char* file,
    int line
) {

    if (lookup_symbol(name) != NULL &&
        strcmp(current_scope_name, "global") == 0) {

        printf(
            "Semantic Error: Duplicate declaration of '%s' at line %d\n",
            name,
            line
        );

        return 0;
    }

    Symbol* temp = symbol_table[hash(name)];

    while (temp != NULL) {

        if (
            strcmp(temp->name, name) == 0 &&
            strcmp(temp->scope_name, current_scope_name) == 0
        ) {

            printf(
                "Semantic Error: Duplicate declaration of '%s' at line %d\n",
                name,
                line
            );

            return 0;
        }
        
        temp = temp->next;

        return 1;
    }

    Symbol* new_symbol = (Symbol*)malloc(sizeof(Symbol));

    strcpy(new_symbol->name, name);
    strcpy(new_symbol->type, type);

    strcpy(new_symbol->category, category);
    strcpy(new_symbol->file, file);

    new_symbol->line = line;

    new_symbol->scope_level = current_scope_level;

    strcpy(new_symbol->scope_name, current_scope_name);

    unsigned int index = hash(name);

    new_symbol->next = symbol_table[index];

    symbol_table[index] = new_symbol;
}

void print_symbol_table() {

    printf("\n=========== SYMBOL TABLE ===========\n\n");

    printf(
        "%-15s %-10s %-15s %-10s %-12s %-15s %-5s\n",
        "NAME",
        "TYPE",
        "SCOPE_NAME",
        "LEVEL",
        "CATEGORY",
        "FILE",
        "LINE"
    );

    printf(
        "---------------------------------------------------------------\n"
    );

    for (int i = 0; i < TABLE_SIZE; i++) {

        Symbol* temp = symbol_table[i];

        while (temp != NULL) {

            printf(
                "%-15s %-10s %-15s %-10d %-12s %-15s %-5d\n",
                temp->name,
                temp->type,
                temp->scope_name,
                temp->scope_level,
                temp->category,
                temp->file,
                temp->line
            );

            temp = temp->next;
        }
    }
}

void enter_scope(char* scope_name) {

    current_scope_level++;

    strcpy(current_scope_name, scope_name);
}

void exit_scope() {

    current_scope_level--;

    strcpy(current_scope_name, "global");
}