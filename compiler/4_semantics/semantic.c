#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "symbol_table.h"

/* ============================================================================
   Main Semantic Analyzer Entry Point
   ============================================================================ */

// Kicks off the semantic analysis phase by establishing the root global environment
void analyze_semantics(ASTNode *root) {

    printf("\n=========== Semantic Analysis ===========\n");
    
    // Spin up the base global scope layer where top-level functions and variables live
    SymbolTable *global_scope = create_scope(NULL, SCOPE_GLOBAL);
    printf("[Semantic] Initialized GLOBAL scope layer.\n");
    
    // Start the recursive descent, defaulting the initial tracking context to "Global"
    semantic_walk(root, global_scope, "Global");
    
    // Clean up the global scope memory block after the entire tree is processed
    destroy_scope(global_scope);

    printf("Semantic Analysis Completed Successfully.\n");
}


/* ============================================================================
   Recursive AST Walker
   ============================================================================ */

// Traverses the AST recursively, verifying variable scopes, types, and declarations
void semantic_walk(ASTNode *node, SymbolTable *current_scope, const char *active_func_context) {

    // Base case: Stop if we hit a dead end in the tree or lose our scope context
    if (node == NULL || current_scope == NULL) {
        return;
    }

    switch (node->type) {
        
        // --------------------------------------------------------------------
        // FUNCTION DEFINITIONS
        // --------------------------------------------------------------------
        case NODE_FUNCTION_DEF: {

            printf("[Semantic] Entering FUNCTION scope context for: %s\n", node->value);
            
            // Register the function's signature in the current (usually Global) scope
            insert_symbol(current_scope, node->value, "int", "function", "Global");
            
            // Spin up a fresh, isolated scope layer dedicated to this function's parameters and body
            SymbolTable *func_scope = create_scope(current_scope, SCOPE_FUNCTION);
            
            // Update the tracking string so inner variables know which function they belong to
            const char *new_function_context = node->value;

            // Phase 1: Process Parameters
            // Parameters sit directly on the right branch and belong to the function's top scope
            if (node->right != NULL) {
                semantic_walk(node->right, func_scope, new_function_context);
            }
            
            // Phase 2: Process Function Body
            // We pass the left branch (the body) into the walker. If it's a compound statement { ... },
            // it will naturally trigger a new BLOCK scope for the local variables inside.
            if (node->left != NULL) {
                semantic_walk(node->left, func_scope, new_function_context);
            }
            
            // Tear down the function's scope block now that we are done analyzing it
            destroy_scope(func_scope);

            printf("[Semantic] Exiting FUNCTION scope context.\n");
            break;
        }

        // --------------------------------------------------------------------
        // STANDARD CODE BLOCKS { ... }
        // --------------------------------------------------------------------
        case NODE_COMPOUND_STATEMENT: {

            printf("[Semantic] Entering nested local BLOCK scope.\n");
            
            // Create a temporary local sandbox scope for anything declared inside these specific curly braces
            SymbolTable *block_scope = create_scope(current_scope, SCOPE_BLOCK);
            
            // Run analysis on the block's contents while maintaining our current function string context
            semantic_walk(node->left, block_scope, active_func_context);
            
            // Destroy this local sandbox immediately upon exiting the braces
            destroy_scope(block_scope);
            
            printf("[Semantic] Exiting nested local BLOCK scope.\n");
            break;
        }

        // --------------------------------------------------------------------
        // VARIABLE DECLARATIONS
        // --------------------------------------------------------------------
        case NODE_DECLARATION: {

            ASTNode *var = node->left;

            // Traverse horizontally across any comma-separated variables on this line (e.g., int x, y, z;)
            while (var != NULL) {
                char *var_name = NULL;

                if (var->type == NODE_IDENTIFIER) {
                    var_name = var->value;
                    
                } else if (var->type == NODE_ASSIGNMENT) {
                    var_name = var->left->value;
                    // Check the right side of the assignment for any undeclared variables being used
                    semantic_walk(var->right, current_scope, active_func_context);
                }

                if (var_name) {
                    
                    // Deduce if this is a function parameter or a standard local variable based on the current active scope
                    const char *target_category = (current_scope->type == SCOPE_FUNCTION) ? "parameter" : "variable";
                    
                    // Attempt to register the variable. If it fails, the user tried to declare it twice in the same scope.
                    if (!insert_symbol(current_scope, var_name, "int", target_category, active_func_context)) {
                        fprintf(stderr, "Semantic Error: Redeclaration of variable '%s' inside same scope level.\n", var_name);
                        exit(1);
                    }
                    
                    // Log the successful registration clearly for terminal debugging
                    if (current_scope->type == SCOPE_GLOBAL) {
                        printf("[Semantic] Registered GLOBAL variable: %s\n", var_name);
                    } else if (current_scope->type == SCOPE_FUNCTION) {
                        printf("[Semantic] Registered FUNCTION parameter variable: %s in %s()\n", var_name, active_func_context);
                    } else {
                        printf("[Semantic] Registered local variable: %s inside context (%s)\n", var_name, active_func_context);
                    }
                }

                // Move to the next sibling variable in the declaration chain
                var = var->next; 
            }

            break;
        }

        // --------------------------------------------------------------------
        // LOOPS & CONDITIONALS
        // --------------------------------------------------------------------
        case NODE_FOR: {

            printf("[Semantic] Entering FOR loop context.\n");

            // For loops require their own distinct block scope to trap loop counter initializations (like 'int i = 0')
            SymbolTable *for_scope = create_scope(current_scope, SCOPE_BLOCK);
            
            // Inspect the initialization, condition, and update steps sequentially
            semantic_walk(node->left, for_scope, active_func_context);
            semantic_walk(node->right, for_scope, active_func_context);
            semantic_walk(node->third, for_scope, active_func_context);
            
            destroy_scope(for_scope);

            printf("[Semantic] Exiting FOR loop context.\n");
            break;
        }

        case NODE_WHILE: {

            printf("[Semantic] Entering WHILE loop context.\n");

            // Inspect the conditional logic first, then dive into the loop body
            semantic_walk(node->left, current_scope, active_func_context);
            semantic_walk(node->right, current_scope, active_func_context);
            
            printf("[Semantic] Exiting WHILE loop context.\n");
            break;
        }

        case NODE_IF: {

            // Type check the condition evaluation
            semantic_walk(node->left, current_scope, active_func_context);
            
            // Traverse the 'true' block statement pathway
            semantic_walk(node->right, current_scope, active_func_context);
            
            // If an 'else' block exists (third branch), traverse that pathway as well
            if (node->third != NULL) {
                semantic_walk(node->third, current_scope, active_func_context);
            }

            break;
        }

        // --------------------------------------------------------------------
        // IDENTIFIER USAGE
        // --------------------------------------------------------------------
        case NODE_IDENTIFIER: {

            // When a variable is used, search backward through all parent scopes to ensure it exists
            Symbol *sym = lookup_symbol(current_scope, node->value);

            if (sym == NULL) {
                fprintf(stderr, "Semantic Error: Variable '%s' used before declaration context was established.\n", node->value);
                exit(1);
            }

            break;
        }

        // --------------------------------------------------------------------
        // DEFAULT FALLTHROUGH
        // --------------------------------------------------------------------
        default:
            // For general math operations, constants, and structure nodes, simply pass the scope context smoothly downwards
            semantic_walk(node->left, current_scope, active_func_context);
            semantic_walk(node->right, current_scope, active_func_context);
            semantic_walk(node->third, current_scope, active_func_context);
            break;
    }

    // Keep running our lateral scan across consecutive sequential statement nodes completely unhindered
    semantic_walk(node->next, current_scope, active_func_context);
}