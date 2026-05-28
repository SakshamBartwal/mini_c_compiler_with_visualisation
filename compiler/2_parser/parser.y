%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler/3_ast/ast.h"

extern char current_file[100];
extern int yylex();
extern int line_num;

void yyerror(const char *s);
%}

%union {
    char* sval;
    ASTNode *node;
}

%token IMPORT
%token INT FLOAT CHAR VOID DOUBLE LONG SHORT SIGNED UNSIGNED
%token IF ELSE
%token WHILE FOR DO
%token RETURN
%token SWITCH CASE DEFAULT
%token BREAK CONTINUE
%token EQ NEQ LE GE
%token AND OR
%token INC DEC
%token SIZEOF
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN

%token <sval> INT_LITERAL
%token <sval> FLOAT_LITERAL
%token <sval> STRING_LITERAL
%token <sval> IDENTIFIER

%right '='
%right UMINUS

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

/* Map ONLY your implemented non-terminals to ASTNode pointers */
%type <node> expression assignment_expression conditional_expression
%type <node> logical_or_expression logical_and_expression equality_expression
%type <node> relational_expression additive_expression multiplicative_expression
%type <node> unary_expression postfix_expression primary_expression
%type <node> declaration variable_list initialized_declarator declarator
%type <node> expression_statement statement compound_statement statement_list
%type <node> program external_declaration
%type <node> function_definition
%type <node> selection_statement
%type <node> iteration_statement
%type <node> jump_statement
%type <node> for_init_statement
%type <node> optional_expression

%%

/* --- Global Program Backbone Chains --- */
program:
      program external_declaration
      {
          $$ = append_node($1, $2);
          root = $$;
      }
    | external_declaration
      {
          $$ = $1;
          if($1 != NULL) root = $1;
      }
    ;

external_declaration:
      function_definition   { $$ = $1; }
    | function_declaration  { $$ = NULL; }
    | declaration           { $$ = $1; }
    | import_statement      { $$ = NULL; }
    | compound_statement    { $$ = $1; }
    ;

import_statement:
      IMPORT STRING_LITERAL ';'
    ;

function_definition:
      type_specifier declarator '(' parameter_list ')' compound_statement
      {
          $$ = create_node(NODE_FUNCTION_DEF, $2->value); 
          
          $$->left = $6; 
      }
    ;

function_declaration:
      type_specifier declarator '(' parameter_list ')' ';'
    ;

parameter_list:
      parameter_list ',' parameter
    | parameter
    |
    ;

parameter:
      type_specifier declarator
    ;

/* --- Variable Declarations (Flat Sibling Chains) --- */
declaration:
      type_specifier variable_list ';'
      {
          $$ = create_node(NODE_DECLARATION, "declaration");
          $$->left = $2; // Points directly to the first variable node in the flat chain
      }
    ;
    
variable_list:
      variable_list ',' declarator
      {
          $$ = append_node($1, $3);
      }
    | variable_list ',' initialized_declarator
      {
          $$ = append_node($1, $3);
      }
    | declarator
      {
          $$ = $1; // Passes raw leaf straight up (No intermediate list wrappers)
      }
    | initialized_declarator
      {
          $$ = $1; // Passes assignment sub-tree root straight up
      }
    ;

initialized_declarator:
      declarator '=' assignment_expression
      {
          $$ = create_node(NODE_ASSIGNMENT, "=");
          $$->left = $1;
          $$->right = $3;
      }
    ;

declarator:
      IDENTIFIER
      {
          $$ = create_node(NODE_IDENTIFIER, $1);
      }
    | '*' declarator
      {
          $$ = create_node(NODE_UNARY_OP, "*");
          $$->left = $2;
      }
    | declarator '[' INT_LITERAL ']'
      {
          $$ = $1;
      }
    ;

/* --- Compound Blocks & Statement Sequencing --- */
compound_statement:
      '{' '}'
      {
          $$ = create_node(NODE_COMPOUND_STATEMENT, "compound_statement");
      }
    | '{' statement_list '}'
      {
          $$ = create_node(NODE_COMPOUND_STATEMENT, "compound_statement");
          /* FIXED: $1 is '{', $2 is the actual statement_list node chain, $3 is '}' */
          $$->left = $2; 
      }
    ;

