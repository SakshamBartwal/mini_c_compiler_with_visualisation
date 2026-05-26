%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_num = 1;
%}

%option noyywrap

DIGIT      [0-9]
LETTER     [a-zA-Z_]
ID         {LETTER}({LETTER}|{DIGIT})*
NUMBER     {DIGIT}+
FLOATNUM   {DIGIT}+\.{DIGIT}+
STRING     \"([^\"]|\\.)*\"

%%

"import"               { return IMPORT; }
"int"                  { return INT; }
"float"                { return FLOAT; }
"char"                 { return CHAR; }
"void"                 { return VOID; }
"if"                   { return IF; }
"else"                 { return ELSE; }
"while"                { return WHILE; }
"for"                  { return FOR; }
"return"               { return RETURN; }
"switch"               { return SWITCH; }
"case"                 { return CASE; }
"default"              { return DEFAULT; }
"break"                { return BREAK; }
"continue"             { return CONTINUE; }

"=="                   { return EQ; }
"!="                   { return NEQ; }
"<="                   { return LE; }
">="                   { return GE; }
"&&"                   { return AND; }
"||"                   { return OR; }

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

{ID}                   {
                            yylval.sval = strdup(yytext);
                            return IDENTIFIER;
                        }

"+"                    { return '+'; }
"-"                    { return '-'; }
"*"                    { return '*'; }
"/"                    { return '/'; }
"="                    { return '='; }
"<"                    { return '<'; }
">"                    { return '>'; }
";"                    { return ';'; }
","                    { return ','; }
"("                    { return '('; }
")"                    { return ')'; }
"{"                    { return '{'; }
"}"                    { return '}'; }
"["                    { return '['; }
"]"                    { return ']'; }

[ \t\r]+               ;
\n                      { line_num++; }

"//".*                 ;

"/*"([^*]|\*+[^*/])*"*/" ;

.                       {
                            printf("Unknown character: %s at line %d\n", yytext, line_num);
                        }

%%