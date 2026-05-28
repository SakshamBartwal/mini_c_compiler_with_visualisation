#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static int node_counter = 0;
ASTNode *root = NULL;

ASTNode *create_node(NodeType type, char *value)
{
    ASTNode *node = malloc(sizeof(ASTNode));

    if(node == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    node->id = ++node_counter;
    node->type = type;

    if(value)
        node->value = strdup(value);
    else
        node->value = NULL;

    node->left = NULL;
    node->right = NULL;
    node->third = NULL;
    node->next = NULL;

    return node;
}

ASTNode *append_node(ASTNode *list, ASTNode *node)
{
    if(list == NULL)
        return node;

    if(node == NULL)
        return list;

    ASTNode *temp = list;

    /* Safely travel down the horizontal line of siblings via .next only */
    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = node;
    return list;
}

void print_ast(ASTNode *node, int level)
{
    if(node == NULL)
        return;

    for(int i = 0; i < level; i++)
        printf("    ");

    printf("[%d] ", node->id);

    switch(node->type)
    {
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

    if(node->value)
        printf(" : %s", node->value);

    printf("\n");

    /* Print internal children blocks deeper down the hierarchy */
    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
    print_ast(node->third, level + 1);

    /* Print consecutive structural siblings at the same layout indentation level */
    print_ast(node->next, level);
}