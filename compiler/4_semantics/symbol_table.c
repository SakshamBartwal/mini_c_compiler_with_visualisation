#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

// Flat array structure designed to preserve a snapshot of variables for React Flow
typedef struct {
    char name[50];
    char type[20];
    char scope[50];     // Tracks function context ("Global", "main", etc.)
    char category[20];  // Tracks role ("variable", "function", "parameter")
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
int insert_symbol(SymbolTable *table, const char *name, const char *type, const char *category, const char *active_func_name) {
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
    new_sym->next = table->buckets[h];
    table->buckets[h] = new_sym;

    // Log a permanent snapshot for the UI before local blocks are completely erased
    if (ui_symbol_count < 1000) {
        
        // Safe string copies bounded strictly to avoid buffer overflows
        strncpy(ui_symbols[ui_symbol_count].name, name, sizeof(ui_symbols[ui_symbol_count].name) - 1);
        ui_symbols[ui_symbol_count].name[sizeof(ui_symbols[ui_symbol_count].name) - 1] = '\0';
        
        strncpy(ui_symbols[ui_symbol_count].type, type, sizeof(ui_symbols[ui_symbol_count].type) - 1);
        ui_symbols[ui_symbol_count].type[sizeof(ui_symbols[ui_symbol_count].type) - 1] = '\0';
        
        // FIXED: Store the exact category explicitly passed down by the semantic analyzer
        strncpy(ui_symbols[ui_symbol_count].category, category, sizeof(ui_symbols[ui_symbol_count].category) - 1);
        ui_symbols[ui_symbol_count].category[sizeof(ui_symbols[ui_symbol_count].category) - 1] = '\0';
        
        // Dynamically assign scope classifications instead of hardcoding "Function"/"Block"
        if (table->type == SCOPE_GLOBAL) {
            strcpy(ui_symbols[ui_symbol_count].scope, "Global");
        } else {
            // Assign the name of the active surrounding function executing this block
            if (active_func_name && strlen(active_func_name) > 0) {
                strncpy(ui_symbols[ui_symbol_count].scope, active_func_name, sizeof(ui_symbols[ui_symbol_count].scope) - 1);
            } else {
                strcpy(ui_symbols[ui_symbol_count].scope, "Unknown_Local");
            }
        }
        
        // THE SAFE FIX: Clean, single-indexed bounds checking calculated perfectly by the compiler
        ui_symbols[ui_symbol_count].scope[sizeof(ui_symbols[ui_symbol_count].scope) - 1] = '\0';
        
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

// Formats our compiled variable snapshots with all 5 telemetry properties into a JSON map
void export_symbols_to_json(const char *filename) {
    FILE *fp = fopen(filename, "w");
    
    if (!fp) {
        return;
    }

    fprintf(fp, "{\n  \"Global Scope Layer\": [\n");
    int first_global = 1;

    // ------------------------------------------------------------------------
    // PASS 1: Serialize Global components with all tracking attributes
    // ------------------------------------------------------------------------
    for (int i = 0; i < ui_symbol_count; i++) {
        if (strcmp(ui_symbols[i].scope, "Global") == 0) {
            
            if (!first_global) {
                fprintf(fp, ",\n");
            }
            
            fprintf(fp, "    {\"name\": \"%s\", \"type\": \"%s\", \"scope\": \"%s\", \"category\": \"%s\"}", 
                    ui_symbols[i].name, ui_symbols[i].type, ui_symbols[i].scope, ui_symbols[i].category);
                    
            first_global = 0;
        }
    }
    
    fprintf(fp, "\n  ]");

    // ------------------------------------------------------------------------
    // PASS 2: Isolate individual local functions and serialize complete profiles
    // ------------------------------------------------------------------------
    for (int i = 0; i < ui_symbol_count; i++) {
        
        if (strcmp(ui_symbols[i].scope, "Global") != 0) {
            
            int already_processed = 0;
            for (int j = 0; j < i; j++) {
                if (strcmp(ui_symbols[j].scope, ui_symbols[i].scope) == 0) {
                    already_processed = 1;
                    break;
                }
            }
            
            if (already_processed) {
                continue;
            }

            fprintf(fp, ",\n  \"Local Scope (%s)\": [\n", ui_symbols[i].scope);
            int first_local = 1;

            // Collect and serialize all elements belonging to this active function track
            for (int k = 0; k < ui_symbol_count; k++) {
                if (strcmp(ui_symbols[k].scope, ui_symbols[i].scope) == 0) {
                    
                    if (!first_local) {
                        fprintf(fp, ",\n");
                    }
                    
                    fprintf(fp, "    {\"name\": \"%s\", \"type\": \"%s\", \"scope\": \"%s\", \"category\": \"%s\"}", 
                            ui_symbols[k].name, ui_symbols[k].type, ui_symbols[k].scope, ui_symbols[k].category);
                            
                    first_local = 0;
                }
            }
            
            fprintf(fp, "\n  ]");
        }
    }

    fprintf(fp, "\n}\n");
    fclose(fp);
    
    ui_symbol_count = 0; 
}