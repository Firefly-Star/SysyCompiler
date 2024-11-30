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

%token INT RETURN CONST
%token <str_val> IDENT 
%token <int_val> INT_CONST

%type <ast_val> FuncDef FuncType Block Stmt Exp UnaryExp PrimaryExp MulExp AddExp RelExp EqExp LAndExp LOrExp Decl ConstDecl BType ConstDef ConstDefs ConstInitVal ConstExp BlockItem BlockItems LVal
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
  : '{' BlockItems '}' {
    auto ast = new BlockAST();
    ast->block_items = shared_cast<BlockItemsAST>($2);
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

PrimaryExp
  : LVal {
    auto ast = new PrimaryExpAST3();
    ast->lval = shared_cast<LValAST>($1);
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

Decl
  : ConstDecl {
    auto ast = new DeclAST1();
    ast->const_decl = shared_cast<ConstDeclAST>($1);
    $$ = ast;
  }
  ;

ConstDecl
  : CONST BType ConstDef ConstDefs ';' {
    auto ast = new ConstDeclAST();
    ast->btype = shared_cast<BTypeAST>($2);
    ast->const_def = shared_cast<ConstDefAST>($3);
    ast->const_defs = shared_cast<ConstDefsAST>($4);
    $$ = ast;
  }
  ;

BType
  : INT {
    auto ast = new BTypeAST();
    ast->type = SysyType::INT;
    $$ = ast;
  }
  ;

ConstDef
  : IDENT '=' ConstInitVal {
    auto ast = new ConstDefAST();
    ast->ident = *$1;
    ast->const_init_val = shared_cast<ConstInitValAST>($3);
    $$ = ast;

    delete $1;
  }
  ;

ConstDefs
  : {
    auto ast = new ConstDefsAST1();
    $$ = ast;
  }
  ;

ConstDefs
  : ',' ConstDef ConstDefs {
    auto ast = new ConstDefsAST2();
    ast->const_def = shared_cast<ConstDefAST>($2);
    ast->const_defs = shared_cast<ConstDefsAST>($3);
    $$ = ast;
  }
  ;

ConstInitVal
  : ConstExp {
    auto ast = new ConstInitValAST();
    ast->const_exp = shared_cast<ConstExpAST>($1);
    $$ = ast;
  }
  ;

BlockItems
  : {
    auto ast = new BlockItemsAST1();
    $$ = ast;
  }
  ;

BlockItems
  : BlockItem BlockItems {
    auto ast = new BlockItemsAST2();
    ast->block_item = shared_cast<BlockItemAST>($1);
    ast->block_items = shared_cast<BlockItemsAST>($2);
    $$ = ast;
  }
  ;

BlockItem
  : Decl {
    auto ast = new BlockItemAST1();
    ast->decl = shared_cast<DeclAST>($1);
    $$ = ast;
  }
  ;

BlockItem
  : Stmt {
    auto ast = new BlockItemAST2();
    ast->stmt = shared_cast<StmtAST>($1);
    $$ = ast;
  }
  ;

LVal
  : IDENT {
    auto ast = new LValAST();
    ast->ident = *$1;
    $$ = ast;

    delete $1;
  }
  ;

ConstExp
  : Exp {
    auto ast = new ConstExpAST();
    ast->exp = shared_cast<ExpAST>($1);
    $$ = ast;
  }
  ;

%%

void yyerror(unique_ptr<BaseAST>& ast, const char* s)
{
    std::cerr << "error: " << s << std::endl;
}