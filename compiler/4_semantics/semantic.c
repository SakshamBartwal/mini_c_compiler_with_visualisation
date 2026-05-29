#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "symbol_table.h"



// The main entry point to kick off the scope and type-checking phase
void analyze_semantics(ASTNode *root) {

    printf("\n=========== Semantic Analysis ===========\n");
    
    // Spin up the base global scope layer where functions and global vars live
    SymbolTable *global_scope = create_scope(NULL, SCOPE_GLOBAL);
    printf("[Semantic] Initialized GLOBAL scope layer.\n");
    
    // Start running our recursive analyzer across the full tree structure
    semantic_walk(root, global_scope);
    
    // Clean up the global scope memory block after we are done
    destroy_scope(global_scope);

    printf("Semantic Analysis Completed Successfully.\n");
}



// The recursive tree walker that inspects scopes and declarations line by line
void semantic_walk(ASTNode *node, SymbolTable *current_scope) {

    if (node == NULL || current_scope == NULL) {
        return;
    }


    switch (node->type) {
        

        case NODE_FUNCTION_DEF: {

            printf("[Semantic] Entering FUNCTION scope context for: %s\n", node->value);
            
            // Register the function name inside our current active scope layer
            insert_symbol(current_scope, node->value, "void", 0);
            
            // Build a completely fresh, isolated local scope dedicated to this function body
            SymbolTable *func_scope = create_scope(current_scope, SCOPE_FUNCTION);
            
            // Head down the right branch first to declare any input parameters inside the function scope
            if (node->right != NULL) {
                semantic_walk(node->right, func_scope);
            }
            
            // Now parse the statement list inside the body using that same function scope
            if (node->left != NULL && node->left->type == NODE_COMPOUND_STATEMENT) {
                if (node->left->left != NULL) {
                    semantic_walk(node->left->left, func_scope);
                }
            }
            
            // Tear down the function scope block once we finish walking through it
            destroy_scope(func_scope);

            printf("[Semantic] Exiting FUNCTION scope context.\n");
            break;
        }


        case NODE_COMPOUND_STATEMENT: {

            printf("[Semantic] Entering nested local BLOCK scope.\n");
            
            // Create a temporary local sandbox scope for standard curly brace blocks { ... }
            SymbolTable *block_scope = create_scope(current_scope, SCOPE_BLOCK);
            
            // Run analysis on everything hiding inside this specific code block
            semantic_walk(node->left, block_scope);
            
            // Drop any variables declared here right away as we exit the braces
            destroy_scope(block_scope);
            
            printf("[Semantic] Exiting nested local BLOCK scope.\n");
            break;
        }


        case NODE_DECLARATION: {

            ASTNode *var = node->left;

            // Travel sideways across any comma-separated variables in this line
            while (var != NULL) {
                char *var_name = NULL;

                if (var->type == NODE_IDENTIFIER) {
                    var_name = var->value;
                } else if (var->type == NODE_ASSIGNMENT) {
                    var_name = var->left->value;
                    // Check the right-side assignment expression for any hidden undeclared variables
                    semantic_walk(var->right, current_scope);
                }

                if (var_name) {
                    // Throw an error and stop if the user tries to declare the same variable name twice here
                    if (!insert_symbol(current_scope, var_name, "int", 0)) {
                        fprintf(stderr, "Semantic Error: Redeclaration of variable '%s' inside same scope level.\n", var_name);
                        exit(1);
                    }
                    
                    // Log the registration clearly based on where it was found
                    if (current_scope->type == SCOPE_GLOBAL) {
                        printf("[Semantic] Registered GLOBAL variable: %s\n", var_name);
                    } else if (current_scope->type == SCOPE_FUNCTION) {
                        printf("[Semantic] Registered FUNCTION local variable: %s\n", var_name);
                    } else {
                        printf("[Semantic] Registered nested BLOCK variable: %s\n", var_name);
                    }
                }

                // Skip over to the next sibling variable in the declaration list
                var = var->next; 
            }

            break;
        }


        case NODE_FOR: {

            printf("[Semantic] Entering FOR loop context.\n");

            // For loops need a distinct block scope to trap loop counter initializations
            SymbolTable *for_scope = create_scope(current_scope, SCOPE_BLOCK);
            
            // Inspect the starter setup, the condition check, and the update steps inside our loop scope
            semantic_walk(node->left, for_scope);
            semantic_walk(node->right, for_scope);
            semantic_walk(node->third, for_scope);
            
            destroy_scope(for_scope);

            printf("[Semantic] Exiting FOR loop context.\n");
            break;
        }


        case NODE_WHILE: {

            printf("[Semantic] Entering WHILE loop context.\n");

            // Check the conditional boundaries first using the scope we are currently sitting in
            semantic_walk(node->left, current_scope);

            // Now dive in and inspect the inner code statements belonging to the loop body
            semantic_walk(node->right, current_scope);
            
            printf("[Semantic] Exiting WHILE loop context.\n");
            break;
        }


        case NODE_IF: {

            // Type check the condition evaluation statements first
            semantic_walk(node->left, current_scope);
            
            // Run analysis across the true block statement pathway
            semantic_walk(node->right, current_scope);
            
            // Hop over and process the alternative else block branch pathway if it exists
            if (node->third != NULL) {
                semantic_walk(node->third, current_scope);
            }

            break;
        }


        case NODE_IDENTIFIER: {

            // Search backward through all parent scope tracking layers to verify this variable actually exists
            Symbol *sym = lookup_symbol(current_scope, node->value);

            if (sym == NULL) {
                fprintf(stderr, "Semantic Error: Variable '%s' used before declaration context was established.\n", node->value);
                exit(1);
            }

            break;
        }


        default:
            // Math operations, constants, and plain paths pass their scope contexts smoothly downwards
            semantic_walk(node->left, current_scope);
            semantic_walk(node->right, current_scope);
            semantic_walk(node->third, current_scope);
            break;
    }


    // Keep running our lateral scan across consecutive sequential statement nodes completely unhindered
    semantic_walk(node->next, current_scope);
}