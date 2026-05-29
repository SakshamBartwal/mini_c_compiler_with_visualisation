#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum {
    SCOPE_GLOBAL,
    SCOPE_FUNCTION,
    SCOPE_BLOCK
} ScopeType;

typedef struct Symbol {
    char *name;
    char *data_type;
    int line_declared;
    struct Symbol *next; /* For chaining inside a hash bucket */
} Symbol;

typedef struct SymbolTable {
    ScopeType type;                  /* SCOPE_GLOBAL, SCOPE_FUNCTION, or SCOPE_BLOCK */
    Symbol *buckets[211];            /* Hash map array bucket allocation */
    struct SymbolTable *outer_scope; /* Pointer to the parent/outer block scope layer */
} SymbolTable;

/* Scope lifecycle management */
SymbolTable *create_scope(SymbolTable *parent, ScopeType type);
SymbolTable *destroy_scope(SymbolTable *current);

/* Symbol manipulation utilities */
int insert_symbol(SymbolTable *table, const char *name, const char *type, int line);
Symbol *lookup_symbol(SymbolTable *table, const char *name);

#endif