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

%type <node> expression
%type <node> assignment_expression
%type <node> conditional_expression
%type <node> logical_or_expression
%type <node> logical_and_expression
%type <node> equality_expression
%type <node> relational_expression
%type <node> additive_expression
%type <node> multiplicative_expression
%type <node> unary_expression
%type <node> postfix_expression
%type <node> primary_expression

%%

program:
      program external_declaration
    |
    ;

external_declaration:
      function_definition
    | function_declaration
    | declaration
    | import_statement
    ;

import_statement:
      IMPORT STRING_LITERAL ';'
    ;

function_definition:
      type_specifier declarator '(' parameter_list ')' compound_statement
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

declaration:
      type_specifier variable_list ';'
    ;

variable_list:
      variable_list ',' declarator
    | variable_list ',' initialized_declarator
    | declarator
    | initialized_declarator
    ;

initialized_declarator:
      declarator '=' expression
    ;

declarator:
      IDENTIFIER
    | '*' declarator
    | declarator '[' INT_LITERAL ']'
    ;

compound_statement:
      '{' statement_list '}'
    ;

statement_list:
      statement_list statement
    |
    ;

statement:
      declaration
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    | compound_statement
    ;

expression_statement:
      expression ';'
    | ';'
    ;

selection_statement:
      IF '(' expression ')' statement %prec LOWER_THAN_ELSE
    | IF '(' expression ')' statement ELSE statement
    | SWITCH '(' expression ')' '{' case_list '}'
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
    | DO statement WHILE '(' expression ')' ';'
    | FOR '(' for_init_statement expression_statement optional_expression ')' statement
    ;

for_init_statement:
      declaration
    | expression_statement
    ;

optional_expression:
      expression
    |
    ;

jump_statement:
      RETURN expression ';'
    | RETURN ';'
    | BREAK ';'
    | CONTINUE ';'
    ;

expression:
      expression ',' assignment_expression
      {
          $$ = NULL;
      }

    | assignment_expression
      {
          $$ = $1;

          root = $$;
      }
    ;

assignment_expression:
      unary_expression '=' assignment_expression
      {
          $$ = NULL;
      }

    | unary_expression ADD_ASSIGN assignment_expression
      {
          $$ = NULL;
      }

    | unary_expression SUB_ASSIGN assignment_expression
      {
          $$ = NULL;
      }

    | unary_expression MUL_ASSIGN assignment_expression
      {
          $$ = NULL;
      }

    | unary_expression DIV_ASSIGN assignment_expression
      {
          $$ = NULL;
      }

    | conditional_expression
      {
          $$ = $1;
      }
    ;

conditional_expression:
      logical_or_expression
      {
          $$ = $1;
      }

    | logical_or_expression '?' expression ':' conditional_expression
      {
          $$ = NULL;
      }
    ;

logical_or_expression:
      logical_or_expression OR logical_and_expression
      {
          $$ = NULL;
      }

    | logical_and_expression
      {
          $$ = $1;
      }
    ;

logical_and_expression:
      logical_and_expression AND equality_expression
      {
          $$ = NULL;
      }

    | equality_expression
      {
          $$ = $1;
      }
    ;

equality_expression:
      equality_expression EQ relational_expression
      {
          $$ = NULL;
      }

    | equality_expression NEQ relational_expression
      {
          $$ = NULL;
      }

    | relational_expression
      {
          $$ = $1;
      }
    ;

relational_expression:
      relational_expression '<' additive_expression
      {
          $$ = NULL;
      }

    | relational_expression '>' additive_expression
      {
          $$ = NULL;
      }

    | relational_expression LE additive_expression
      {
          $$ = NULL;
      }

    | relational_expression GE additive_expression
      {
          $$ = NULL;
      }

    | additive_expression
      {
          $$ = $1;
      }
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
      postfix_expression
      {
          $$ = $1;
      }

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
      primary_expression
      {
          $$ = $1;
      }

    | postfix_expression '[' expression ']'
      {
          $$ = NULL;
      }

    | postfix_expression '(' argument_list_opt ')'
      {
          $$ = NULL;
      }

    | postfix_expression INC
      {
          $$ = NULL;
      }

    | postfix_expression DEC
      {
          $$ = NULL;
      }
    ;

primary_expression:
      IDENTIFIER
      {
          $$ = create_node(NODE_IDENTIFIER, $1);
      }

    | STRING_LITERAL
      {
          $$ = create_node(NODE_STRING_LITERAL, $1);
      }

    | INT_LITERAL
      {
          $$ = create_node(NODE_INT_LITERAL, $1);
      }

    | FLOAT_LITERAL
      {
          $$ = create_node(NODE_FLOAT_LITERAL, $1);
      }

    | '(' expression ')'
      {
          $$ = $2;
      }
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
      INT
    | FLOAT
    | CHAR
    | VOID
    | DOUBLE
    | LONG
    | SHORT
    | SIGNED
    | UNSIGNED
    ;

%%

void yyerror(const char *s)
{
    fprintf(
        stderr,
        "Parser Error: %s at line %d\n",
        s,
        line_num
    );
}