#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static int node_counter = 0;
ASTNode *root = NULL;



// Allocates memory and configures default tracking attributes for a single node
ASTNode *create_node(NodeType type, char *value) {

    ASTNode *node = malloc(sizeof(ASTNode));

    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    node->id = ++node_counter;
    node->type = type;

    if (value) {
        node->value = strdup(value);
    } else {
        node->value = NULL;
    }

    // Explicitly zero out all relational child and sibling pointers
    node->left  = NULL;
    node->right = NULL;
    node->third = NULL;
    node->next  = NULL;

    return node;
}



// Travels to the end of a horizontal statement list and appends a new code node
ASTNode *append_node(ASTNode *list, ASTNode *node) {

    if (list == NULL) {
        return node;
    }

    if (node == NULL) {
        return list;
    }

    ASTNode *temp = list;

    // Follow the sequential chain of statement siblings via the next pointer
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Attach the new block onto the absolute end of the horizontal timeline
    temp->next = node;
    
    return list;
}



// Debug tool to print a clean text version of your abstract syntax tree to logs
void print_ast(ASTNode *node, int level) {

    if (node == NULL) {
        return;
    }

    // Indent dynamically using spaces based on how deep we are in the hierarchy
    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    printf("[%d] ", node->id);


    switch (node->type) {
        case NODE_PROGRAM:            printf("PROGRAM"); break;
        case NODE_FUNCTION_DEF:       printf("FUNCTION_DEF"); break;
        case NODE_COMPOUND_STATEMENT: printf("COMPOUND_STATEMENT"); break;
        case NODE_BINARY_OP:          printf("BINARY_OP"); break;
        case NODE_UNARY_OP:           printf("UNARY_OP"); break;
        case NODE_DECLARATION:        printf("DECLARATION"); break;
        case NODE_ASSIGNMENT:         printf("ASSIGNMENT"); break;
        case NODE_IDENTIFIER:         printf("IDENTIFIER"); break;
        case NODE_INT_LITERAL:        printf("INT_LITERAL"); break;
        case NODE_FLOAT_LITERAL:      printf("FLOAT_LITERAL"); break;
        case NODE_STRING_LITERAL:     printf("STRING_LITERAL"); break;
        case NODE_IF:                 printf("IF"); break;
        case NODE_WHILE:              printf("WHILE"); break;
        case NODE_FOR:                printf("FOR"); break;
        case NODE_RETURN:             printf("RETURN"); break;
        case NODE_BREAK:              printf("BREAK"); break;
        case NODE_CONTINUE:           printf("CONTINUE"); break;    
        default:                      printf("UNKNOWN");
    }


    if (node->value) {
        printf(" : %s", node->value);
    }

    printf("\n");


    // 1. Traverse down into nested internal scoping layers first
    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
    print_ast(node->third, level + 1);

    // 2. Step laterally into chronological code statements resting at the same layout level
    print_ast(node->next, level);
}



// Serializes the full operational memory tree into a flat string pattern for React Flow
void write_ast_json_node(FILE *fp, ASTNode *node, int *id_counter) {

    if (!node) {
        fprintf(fp, "null");
        return;
    }
    
    int current_id = (*id_counter)++;
    
    // Print the basic identification attributes of the target node block
    fprintf(fp, "{\"id\": %d, \"type\": \"AST_NODE\", \"value\": \"%s\", \"left\": ", 
            current_id, node->value ? node->value : "unknown");
            
    // Recursively handle the primary left sub-expression
    write_ast_json_node(fp, node->left, id_counter);
    
    fprintf(fp, ", \"right\": ");
    // Recursively handle the secondary right sub-expression
    write_ast_json_node(fp, node->right, id_counter);
    
    fprintf(fp, ", \"third\": ");
    // Recursively handle complex control elements (loops, branches, adjustments)
    write_ast_json_node(fp, node->third, id_counter);
    
    fprintf(fp, ", \"next\": ");
    // Recursively process subsequent sequential lines within the statement sequence
    write_ast_json_node(fp, node->next, id_counter);
    
    fprintf(fp, "}");
}



// Entry point used by main.c to safely store the structural graph data onto your hard drive
void export_ast_to_json(ASTNode *root_node, const char *filename) {

    FILE *fp = fopen(filename, "w");

    if (!fp) {
        printf("Error: Could not open %s for writing.\n", filename);
        return;
    }

    int id = 1;
    
    // Kick off our nested structural JSON walker
    write_ast_json_node(fp, root_node, &id);
    
    fclose(fp);
}