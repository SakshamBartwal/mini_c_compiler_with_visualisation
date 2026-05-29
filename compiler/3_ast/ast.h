#ifndef AST_H
#define AST_H

// Classification tags representing every grammatical structure our C compiler can recognize
typedef enum {

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



// The core building block structure for our Abstract Syntax Tree graph
typedef struct ASTNode {

    int id;                // Unique ID used by React Flow to track nodes on the UI canvas
    NodeType type;         // The enum classification tag for this node
    char *value;           // The literal text value (like variable names, numbers, or operators)

    // Vertical down-pointers to handle nested sub-expressions and inner blocks
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *third; // Dedicated slot for complex control flow structures like 'for' loop statements

    // Horizontal cross-pointer to link consecutive lines of code together inside a block
    struct ASTNode *next; 

} ASTNode;



// Global anchor pointing to the very top entry point of your compiled program tree
extern ASTNode *root;



/* ============================================================================
   Engine Interface Modules
   ============================================================================ */

// Allocates memory and sets up default parameters for a brand new node block
ASTNode *create_node(NodeType type, char *value);


// Chains code statements together horizontally in chronological order using the next pointer
ASTNode *append_node(ASTNode *list, ASTNode *node);


// Debug tool to print out a visual text outline of the tree structure into your terminal logs
void print_ast(ASTNode *node, int level);


// Serializes the structural memory graph into a JSON file to feed the React UI canvas
void export_ast_to_json(ASTNode *root, const char *filename);



#endif