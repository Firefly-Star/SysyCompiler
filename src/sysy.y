%code requires{
    #include <memory>
    #include <string>
    #include "AST.h"
}

%{

#include <iostream>
#include <memory>
#include <string>
#include "AST.h"

int yylex();
void yyerror(std::unique_ptr<BaseAST>& ast, const char* s);

using namespace std;

%}

%parse-param {std::unique_ptr<BaseAST>& ast_root}

%union{
    std::string* str_val;
    int int_val;
    BaseAST* ast_val;
}

%token INT RETURN
%token <str_val> IDENT 
%token <int_val> INT_CONST

%type <ast_val> FuncDef FuncType Block Stmt Exp UnaryExp PrimaryExp MulExp AddExp RelExp EqExp LAndExp LOrExp
%type <int_val> Number
%type <str_val> UnaryOp MulOp AddOp EqOp RelOp

%%
// 开始符, CompUnit ::= FuncDef, 大括号后声明了解析完成后 parser 要做的事情
CompUnit
  : FuncDef {
    auto comp_unit = std::make_unique<CompUnitAST>();
    comp_unit->func_def = std::unique_ptr<FuncDefAST>(dynamic_cast<FuncDefAST*>($1));
    ast_root = std::move(comp_unit);
  }
  ;

// FuncDef ::= FuncType IDENT '(' ')' Block;
// 我们这里可以直接写 '(' 和 ')', 因为之前在 lexer 里已经处理了单个字符的情况
FuncDef
  : FuncType IDENT '(' ')' Block {
    auto ast = new FuncDefAST();
    ast->func_type = std::unique_ptr<FuncTypeAST>(dynamic_cast<FuncTypeAST*>($1));
    ast->ident = *$2;
    ast->block = std::unique_ptr<BlockAST>(dynamic_cast<BlockAST*>($5));
    $$ = ast;

    delete $2;
  }
  ;

// 同上, 不再解释
FuncType
  : INT {
    auto ast = new FuncTypeAST();
    ast->type = SysyType::INT;
    $$ = ast;
  }
  ;

Block
  : '{' Stmt '}' {
    auto ast = new BlockAST();
    ast->stmt = std::unique_ptr<StmtAST>(dynamic_cast<StmtAST*>($2));
    $$ = ast;
  }
  ;

Stmt
  : RETURN Exp ';' {
    auto ast = new StmtAST();
    ast->exp = std::shared_ptr<ExpAST>(dynamic_cast<ExpAST*>($2));
    $$ = ast;
  }
  ;

Exp
  : LOrExp {
    auto ast = new ExpAST();
    ast->l_or_exp = shared_cast<LOrExpAST>($1);
    $$ = ast;
  }
  ;

PrimaryExp
  : '(' Exp ')' {
    auto ast = new PrimaryExpAST1();
    ast->exp = shared_cast<ExpAST>($2);
    $$ = ast;
  }
  ;

PrimaryExp
  : Number {
    auto ast = new PrimaryExpAST2();
    ast->number = $1;
    $$ = ast;
  }
  ;

UnaryExp
  : PrimaryExp {
    auto ast = new UnaryExpAST1();
    ast->primary_exp = shared_cast<PrimaryExpAST>($1);
    $$ = ast;
  }
  ;

UnaryExp
  : UnaryOp UnaryExp {
    auto ast = new UnaryExpAST2();
    ast->op = *$1;
    ast->unary_exp = shared_cast<UnaryExpAST>($2);
    $$ = ast;

    delete $1;
  }
  ;

Number
  : INT_CONST {
    $$ = $1;
  }
  ;

UnaryOp
  : '+' { $$ = new std::string("+"); }
  | '-' { $$ = new std::string("-"); }
  | '!' { $$ = new std::string("!"); }
  ;

MulExp
  : UnaryExp{
    auto ast = new MulExpAST1();
    ast->unary_exp = shared_cast<UnaryExpAST>($1);
    $$ = ast;
  }
  ;

MulExp
  : MulExp MulOp UnaryExp {
    auto ast = new MulExpAST2();
    ast->mul_exp = shared_cast<MulExpAST>($1);
    ast->op = *$2;
    ast->unary_exp = shared_cast<UnaryExpAST>($3);
    $$ = ast;

    delete $2;
  }
  ;

MulOp
  : '*' { $$ = new std::string("*"); }
  | '/' { $$ = new std::string("/"); }
  | '%' { $$ = new std::string("%"); } 
  ;

AddExp
  : MulExp {
    auto ast = new AddExpAST1();
    ast->mul_exp = shared_cast<MulExpAST>($1);
    $$ = ast;
  }
  ;

AddExp
  : AddExp AddOp MulExp {
    auto ast = new AddExpAST2();
    ast->add_exp = shared_cast<AddExpAST>($1);
    ast->op = *$2;
    ast->mul_exp = shared_cast<MulExpAST>($3);
    $$ = ast;

    delete $2;
  }
  ;

AddOp
  : '+' { $$ = new std::string("+"); }
  | '-' { $$ = new std::string("-"); }
  ;

RelExp
  : AddExp {
    auto ast = new RelExpAST1();
    ast->add_exp = shared_cast<AddExpAST>($1);
    $$ = ast;
  }
  ;

RelExp
  : RelExp RelOp AddExp {
    auto ast = new RelExpAST2();
    ast->rel_exp = shared_cast<RelExpAST>($1);
    ast->op = *$2;
    ast->add_exp = shared_cast<AddExpAST>($3);
    $$ = ast;

    delete $2;
  }
  ;

RelOp
  : '<' { $$ = new std::string("<"); }
  | '>' { $$ = new std::string(">"); }
  | '<' '=' { $$ = new std::string("<="); }
  | '>' '=' { $$ = new std::string(">="); }
  ;

EqExp
  : RelExp {
    auto ast = new EqExpAST1();
    ast->rel_exp = shared_cast<RelExpAST>($1);
    $$ = ast;
  }
  ;

EqExp
  : EqExp EqOp RelExp {
    auto ast = new EqExpAST2();
    ast->eq_exp = shared_cast<EqExpAST>($1);
    ast->op = *$2;
    ast->rel_exp = shared_cast<RelExpAST>($3);
    $$ = ast;

    delete $2;
  }
  ;

EqOp
  : '=' '=' { $$ = new std::string("=="); }
  | '!' '=' { $$ = new std::string("!="); }
  ;

LAndExp
  : EqExp {
    auto ast = new LAndExpAST1();
    ast->eq_exp = shared_cast<EqExpAST>($1);
    $$ = ast;
  }
  ;

LAndExp
  : LAndExp '&' '&' EqExp {
    auto ast = new LAndExpAST2();
    ast->l_and_exp = shared_cast<LAndExpAST>($1);
    ast->eq_exp = shared_cast<EqExpAST>($4);
    $$ = ast;
  }
  ;

LOrExp
  : LAndExp {
    auto ast = new LOrExpAST1();
    ast->l_and_exp = shared_cast<LAndExpAST>($1);
    $$ = ast;
  }
  ;

LOrExp
  : LOrExp '|' '|' LAndExp {
    auto ast = new LOrExpAST2();
    ast->l_or_exp = shared_cast<LOrExpAST>($1);
    ast->l_and_exp = shared_cast<LAndExpAST>($4);
    $$ = ast;
  }
  ;

%%

void yyerror(unique_ptr<BaseAST>& ast, const char* s)
{
    std::cerr << "error: " << s << std::endl;
}