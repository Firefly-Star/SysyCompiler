%option noyywrap
%option nounput
%option noinput

%{

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

// 因为 Flex 会用到 Bison 中关于 token 的定义
// 所以需要 include Bison 生成的头文件
#include "sysy.tab.hpp"

using namespace std;
int line_number = 1;
std::stringstream lexOutss;

%}

/* 空白符和注释 */
WhiteSpace    [ \t\r]*
EndLine       "\n"
LineComment   "//".*
BlockComment  "/*"([^*]|\*+[^/]|"\n")*"*/"

/* 标识符 */
Identifier    [a-zA-Z_][a-zA-Z0-9_]*

/* 整数字面量 */
Decimal       [1-9][0-9]*
Octal         0[0-7]*
Hexadecimal   0[xX][0-9a-fA-F]+

%%

{WhiteSpace}    { lexOutss << "<WhiteSpace, >\n";                               /* 忽略, 不做任何操作 */ }
{EndLine}       { lexOutss << "<EndLine, >\n";                                  ++line_number; }
{LineComment}   { lexOutss << "<LineComment, " << yytext << ">\n";              /* 忽略, 不做任何操作 */ }
{BlockComment}  { lexOutss << "<BlockComment, " << yytext << ">\n";             /* 忽略, 不做任何操作 */ }

"int"           { lexOutss << "<INT, int>\n";                                   return INT; }
"return"        { lexOutss << "<RETURN, return>\n";                             return RETURN; }
"const"         { lexOutss << "<CONST, const>\n";                               return CONST; }
"if"            { lexOutss << "<IF, if>\n";                                     return IF; }
"else"          { lexOutss << "<ELSE, else>\n";                                 return ELSE; }
"while"         { lexOutss << "<WHILE, while>\n";                               return WHILE; }
"break"         { lexOutss << "<BREAK, break>\n";                               return BREAK; }
"continue"      { lexOutss << "<CONTINUE, continue>\n";                         return CONTINUE; }
"void"          { lexOutss << "<VOID, voidint>\n";                              return VOID; }

{Identifier}    { lexOutss << "<Identifier, " << yytext << ">\n";               yylval.str_val = new std::string(yytext); return IDENT; }

{Decimal}       { lexOutss << "<Decimal, " << yytext << ">\n";                  yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{Octal}         { lexOutss << "<Octal, " << yytext << ">\n";                    yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{Hexadecimal}   { lexOutss << "<Hexadecimal, " << yytext << ">\n";              yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }

.               { lexOutss << "<UnkownToken, " << yytext << ">\n";              return yytext[0]; }

%%