statement_list:
      statement
      {
          /* If the statement is an empty semicolon, pass NULL.
             Otherwise, this statement becomes the head of the chain. */
          $$ = $1; 
      }
    | statement_list statement
      {
          if ($1 == NULL) {
              /* If everything before was empty, this new statement 
                 becomes the new head of the list */
              $$ = $2;
          } else {
              if ($2 != NULL) {
                  append_node($1, $2);
              }
              $$ = $1;
          }
      }
    ;

statement:
      declaration           { $$ = $1; }
    | expression_statement  { $$ = $1; }
    | selection_statement   { $$ = $1; }
    | iteration_statement   { $$ = $1; }
    | jump_statement        { $$ = $1; }
    | compound_statement    { $$ = $1; }
    ;

expression_statement:
      expression ';'        { $$ = $1; }
    | ';'                   { $$ = NULL; }
    ;

selection_statement:
      IF '(' expression ')' statement %prec LOWER_THAN_ELSE
      {
          $$ = create_node(NODE_IF, "if");
          $$->left = $3;   /* Condition expression */
          $$->right = $5;  /* Body statement */
      }
    | IF '(' expression ')' statement ELSE statement
      {
          $$ = create_node(NODE_IF, "if_else");
          $$->left = $3;   /* Condition expression */
          $$->right = $5;  /* Then block statement */
          $$->third = $7;  /* Else block statement */
      }
    | SWITCH '(' expression ')' '{' case_list '}' { $$ = NULL; }
    ;

case_list:
      case_list case_statement
    | case_statement
    ;

case_statement:
      CASE constant_expression ':' statement_list
    | DEFAULT ':' statement_list
    ;

constant_expression:
      INT_LITERAL
    | FLOAT_LITERAL
    | STRING_LITERAL
    ;

iteration_statement:
      WHILE '(' expression ')' statement
      {
          $$ = create_node(NODE_WHILE, "while");
          $$->left = $3;   /* Condition expression */
          $$->right = $5;  /* Loop body statement */
      }
    | DO statement WHILE '(' expression ')' ';' { $$ = NULL; }
    | FOR '(' for_init_statement expression_statement optional_expression ')' statement
      {
          $$ = create_node(NODE_FOR, "for");
          $$->left = $3;   /* Initialization statement */
          $$->right = $4;  /* Condition statement */
          
          /* Append the update expression step ($5) directly to the tail
             of the loop body statement block ($7) using your flat append system */
          if($5 != NULL) {
              append_node($7, $5);
          }
          $$->third = $7;  /* Unified loop body root */
      }
    ;

for_init_statement:
      declaration           { $$ = $1; }
    | expression_statement  { $$ = $1; }
    ;

optional_expression:
      expression            { $$ = $1; }
    |                       { $$ = NULL; } /* Handle empty increment case safely */
    ;

jump_statement:
      RETURN expression ';'
      {
          $$ = create_node(NODE_RETURN, "return");
          $$->left = $2;
      }
    | RETURN ';'
      {
          $$ = create_node(NODE_RETURN, "return");
      }
    | BREAK ';'
      {
          $$ = create_node(NODE_BREAK, "break");
      }
    | CONTINUE ';'
      {
          $$ = create_node(NODE_CONTINUE, "continue");
      }
    ;

/* --- Core Expressions & Math Operators --- */
expression:
      expression ',' assignment_expression
      {
          $$ = $3;
      }
    | assignment_expression
      {
          $$ = $1;
      }
    ;

assignment_expression:
      unary_expression '=' assignment_expression
      {
          $$ = create_node(NODE_ASSIGNMENT, "=");
          $$->left = $1;
          $$->right = $3;
      }
    | unary_expression ADD_ASSIGN assignment_expression { $$ = NULL; }
    | unary_expression SUB_ASSIGN assignment_expression { $$ = NULL; }
    | unary_expression MUL_ASSIGN assignment_expression { $$ = NULL; }
    | unary_expression DIV_ASSIGN assignment_expression { $$ = NULL; }
    | conditional_expression
      {
          $$ = $1;
      }
    ;

conditional_expression:
      logical_or_expression   { $$ = $1; }
    | logical_or_expression '?' expression ':' conditional_expression { $$ = NULL; }
    ;

logical_or_expression:
      logical_or_expression OR logical_and_expression { $$ = NULL; }
    | logical_and_expression { $$ = $1; }
    ;

logical_and_expression:
      logical_and_expression AND equality_expression { $$ = NULL; }
    | equality_expression { $$ = $1; }
    ;

