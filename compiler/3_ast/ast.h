#ifndef AST_H
#define AST_H

typedef enum
{
    NODE_PROGRAM,

    NODE_BINARY_OP,
    NODE_UNARY_OP,

    NODE_DECLARATION,
    NODE_DECLARATOR_LIST,
    NODE_ASSIGNMENT,

    NODE_IDENTIFIER,

    NODE_INT_LITERAL,
    NODE_FLOAT_LITERAL,
    NODE_STRING_LITERAL

} NodeType;

typedef struct ASTNode
{
    int id;

    NodeType type;

    char *value;

    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *third;

    struct ASTNode *next;

} ASTNode;

extern ASTNode *root;

ASTNode *create_node(NodeType type, char *value);

ASTNode *append_node(ASTNode *list, ASTNode *node);

void print_ast(ASTNode *node, int level);


#endif