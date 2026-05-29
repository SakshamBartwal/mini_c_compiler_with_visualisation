#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "symbol_table.h"

void analyze_semantics(ASTNode *root) {
    printf("\n=========== Semantic Analysis ===========\n");
    
    /* Initialize the top-level GLOBAL scope */
    SymbolTable *global_scope = create_scope(NULL, SCOPE_GLOBAL);
    printf("[Semantic] Initialized GLOBAL scope layer.\n");
    
    /* Fire up your recursive visitor walk across your flat sibling tree elements */
    semantic_walk(root, global_scope);
    
    destroy_scope(global_scope);
    printf("Semantic Analysis Completed Successfully.\n");
}

void semantic_walk(ASTNode *node, SymbolTable *current_scope) {
    if (node == NULL || current_scope == NULL) return;

    switch (node->type) {
        
        case NODE_FUNCTION_DEF: {
            printf("[Semantic] Entering FUNCTION scope context for: %s\n", node->value);
            
            /* 1. Register the function signature name globally */
            insert_symbol(current_scope, node->value, "void", 0);
            
            /* 2. Create a local scope layer dedicated to this function frame */
            SymbolTable *func_scope = create_scope(current_scope, SCOPE_FUNCTION);
            
            /* 3. Walk the parameters subtree (node->right) to populate the function scope directly */
            if (node->right != NULL) {
                semantic_walk(node->right, func_scope);
            }
            
            /* 4. Process the body compound block statement contents directly *without* calling */
            /* semantic_walk(node->left) directly, which would create a redundant block scope layer. */
            if (node->left != NULL && node->left->type == NODE_COMPOUND_STATEMENT) {
                /* Walk the internal statement lists of the body block using the frame scope context directly */
                if (node->left->left != NULL) {
                    semantic_walk(node->left->left, func_scope);
                }
            }
            
            destroy_scope(func_scope);
            printf("[Semantic] Exiting FUNCTION scope context.\n");
            break;
        }

        case NODE_COMPOUND_STATEMENT: {
            printf("[Semantic] Entering nested local BLOCK scope.\n");
            
            /* Dynamically spin up a brand new scope level for this block */
            SymbolTable *block_scope = create_scope(current_scope, SCOPE_BLOCK);
            
            /* Walk the contents of the block using our clean sandbox */
            semantic_walk(node->left, block_scope);
            
            /* Destroy the table to automatically drop inner block variables */
            destroy_scope(block_scope);
            
            printf("[Semantic] Exiting nested local BLOCK scope.\n");
            break;
        }

        case NODE_DECLARATION: {
            ASTNode *var = node->left;
            while (var != NULL) {
                char *var_name = NULL;

                if (var->type == NODE_IDENTIFIER) {
                    var_name = var->value;
                } else if (var->type == NODE_ASSIGNMENT) {
                    var_name = var->left->value;
                    /* Check the initialization calculation subtree for undeclared variables */
                    semantic_walk(var->right, current_scope);
                }

                if (var_name) {
                    if (!insert_symbol(current_scope, var_name, "int", 0)) {
                        fprintf(stderr, "Semantic Error: Redeclaration of variable '%s' inside same scope level.\n", var_name);
                        exit(1);
                    }
                    
                    /* Clean classification reporting for logs */
                    if (current_scope->type == SCOPE_GLOBAL)
                        printf("[Semantic] Registered GLOBAL variable: %s\n", var_name);
                    else if (current_scope->type == SCOPE_FUNCTION)
                        printf("[Semantic] Registered FUNCTION local variable: %s\n", var_name);
                    else
                        printf("[Semantic] Registered nested BLOCK variable: %s\n", var_name);
                }
                var = var->next; /* Step across declaration siblings */
            }
            break;
        }

        case NODE_FOR: {
            printf("[Semantic] Entering FOR loop context.\n");
            /* A 'for' loop has its own initialization block scope */
            SymbolTable *for_scope = create_scope(current_scope, SCOPE_BLOCK);
            
            /* Process loop initializations, conditions, and increments inside the new scope */
            semantic_walk(node->left, for_scope);
            semantic_walk(node->right, for_scope);
            semantic_walk(node->third, for_scope);
            
            destroy_scope(for_scope);
            printf("[Semantic] Exiting FOR loop context.\n");
            break;
        }

        case NODE_WHILE: {
            printf("[Semantic] Entering WHILE loop context.\n");
            /* Condition is evaluated in current scope, but body should be treated cleanly */
            semantic_walk(node->left, current_scope);
            semantic_walk(node->right, current_scope);
            
            printf("[Semantic] Exiting WHILE loop context.\n");
            break;
        }

        case NODE_IF: {
            /* Evaluate structural condition expressions first */
            semantic_walk(node->left, current_scope);
            
            /* Walk the true block branch statement */
            semantic_walk(node->right, current_scope);
            
            /* Walk the optional else block branch statement if it exists */
            if (node->third != NULL) {
                semantic_walk(node->third, current_scope);
            }
            break;
        }

        case NODE_IDENTIFIER: {
            Symbol *sym = lookup_symbol(current_scope, node->value);
            if (sym == NULL) {
                fprintf(stderr, "Semantic Error: Variable '%s' used before declaration context was established.\n", node->value);
                exit(1);
            }
            break;
        }

        default:
            /* Standard math operators or branches pass contexts down smoothly to sub-trees */
            semantic_walk(node->left, current_scope);
            semantic_walk(node->right, current_scope);
            semantic_walk(node->third, current_scope);
            break;
    }

    /* FIXED: Process horizontal timelines unconditionally for all sibling blocks globally */
    semantic_walk(node->next, current_scope);
}