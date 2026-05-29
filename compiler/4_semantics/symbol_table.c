#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"



// Flat array structure designed to preserve a snapshot of variables for React Flow
typedef struct {
    char name[50];
    char type[50];
    char scope[50];
    int line;
} UISymbol;

UISymbol ui_symbols[1000];
int ui_symbol_count = 0;



// Standard string hash utility to compute bucket placements
unsigned int hash(const char *str) {

    unsigned int h = 5381;
    int c;

    while ((c = *str++)) {
        h = ((h << 5) + h) + c;
    }

    return h % 211;
}



// Generates a completely new scope layer mapping back to its parent context
SymbolTable *create_scope(SymbolTable *parent, ScopeType type) {

    SymbolTable *table = malloc(sizeof(SymbolTable));

    if (!table) {
        fprintf(stderr, "Fatal: Out of memory for SymbolTable\n");
        exit(1);
    }

    // Initialize all underlying hash map slots to null pointers
    for (int i = 0; i < 211; i++) {
        table->buckets[i] = NULL;
    }

    table->outer_scope = parent;
    table->type = type;

    return table;
}



// Walks through an active scope and completely frees up its bucket memory allocations
SymbolTable *destroy_scope(SymbolTable *current) {

    if (!current) {
        return NULL;
    }

    SymbolTable *parent = current->outer_scope;


    for (int i = 0; i < 211; i++) {
        Symbol *sym = current->buckets[i];

        while (sym != NULL) {
            Symbol *next = sym->next;

            free(sym->name);
            free(sym->data_type);
            free(sym);

            sym = next;
        }
    }

    free(current);

    return parent;
}



// Registers a newly declared tracking variable token inside our current active scope
int insert_symbol(SymbolTable *table, const char *name, const char *type, int line) {

    if (!table) {
        return 0;
    }

    unsigned int h = hash(name);
    Symbol *curr = table->buckets[h];


    // Check if the exact same variable name already exists inside this local layer
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            return 0; 
        }
        curr = curr->next;
    }


    // Configure and prepend the fresh identifier token to the hash slot bucket chain
    Symbol *new_sym = malloc(sizeof(Symbol));
    new_sym->name = strdup(name);
    new_sym->data_type = strdup(type);
    new_sym->line_declared = line;
    new_sym->next = table->buckets[h];
    table->buckets[h] = new_sym;


    // Log a permanent snapshot for the UI before local blocks are completely erased
    if (ui_symbol_count < 1000) {
        strncpy(ui_symbols[ui_symbol_count].name, name, 49);
        strncpy(ui_symbols[ui_symbol_count].type, type, 49);
        
        if (table->type == SCOPE_GLOBAL) {
            strcpy(ui_symbols[ui_symbol_count].scope, "Global");
        } else if (table->type == SCOPE_FUNCTION) {
            strcpy(ui_symbols[ui_symbol_count].scope, "Function");
        } else {
            strcpy(ui_symbols[ui_symbol_count].scope, "Block");
        }
        
        ui_symbols[ui_symbol_count].line = line;
        ui_symbol_count++;
    }

    return 1; 
}



// Searches backward up through nesting hierarchies until a matching token is found
Symbol *lookup_symbol(SymbolTable *table, const char *name) {

    unsigned int h = hash(name);
    SymbolTable *current_scope = table;


    while (current_scope != NULL) {
        Symbol *sym = current_scope->buckets[h];

        while (sym != NULL) {
            if (strcmp(sym->name, name) == 0) {
                return sym; 
            }
            sym = sym->next;
        }

        // Drop down one layer into the parent context if lookups miss locally
        current_scope = current_scope->outer_scope;
    }

    return NULL; 
}


// Exports our compiled variable snapshots straight into a structured JSON layout for the UI
void export_symbols_to_json(const char *filename) {

    FILE *fp = fopen(filename, "w");

    if (!fp) {
        return;
    }


    fprintf(fp, "{\n  \"Global Scope Layer\": [\n");
    int first_global = 1;

    // Pass 1: Write out all Global variables sequentially
    for (int i = 0; i < ui_symbol_count; i++) {
        if (strcmp(ui_symbols[i].scope, "Global") == 0) {
            if (!first_global) {
                fprintf(fp, ",\n");
            }
            fprintf(fp, "    {\"name\": \"%s\", \"type\": \"%s\", \"category\": \"variable\"}", 
                    ui_symbols[i].name, ui_symbols[i].type);
            first_global = 0;
        }
    }


    fprintf(fp, "\n  ],\n  \"Local Scope (main)\": [\n");
    int first_local = 1;

    // Pass 2: Write out all local function block variables sequentially
    for (int i = 0; i < ui_symbol_count; i++) {
        if (strcmp(ui_symbols[i].scope, "Global") != 0) {
            if (!first_local) {
                fprintf(fp, ",\n");
            }
            fprintf(fp, "    {\"name\": \"%s\", \"type\": \"%s\", \"category\": \"variable\"}", 
                    ui_symbols[i].name, ui_symbols[i].type);
            first_local = 0;
        }
    }

    fprintf(fp, "\n  ]\n}\n");

    fclose(fp);
    
    // Clear the tracker token index count back down to 0 for subsequent builds
    ui_symbol_count = 0; 
}