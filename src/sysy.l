%option noyywrap
%option nounput
%option noinput

%{

#include <cstdlib>
#include <string>
#include <iostream>

// ��Ϊ Flex ���õ� Bison �й��� token �Ķ���
// ������Ҫ include Bison ���ɵ�ͷ�ļ�
#include "sysy.tab.hpp"

using namespace std;
int line_number;

%}

/* �հ׷���ע�� */
WhiteSpace    [ \t\r]*
EndLine       "\n"
LineComment   "//".*
BlockComment  "/*"([^*]|\*+[^/]|"\n")*"*/"

/* ��ʶ�� */
Identifier    [a-zA-Z_][a-zA-Z0-9_]*

/* ���������� */
Decimal       [1-9][0-9]*
Octal         0[0-7]*
Hexadecimal   0[xX][0-9a-fA-F]+

Parenthesis   "("|")"|"{"|"}"|"["|"]"

%%

{WhiteSpace}    { /* ����, �����κβ��� */ }
{EndLine}       { ++line_number; }
{LineComment}   { /* ����, �����κβ��� */ }
{BlockComment}  { /* ����, �����κβ��� */ }

"int"           { return INT; }
"return"        { return RETURN; }

{Identifier}    { yylval.str_val = new string(yytext); return IDENT; }

{Decimal}       { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{Octal}         { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{Hexadecimal}   { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }

{Parenthesis}   { return yytext[0]; }

","|";"         { return yytext[0]; }

.               { std::cerr << "Lexical error at line " << line_number 
                    << ": Invalid character " << yytext << "\n"; 
                  exit(EXIT_FAILURE); }

%%