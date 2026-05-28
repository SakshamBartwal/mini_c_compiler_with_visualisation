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

    ASTNode *temp = list;

    while(temp->next)
        temp = temp->next;

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
        case NODE_PROGRAM:
            printf("PROGRAM");
            break;

        case NODE_BINARY_OP:
            printf("BINARY_OP");
            break;

        case NODE_UNARY_OP:
            printf("UNARY_OP");
            break;

        case NODE_IDENTIFIER:
            printf("IDENTIFIER");
            break;

        case NODE_INT_LITERAL:
            printf("INT_LITERAL");
            break;

        case NODE_FLOAT_LITERAL:
            printf("FLOAT_LITERAL");
            break;

        case NODE_STRING_LITERAL:
            printf("STRING_LITERAL");
            break;

        default:
            printf("UNKNOWN");
    }

    if(node->value)
        printf(" : %s", node->value);

    printf("\n");

    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
    print_ast(node->third, level + 1);

    print_ast(node->next, level);
}