equality_expression:
      equality_expression EQ relational_expression
      {
          $$ = create_node(NODE_BINARY_OP, "==");
          $$->left = $1;
          $$->right = $3;
      }
    | equality_expression NEQ relational_expression
      {
          $$ = create_node(NODE_BINARY_OP, "!=");
          $$->left = $1;
          $$->right = $3;
      }
    | relational_expression { $$ = $1; }
    ;

relational_expression:
      relational_expression '<' additive_expression
      {
          $$ = create_node(NODE_BINARY_OP, "<");
          $$->left = $1;
          $$->right = $3;
      }
    | relational_expression '>' additive_expression
      {
          $$ = create_node(NODE_BINARY_OP, ">");
          $$->left = $1;
          $$->right = $3;
      }
    | relational_expression LE additive_expression
      {
          $$ = create_node(NODE_BINARY_OP, "<=");
          $$->left = $1;
          $$->right = $3;
      }
    | relational_expression GE additive_expression
      {
          $$ = create_node(NODE_BINARY_OP, ">=");
          $$->left = $1;
          $$->right = $3;
      }
    | additive_expression { $$ = $1; }
    ;

additive_expression:
      additive_expression '+' multiplicative_expression
      {
          $$ = create_node(NODE_BINARY_OP, "+");
          $$->left = $1;
          $$->right = $3;
      }
    | additive_expression '-' multiplicative_expression
      {
          $$ = create_node(NODE_BINARY_OP, "-");
          $$->left = $1;
          $$->right = $3;
      }
    | multiplicative_expression
      {
          $$ = $1;
      }
    ;

multiplicative_expression:
      multiplicative_expression '*' unary_expression
      {
          $$ = create_node(NODE_BINARY_OP, "*");
          $$->left = $1;
          $$->right = $3;
      }
    | multiplicative_expression '/' unary_expression
      {
          $$ = create_node(NODE_BINARY_OP, "/");
          $$->left = $1;
          $$->right = $3;
      }
    | multiplicative_expression '%' unary_expression
      {
          $$ = create_node(NODE_BINARY_OP, "%");
          $$->left = $1;
          $$->right = $3;
      }
    | unary_expression
      {
          $$ = $1;
      }
    ;

unary_expression:
      postfix_expression { $$ = $1; }
    | INC unary_expression
      {
          $$ = create_node(NODE_UNARY_OP, "++");
          $$->left = $2;
      }
    | DEC unary_expression
      {
          $$ = create_node(NODE_UNARY_OP, "--");
          $$->left = $2;
      }
    | '&' unary_expression
      {
          $$ = create_node(NODE_UNARY_OP, "&");
          $$->left = $2;
      }
    | '*' unary_expression
      {
          $$ = create_node(NODE_UNARY_OP, "*");
          $$->left = $2;
      }
    | '-' unary_expression %prec UMINUS
      {
          $$ = create_node(NODE_UNARY_OP, "-");
          $$->left = $2;
      }
    | '!' unary_expression
      {
          $$ = create_node(NODE_UNARY_OP, "!");
          $$->left = $2;
      }
    | SIZEOF unary_expression
      {
          $$ = create_node(NODE_UNARY_OP, "sizeof");
          $$->left = $2;
      }
    | '(' type_specifier ')' unary_expression
      {
          $$ = create_node(NODE_UNARY_OP, "cast");
          $$->left = $4;
      }
    ;

postfix_expression:
      primary_expression { $$ = $1; }
    | postfix_expression '[' expression ']' { $$ = NULL; }
    | postfix_expression '(' argument_list_opt ')' { $$ = NULL; }
    | postfix_expression INC { $$ = NULL; }
    | postfix_expression DEC { $$ = NULL; }
    ;

primary_expression:
      IDENTIFIER         { $$ = create_node(NODE_IDENTIFIER, $1); }
    | STRING_LITERAL     { $$ = create_node(NODE_STRING_LITERAL, $1); }
    | INT_LITERAL        { $$ = create_node(NODE_INT_LITERAL, $1); }
    | FLOAT_LITERAL      { $$ = create_node(NODE_FLOAT_LITERAL, $1); }
    | '(' expression ')' { $$ = $2; }
    ;

argument_list_opt:
      argument_list
    |
    ;

argument_list:
      argument_list ',' expression
    | expression
    ;

type_specifier:
      INT | FLOAT | CHAR | VOID | DOUBLE | LONG | SHORT | SIGNED | UNSIGNED
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s at line %d\n", s, line_num);
}