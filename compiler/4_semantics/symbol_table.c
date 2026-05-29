#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h" /* Updated include */

/* Standard DJB2 string hashing function */
unsigned int hash(const char *str) {
    unsigned int h = 5381;
    int c;
    while ((c = *str++)) {
        h = ((h << 5) + h) + c;
    }
    return h % 211;
}

SymbolTable *create_scope(SymbolTable *parent, ScopeType type) {
    SymbolTable *table = malloc(sizeof(SymbolTable));
    if (!table) {
        fprintf(stderr, "Fatal: Out of memory for SymbolTable\n");
        exit(1);
    }
    for (int i = 0; i < 211; i++) {
        table->buckets[i] = NULL;
    }
    table->outer_scope = parent;
    table->type = type;
    return table;
}

SymbolTable *destroy_scope(SymbolTable *current) {
    if (!current) return NULL;
    SymbolTable *parent = current->outer_scope;

    /* Free all allocated symbol blocks inside this local scope table */
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

int insert_symbol(SymbolTable *table, const char *name, const char *type, int line) {
    if (!table) return 0;
    unsigned int h = hash(name);
    
    /* Check if the variable is already declared within the EXACT same scope layer */
    Symbol *curr = table->buckets[h];
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            return 0; /* Redeclaration Error */
        }
        curr = curr->next;
    }

    /* Allocate and prepend new symbol tracking token to bucket chain */
    Symbol *new_sym = malloc(sizeof(Symbol));
    new_sym->name = strdup(name);
    new_sym->data_type = strdup(type);
    new_sym->line_declared = line;
    new_sym->next = table->buckets[h];
    table->buckets[h] = new_sym;

    return 1; /* Success */
}

Symbol *lookup_symbol(SymbolTable *table, const char *name) {
    unsigned int h = hash(name);
    SymbolTable *current_scope = table;

    /* Search backwards up through parent scope layers until we hit the global context */
    while (current_scope != NULL) {
        Symbol *sym = current_scope->buckets[h];
        while (sym != NULL) {
            if (strcmp(sym->name, name) == 0) {
                return sym; /* Found variable context! */
            }
            sym = sym->next;
        }
        current_scope = current_scope->outer_scope;
    }
    return NULL; /* Variable is completely undeclared or out of scope */
}