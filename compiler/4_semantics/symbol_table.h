#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H



// Classification tags defining the specific boundary level of a code block scope
typedef enum {

    SCOPE_GLOBAL,
    SCOPE_FUNCTION,
    SCOPE_BLOCK

} ScopeType;



// The individual tracking token structure for a single registered identifier
typedef struct Symbol {

    char *name;               // Name of the identifier (like variable or function name)
    char *data_type;          // The recorded data type (e.g., "int", "void")
    int line_declared;        // Source file line number where this item was found
    
    struct Symbol *next;      // Cross-link pointer to manage collisions inside the same hash map bucket

} Symbol;



// A distinct scope tracking environment containing its own localized hash map lookup table
typedef struct SymbolTable {

    ScopeType type;                  // The type classification of this scope block layer
    Symbol *buckets[211];            // Fixed array slots forming our hash map collision buckets
    
    struct SymbolTable *outer_scope; // Pointer referencing the enclosing parent scope layer back up the tree

} SymbolTable;



/* ============================================================================
   Scope Lifecycle Management
   ============================================================================ */

// Allocates memory and maps an inner local sandbox level back to its parent scope
SymbolTable *create_scope(SymbolTable *parent, ScopeType type);


// Unwinds a completed scope level and frees up its internal hash memory allocations
SymbolTable *destroy_scope(SymbolTable *current);



/* ============================================================================
   Symbol Manipulation Utilities
   ============================================================================ */

// Adds a newly discovered variable or signature entry into the active scope table
int insert_symbol(SymbolTable *table, const char *name, const char *type, int line);


// Looks up an identifier name recursively backwards through all surrounding scope layers
Symbol *lookup_symbol(SymbolTable *table, const char *name);



/* ============================================================================
   UI Visualizer Layer Integration
   ============================================================================ */

// Saves all tracked identifier data snapshots into a flat JSON array for React Flow
void export_symbols_to_json(const char *filename);



#endif