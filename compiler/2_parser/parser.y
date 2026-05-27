%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char current_file[100];

extern int yylex();
extern int line_num;

void yyerror(const char *s);
%}

%union {
    int ival;
    float fval;
    char* sval;
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

%token <ival> INT_LITERAL
%token <fval> FLOAT_LITERAL
%token <sval> STRING_LITERAL
%token <sval> IDENTIFIER



%right '='
%right UMINUS

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

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
    | assignment_expression
    ;

assignment_expression:
      unary_expression '=' assignment_expression
    | unary_expression ADD_ASSIGN assignment_expression
    | unary_expression SUB_ASSIGN assignment_expression
    | unary_expression MUL_ASSIGN assignment_expression
    | unary_expression DIV_ASSIGN assignment_expression
    | conditional_expression
    ;

conditional_expression:
      logical_or_expression
    | logical_or_expression '?' expression ':' conditional_expression
    ;

logical_or_expression:
      logical_or_expression OR logical_and_expression
    | logical_and_expression
    ;

logical_and_expression:
      logical_and_expression AND equality_expression
    | equality_expression
    ;

equality_expression:
      equality_expression EQ relational_expression
    | equality_expression NEQ relational_expression
    | relational_expression
    ;

relational_expression:
      relational_expression '<' additive_expression
    | relational_expression '>' additive_expression
    | relational_expression LE additive_expression
    | relational_expression GE additive_expression
    | additive_expression
    ;

additive_expression:
      additive_expression '+' multiplicative_expression
    | additive_expression '-' multiplicative_expression
    | multiplicative_expression
    ;

multiplicative_expression:
      multiplicative_expression '*' unary_expression
    | multiplicative_expression '/' unary_expression
    | multiplicative_expression '%' unary_expression
    | unary_expression
    ;

unary_expression:
      postfix_expression
    | INC unary_expression
    | DEC unary_expression
    | '&' unary_expression
    | '*' unary_expression
    | '-' unary_expression %prec UMINUS
    | '!' unary_expression
    | SIZEOF unary_expression
    | '(' type_specifier ')' unary_expression
    ;

postfix_expression:
      primary_expression
    | postfix_expression '[' expression ']'
    | postfix_expression '(' argument_list_opt ')'
    | postfix_expression INC
    | postfix_expression DEC
    ;

primary_expression:
      IDENTIFIER
    | STRING_LITERAL
    | INT_LITERAL
    | FLOAT_LITERAL
    | '(' expression ')'
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

void yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s at line %d\n", s, line_num);
}