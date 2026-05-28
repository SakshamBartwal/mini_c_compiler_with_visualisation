#ifndef AST_H
#define AST_H

typedef enum
{
    NODE_PROGRAM,
    NODE_FUNCTION_DEF,
    NODE_COMPOUND_STATEMENT,
    NODE_STATEMENT_LIST,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_DECLARATION,
    NODE_ASSIGNMENT,
    NODE_IDENTIFIER,
    NODE_INT_LITERAL,
    NODE_FLOAT_LITERAL,
    NODE_STRING_LITERAL,

    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_RETURN,
    NODE_BREAK,
    NODE_CONTINUE
} NodeType;

typedef struct ASTNode
{
    int id;
    NodeType type;
    char *value;

    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *third;

    struct ASTNode *next; // Strictly handles horizontal sibling sequencing

} ASTNode;

extern ASTNode *root;

ASTNode *create_node(NodeType type, char *value);
ASTNode *append_node(ASTNode *list, ASTNode *node);
void print_ast(ASTNode *node, int level);

#endif