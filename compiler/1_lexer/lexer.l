%{
#include "parser.tab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_num = 1;

extern char current_file[100];
%}

%x COMMENT
%option noyywrap

DIGIT          [0-9]
LETTER         [a-zA-Z_]
ID             {LETTER}({LETTER}|{DIGIT})*

NUMBER         {DIGIT}+
FLOATNUM       {DIGIT}+\.{DIGIT}+

STRING         \"([^\\\"]|\\.)*\"

%%

 /*|=========================================================|
   |                      KEYWORDS                           |
   |=========================================================| */

"import"               { return IMPORT; }

"int"                  { return INT; }
"float"                { return FLOAT; }
"char"                 { return CHAR; }
"void"                 { return VOID; }

"double"               { return DOUBLE; }

"long"                 { return LONG; }
"short"                { return SHORT; }
"signed"               { return SIGNED; }
"unsigned"             { return UNSIGNED; }

"if"                   { return IF; }
"else"                 { return ELSE; }

"while"                { return WHILE; }
"for"                  { return FOR; }
"do"                   { return DO; }

"return"               { return RETURN; }

"switch"               { return SWITCH; }
"case"                 { return CASE; }
"default"              { return DEFAULT; }

"break"                { return BREAK; }
"continue"             { return CONTINUE; }

"sizeof"               { return SIZEOF; }


  /*|=========================================================|
    |                     MULTI-CHAR OPERATORS                |
    |---------------------------------------------------------|
    |           IMPORTANT:                                    |
    |             Must appear BEFORE single-char operators    |
    |=========================================================| */



"=="                   { return EQ; }
"!="                   { return NEQ; }

"<="                   { return LE; }
">="                   { return GE; }

"&&"                   { return AND; }
"||"                   { return OR; }

"++"                   { return INC; }
"--"                   { return DEC; }

"+="                   { return ADD_ASSIGN; }
"-="                   { return SUB_ASSIGN; }
"*="                   { return MUL_ASSIGN; }
"/="                   { return DIV_ASSIGN; }



 /*|=========================================================|
   |                        LITERALS                         |
   |=========================================================|*/
                  /* FLOAT must come BEFORE INT */

{FLOATNUM}             {
                            yylval.fval = atof(yytext);
                            return FLOAT_LITERAL;
                        }

{NUMBER}               {
                            yylval.ival = atoi(yytext);
                            return INT_LITERAL;
                        }

{STRING}               {
                            yylval.sval = strdup(yytext);
                            return STRING_LITERAL;
                        }



 /*|=========================================================|
   |                        IDENTIFIERS                      |
   |=========================================================|*/


{ID}                   {
                            yylval.sval = strdup(yytext);
                            return IDENTIFIER;
                        }




 /*|=========================================================|
   |                 SINGLE-CHAR OPERATORS                   |
   |=========================================================|*/

"+"                    { return '+'; }
"-"                    { return '-'; }

"*"                    { return '*'; }
"/"                    { return '/'; }
"%"                    { return '%'; }

"="                    { return '='; }

"<"                    { return '<'; }
">"                    { return '>'; }

"!"                    { return '!'; }

"&"                    { return '&'; }

"?"                    { return '?'; }
":"                    { return ':'; }

";"                    { return ';'; }
","                    { return ','; }

"("                    { return '('; }
")"                    { return ')'; }

"{"                    { return '{'; }
"}"                    { return '}'; }

"["                    { return '['; }
"]"                    { return ']'; }



 /*|=========================================================|
   |                        COMMENTS                         |
   |=========================================================|*/

"//".*                 ;   /* Single-line comments */


       /* Multi-line comments */

"/*"                    { BEGIN(COMMENT); }

<COMMENT>"*/"           { BEGIN(INITIAL); }

<COMMENT>\n             { line_num++; }

<COMMENT>.              ;   



 /*|=========================================================|
   |                        WHITESPACE                       |
   |=========================================================|*/

[ \t\r]+               ;

\n                     { line_num++; }


 /*|=========================================================|
   |                    ERROR HANDLING                       |
   |=========================================================|*/

.                      {fprintf(
                            stderr,
                            "%s: Lexical Error: Unknown character '%s' at line %d\n",
                            current_file,
                            yytext,
                            line_num
                        );}

%%