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

#define YYERROR_VERBOSE 1

int yylex();
void yyerror(std::unique_ptr<RootAST>& ast_root, const char* s);
bool result = true;

extern int line_number;

using namespace std;

%}

%parse-param {std::unique_ptr<RootAST>& ast_root}

%union{
    std::string* str_val;
    int int_val;
    BaseAST* ast_val;
}


%token INT RETURN CONST IF ELSE WHILE BREAK CONTINUE VOID FLOAT
%token <str_val> IDENT 
%token <int_val> INT_CONST

%type <ast_val> Root CompUnit FuncDef FuncType Block Stmt Exp UnaryExp PrimaryExp MulExp AddExp RelExp EqExp LAndExp LOrExp Decl ConstDecl BType ConstDef ConstDefs ConstInitVal ConstExp BlockItem BlockItems LVal VarDecl VarDef VarDefs InitVal FuncFParams FuncFParam FuncRParams Exps DimenConstExp ConstInitVals InitVals DimenExp FDef_VDecl FVType FDef_VDeclSuffix
%type <int_val> Number
%type <str_val> UnaryOp MulOp AddOp EqOp RelOp



%%
Root
  : CompUnit {
    auto ast = new RootAST();
    ast->line = line_number;
    ast->comp_unit = shared_cast<CompUnitAST>($1);
    ast_root = std::unique_ptr<RootAST>(ast);
    ast_root->result = result;
  }
  ;

CompUnit
  : FuncDef {
    auto ast = new CompUnitAST1();
    ast->line = line_number;
    ast->comp_unit = nullptr;
    ast->func_def = shared_cast<FuncDefAST>($1);
    $$ = ast;
  }
  ;

CompUnit
  : CompUnit FuncDef {
    auto ast = new CompUnitAST1();
    ast->line = line_number;
    ast->comp_unit = shared_cast<CompUnitAST>($1);
    ast->func_def = shared_cast<FuncDefAST>($2);
    $$ = ast;
  }
  ;

CompUnit
  : ConstDecl {
    auto ast = new CompUnitAST2();
    ast->line = line_number;
    ast->comp_unit = nullptr;
    ast->const_decl = shared_cast<ConstDeclAST>($1);
    $$ = ast;
  }
  ;

CompUnit
  : CompUnit ConstDecl {
    auto ast = new CompUnitAST2();
    ast->line = line_number;
    ast->comp_unit = shared_cast<CompUnitAST>($1);
    ast->const_decl = shared_cast<ConstDeclAST>($2);
    $$ = ast;
  }
  ;

CompUnit
  : FDef_VDecl {
    auto ast = new CompUnitAST3();
    ast->line = line_number;
    ast->comp_unit = nullptr;
    ast->fdef_vdecl = shared_cast<FDef_VDeclAST>($1);
    $$ = ast;
  }
  ;

CompUnit
  : CompUnit FDef_VDecl {
    auto ast = new CompUnitAST3();
    ast->line = line_number;
    ast->comp_unit = shared_cast<CompUnitAST>($1);
    ast->fdef_vdecl = shared_cast<FDef_VDeclAST>($2);
    $$ = ast;
  }
  ;

FDef_VDecl
  : FVType IDENT FDef_VDeclSuffix {
    auto ast = new FDef_VDeclAST();
    ast->line = line_number;
    ast->fvtype = shared_cast<FVTypeAST>($1);
    ast->ident = *$2;
    ast->fdef_vdecl_suffix = shared_cast<FDef_VDeclSuffixAST>($3);
    $$ = ast;

    delete $2;
  }
  ;

FVType
  : INT {
    auto ast = new FVTypeAST();
    ast->line = line_number;
    ast->type = SysyType::INT;
    $$ = ast;
  }
  | FLOAT {
    auto ast = new FVTypeAST();
    ast->type = SysyType::FLOAT;
    $$ = ast;
  }
  ;

FDef_VDeclSuffix
  : ';' {
    auto ast = new FDef_VDeclSuffixAST1();
    ast->line = line_number;
    ast->dimen_const_exp = nullptr;
    ast->init_val = nullptr;
    ast->var_defs = nullptr;
    $$ = ast;
  }
  | DimenConstExp ';' {
    auto ast = new FDef_VDeclSuffixAST1();
    ast->line = line_number;
    ast->dimen_const_exp = shared_cast<DimenConstExpAST>($1);
    ast->init_val = nullptr;
    ast->var_defs = nullptr;
    $$ = ast;
  }
  | DimenConstExp '=' InitVal ';' {
    auto ast = new FDef_VDeclSuffixAST1();
    ast->line = line_number;
    ast->dimen_const_exp = shared_cast<DimenConstExpAST>($1);
    ast->init_val = shared_cast<InitValAST>($3);
    ast->var_defs = nullptr;
    $$ = ast;
  }
  | DimenConstExp '=' InitVal ',' VarDefs ';' {
    auto ast = new FDef_VDeclSuffixAST1();
    ast->line = line_number;
    ast->dimen_const_exp = shared_cast<DimenConstExpAST>($1);
    ast->init_val = shared_cast<InitValAST>($3);
    ast->var_defs = shared_cast<VarDefsAST>($5);
    $$ = ast;
  }
  | DimenConstExp ',' VarDefs ';' {
    auto ast = new FDef_VDeclSuffixAST1();
    ast->line = line_number;
    ast->dimen_const_exp = shared_cast<DimenConstExpAST>($1);
    ast->init_val = nullptr;
    ast->var_defs = shared_cast<VarDefsAST>($3);
    $$ = ast;
  }
  | '=' InitVal ';' {
    auto ast = new FDef_VDeclSuffixAST1();
    ast->line = line_number;
    ast->dimen_const_exp = nullptr;
    ast->init_val = shared_cast<InitValAST>($2);
    ast->var_defs = nullptr;
    $$ = ast;
  }
  | '=' InitVal ',' VarDefs ';' {
    auto ast = new FDef_VDeclSuffixAST1();
    ast->line = line_number;
    ast->dimen_const_exp = nullptr;
    ast->init_val = shared_cast<InitValAST>($2);
    ast->var_defs = shared_cast<VarDefsAST>($4);
    $$ = ast;
  }
  | ',' VarDefs ';' {
    auto ast = new FDef_VDeclSuffixAST1();
    ast->line = line_number;
    ast->dimen_const_exp = nullptr;
    ast->init_val = nullptr;
    ast->var_defs = shared_cast<VarDefsAST>($2);
    $$ = ast;
  } 
  | '(' ')' Block {
    auto ast = new FDef_VDeclSuffixAST2();
    ast->line = line_number;
    ast->func_fparams = nullptr;
    ast->block = shared_cast<BlockAST>($3);
    $$ = ast;
  }
  | '(' FuncFParams ')' Block {
    auto ast = new FDef_VDeclSuffixAST2();
    ast->line = line_number;
    ast->func_fparams = shared_cast<FuncFParamsAST>($2);
    ast->block = shared_cast<BlockAST>($4);
    $$ = ast;
  }
  ;

FuncDef
  : FuncType IDENT '(' ')' Block {
    auto ast = new FuncDefAST();
    ast->line = line_number;
    ast->func_type = shared_cast<FuncTypeAST>($1);
    ast->ident = *$2;
    ast->func_fparams = nullptr;
    ast->block = shared_cast<BlockAST>($5);
    $$ = ast;

    delete $2;
  }
  
  ;

FuncDef
  : FuncType IDENT '(' FuncFParams ')' Block {
    auto ast = new FuncDefAST();
    ast->line = line_number;
    ast->func_type = shared_cast<FuncTypeAST>($1);
    ast->ident = *$2;
    ast->func_fparams = shared_cast<FuncFParamsAST>($4);
    ast->block = shared_cast<BlockAST>($6);
    $$ = ast;

    delete $2;
  }
  
  ;

FuncType
  : VOID {
    auto ast = new FuncTypeAST();
    ast->line = line_number;
    ast->type = SysyType::VOID;
    $$ = ast;
  }
  
  ;

Block
  : '{' BlockItems '}' {
    auto ast = new BlockAST();
    ast->line = line_number;
    ast->block_items = shared_cast<BlockItemsAST>($2);
    $$ = ast;
  }
  
  ;

Block
  : '{' '}' {
    auto ast = new BlockAST();
    ast->line = line_number;
    ast->block_items = nullptr;
    $$ = ast;
  }
  
  ;

Stmt
  : LVal '=' Exp ';' {
    auto ast = new StmtAST2();
    ast->line = line_number;
    ast->lval = shared_cast<LValAST>($1);
    ast->exp = shared_cast<ExpAST>($3);
    $$ = ast;
  }
  
  ;

Stmt
  : RETURN Exp ';' {
    auto ast = new StmtAST1();
    ast->line = line_number;
    ast->exp = shared_cast<ExpAST>($2);
    $$ = ast;
  }
  
  ;

Stmt
  : RETURN ';' {
    auto ast = new StmtAST1();
    ast->line = line_number;
    ast->exp = nullptr;
    $$ = ast;
  }
  
  ;

Stmt
  : ';' {
    auto ast = new StmtAST3();
    ast->exp = nullptr;
    ast->line = line_number;
    $$ = ast;
  }
  
  ;

Stmt
  : Exp ';' {
    auto ast = new StmtAST3();
    ast->line = line_number;
    ast->exp = shared_cast<ExpAST>($1);
    $$ = ast;
  }
  
  ;

Stmt
  : Block {
    auto ast = new StmtAST4();
    ast->line = line_number;
    ast->block = shared_cast<BlockAST>($1);
    $$ = ast;
  }
  
  ;

Stmt
  : IF '(' Exp ')' Stmt {
    auto ast = new StmtAST5();
    ast->exp = shared_cast<ExpAST>($3);
    ast->line = line_number;
    ast->true_stmt = shared_cast<StmtAST>($5);
    ast->false_stmt = nullptr;
    $$ = ast;
  }
  
  ;

Stmt
  : IF '(' Exp ')' Stmt ELSE Stmt {
    auto ast = new StmtAST5();
    ast->line = line_number;
    ast->exp = shared_cast<ExpAST>($3);
    ast->true_stmt = shared_cast<StmtAST>($5);
    ast->false_stmt = shared_cast<StmtAST>($7);
    $$ = ast;
  }
  
  ;

Stmt
  : WHILE '(' Exp ')' Stmt {
    auto ast = new StmtAST6();
    ast->line = line_number;
    ast->exp = shared_cast<ExpAST>($3);
    ast->stmt = shared_cast<StmtAST>($5);
    $$ = ast;
  }
  
  ;

Stmt
  : BREAK ';' {
    auto ast = new StmtAST7();
    ast->line = line_number;
    $$ = ast;
  }
  
  ;

Stmt
  : CONTINUE ';' {
    auto ast = new StmtAST8();
    ast->line = line_number;
    $$ = ast;
  }
  
  ;

Exp
  : LOrExp {
    auto ast = new ExpAST();
    ast->line = line_number;
    ast->l_or_exp = shared_cast<LOrExpAST>($1);
    $$ = ast;
  }
  
  ;

UnaryExp
  : PrimaryExp {
    auto ast = new UnaryExpAST1();
    ast->line = line_number;
    ast->primary_exp = shared_cast<PrimaryExpAST>($1);
    $$ = ast;
  }
  
  ;

UnaryExp
  : UnaryOp UnaryExp {
    auto ast = new UnaryExpAST2();
    ast->line = line_number;
    ast->op = *$1;
    ast->unary_exp = shared_cast<UnaryExpAST>($2);
    $$ = ast;

    delete $1;
  }
  
  ;

UnaryExp
  : IDENT '(' ')' {
    auto ast = new UnaryExpAST3();
    ast->line = line_number;
    ast->ident = *$1;
    ast->func_rparams = nullptr;
    $$ = ast;

    delete $1;
  }
  
  ;

UnaryExp
  : IDENT '(' FuncRParams ')' {
    auto ast = new UnaryExpAST3();
    ast->line = line_number;
    ast->ident = *$1;
    ast->func_rparams = shared_cast<FuncRParamsAST>($3);
    $$ = ast;

    delete $1;
  }
  
  ;

PrimaryExp
  : '(' Exp ')' {
    auto ast = new PrimaryExpAST1();
    ast->line = line_number;
    ast->exp = shared_cast<ExpAST>($2);
    $$ = ast;
  }
  
  ;

PrimaryExp
  : Number {
    auto ast = new PrimaryExpAST2();
    ast->line = line_number;
    ast->number = $1;
    $$ = ast;
  }
  
  ;

PrimaryExp
  : LVal {
    auto ast = new PrimaryExpAST3();
    ast->line = line_number;
    ast->lval = shared_cast<LValAST>($1);
    $$ = ast;
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

AddExp
  : MulExp {
    auto ast = new AddExpAST1();
    ast->line = line_number;
    ast->mul_exp = shared_cast<MulExpAST>($1);
    $$ = ast;
  }
  
  ;

AddExp
  : AddExp AddOp MulExp {
    auto ast = new AddExpAST2();
    ast->line = line_number;
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

MulExp
  : UnaryExp{
    auto ast = new MulExpAST1();
    ast->line = line_number;
    ast->unary_exp = shared_cast<UnaryExpAST>($1);
    $$ = ast;
  }
  
  ;

MulExp
  : MulExp MulOp UnaryExp {
    auto ast = new MulExpAST2();
    ast->mul_exp = shared_cast<MulExpAST>($1);
    ast->line = line_number;
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

RelExp
  : AddExp {
    auto ast = new RelExpAST1();
    ast->line = line_number;
    ast->add_exp = shared_cast<AddExpAST>($1);
    $$ = ast;
  }
  
  ;

RelExp
  : RelExp RelOp AddExp {
    auto ast = new RelExpAST2();
    ast->rel_exp = shared_cast<RelExpAST>($1);
    ast->line = line_number;
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
    ast->line = line_number;
    ast->rel_exp = shared_cast<RelExpAST>($1);
    $$ = ast;
  }
  
  ;

EqExp
  : EqExp EqOp RelExp {
    auto ast = new EqExpAST2();
    ast->eq_exp = shared_cast<EqExpAST>($1);
    ast->line = line_number;
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
    ast->line = line_number;
    ast->eq_exp = shared_cast<EqExpAST>($1);
    $$ = ast;
  }
  
  ;

LAndExp
  : LAndExp '&' '&' EqExp {
    auto ast = new LAndExpAST2();
    ast->line = line_number;
    ast->l_and_exp = shared_cast<LAndExpAST>($1);
    ast->eq_exp = shared_cast<EqExpAST>($4);
    $$ = ast;
  }
  
  ;

LOrExp
  : LAndExp {
    auto ast = new LOrExpAST1();
    ast->line = line_number;
    ast->l_and_exp = shared_cast<LAndExpAST>($1);
    $$ = ast;
  }
  
  ;

LOrExp
  : LOrExp '|' '|' LAndExp {
    auto ast = new LOrExpAST2();
    ast->line = line_number;
    ast->l_or_exp = shared_cast<LOrExpAST>($1);
    ast->l_and_exp = shared_cast<LAndExpAST>($4);
    $$ = ast;
  }
  
  ;

Decl
  : ConstDecl {
    auto ast = new DeclAST1();
    ast->line = line_number;
    ast->const_decl = shared_cast<ConstDeclAST>($1);
    $$ = ast;
  }
  
  ;

Decl
  : VarDecl {
    auto ast = new DeclAST2();
    ast->line = line_number;
    ast->var_decl = shared_cast<VarDeclAST>($1);
    $$ = ast;
  }
  
  ;

ConstDecl
  : CONST BType ConstDefs ';' {
    auto ast = new ConstDeclAST();
    ast->btype = shared_cast<BTypeAST>($2);
    ast->line = line_number;
    ast->const_defs = shared_cast<ConstDefsAST>($3);
    $$ = ast;
  }
  
  ;

BType
  : INT {
    auto ast = new BTypeAST();
    ast->line = line_number;
    ast->type = SysyType::INT;
    $$ = ast;
  }
  | FLOAT {
    auto ast = new BTypeAST();
    ast->line = line_number;
    ast->type = SysyType::FLOAT;
    $$ = ast;
  }
  ;

ConstDef
  : IDENT '=' ConstInitVal {
    auto ast = new ConstDefAST();
    ast->ident = *$1;
    ast->line = line_number;
    ast->dimen_const_exp = nullptr;
    ast->const_init_val = shared_cast<ConstInitValAST>($3);
    $$ = ast;

    delete $1;
  }
  
  ;

ConstDef
  : IDENT DimenConstExp '=' ConstInitVal {
    auto ast = new ConstDefAST();
    ast->ident = *$1;
    ast->line = line_number;
    ast->dimen_const_exp = shared_cast<DimenConstExpAST>($2);
    ast->const_init_val = shared_cast<ConstInitValAST>($4);
    $$ = ast;

    delete $1;
  }
  
  ;

DimenConstExp
  : '[' ConstExp ']' {
    auto ast = new DimenConstExpAST();
    ast->line = line_number;
    ast->const_exp = shared_cast<ConstExpAST>($2);
    ast->dimen_const_exp = nullptr;
    $$ = ast;
  }
  
  ;

DimenConstExp
  : '[' ConstExp ']' DimenConstExp {
    auto ast = new DimenConstExpAST();
    ast->line = line_number;
    ast->const_exp = shared_cast<ConstExpAST>($2);
    ast->dimen_const_exp = shared_cast<DimenConstExpAST>($4);
    $$ = ast;
  }
  
  ;

ConstDefs
  : ConstDef {
    auto ast = new ConstDefsAST();
    ast->line = line_number;
    ast->const_def = shared_cast<ConstDefAST>($1);
    ast->const_defs = nullptr;
    $$ = ast;
  }
  
  ;

ConstDefs
  : ConstDef ',' ConstDefs {
    auto ast = new ConstDefsAST();
    ast->line = line_number;
    ast->const_def = shared_cast<ConstDefAST>($1);
    ast->const_defs = shared_cast<ConstDefsAST>($3);
    $$ = ast;
  }
  
  ;

ConstInitVal
  : ConstExp {
    auto ast = new ConstInitValAST1();
    ast->line = line_number;
    ast->const_exp = shared_cast<ConstExpAST>($1);
    $$ = ast;
  }
  
  ;

ConstInitVal
  : '{' '}' {
    auto ast = new ConstInitValAST2();
    ast->line = line_number;
    ast->const_init_vals = nullptr;
    $$ = ast;
  }
  
  ;

ConstInitVal
  : '{' ConstInitVals '}' {
    auto ast = new ConstInitValAST2();
    ast->line = line_number;
    ast->const_init_vals = shared_cast<ConstInitValsAST>($2);
    $$ = ast;
  }
  
  ;

ConstInitVals
  : ConstInitVal {
    auto ast = new ConstInitValsAST();
    ast->const_init_val = shared_cast<ConstInitValAST>($1);
    ast->line = line_number;
    ast->const_init_vals = nullptr;
    $$ = ast;
  }
  
  ;

ConstInitVals
  : ConstInitVal ',' ConstInitVals {
    auto ast = new ConstInitValsAST();
    ast->const_init_val = shared_cast<ConstInitValAST>($1);
    ast->line = line_number;
    ast->const_init_vals = shared_cast<ConstInitValsAST>($3);
    $$ = ast;
  }
  
  ;

BlockItems
  : BlockItem{
    auto ast = new BlockItemsAST();
    ast->line = line_number;
    ast->block_item = shared_cast<BlockItemAST>($1);
    ast->block_items = nullptr;
    $$ = ast;
  }
  
  ;

BlockItems
  : BlockItem BlockItems {
    auto ast = new BlockItemsAST();
    ast->line = line_number;
    ast->block_item = shared_cast<BlockItemAST>($1);
    ast->block_items = shared_cast<BlockItemsAST>($2);
    $$ = ast;
  }
  
  ;

BlockItem
  : Decl {
    auto ast = new BlockItemAST1();
    ast->line = line_number;
    ast->decl = shared_cast<DeclAST>($1);
    $$ = ast;
  }
  
  ;

BlockItem
  : Stmt {
    auto ast = new BlockItemAST2();
    ast->line = line_number;
    ast->stmt = shared_cast<StmtAST>($1);
    $$ = ast;
  }
  
  ;

LVal
  : IDENT {
    auto ast = new LValAST();
    ast->ident = *$1;
    ast->line = line_number;
    ast->dimen_exp = nullptr;
    $$ = ast;

    delete $1;
  }
  
  ;

LVal
  : IDENT DimenExp {
    auto ast = new LValAST();
    ast->ident = *$1;
    ast->line = line_number;
    ast->dimen_exp = shared_cast<DimenExpAST>($2);
    $$ = ast;

    delete $1;
  }
  
  ;

DimenExp
  : '[' Exp ']' {
    auto ast = new DimenExpAST();
    ast->line = line_number;
    ast->exp = shared_cast<ExpAST>($2);
    ast->dimen_exp = nullptr;
    $$ = ast;
  }
  
  ;

DimenExp
  : '[' Exp ']' DimenExp {
    auto ast = new DimenExpAST();
    ast->line = line_number;
    ast->exp = shared_cast<ExpAST>($2);
    ast->dimen_exp = shared_cast<DimenExpAST>($4);
    $$ = ast;
  }
  
  ;

ConstExp
  : Exp {
    auto ast = new ConstExpAST();
    ast->line = line_number;
    ast->exp = shared_cast<ExpAST>($1);
    $$ = ast;
  }
  
  ;

VarDecl
  : BType VarDefs ';' {
    auto ast = new VarDeclAST();
    ast->line = line_number;
    ast->btype = shared_cast<BTypeAST>($1);
    ast->var_defs = shared_cast<VarDefsAST>($2);
    $$ = ast;
  }
   
  ;

VarDefs
  : VarDef{
    auto ast = new VarDefsAST();
    ast->var_def = shared_cast<VarDefAST>($1);
    ast->line = line_number;
    ast->var_defs = nullptr;
    $$ = ast;
  }
  
  ;

VarDefs
  : VarDef ',' VarDefs {
    auto ast = new VarDefsAST();
    ast->line = line_number;
    ast->var_def = shared_cast<VarDefAST>($1);
    ast->var_defs = shared_cast<VarDefsAST>($3);
    $$ = ast;
  }
  
  ;

VarDef
  : IDENT {
    auto ast = new VarDefAST1();
    ast->ident = *$1;
    ast->line = line_number;
    ast->dimen_const_exp = nullptr;
    $$ = ast;

    delete $1;
  }
  
  ;

VarDef
  : IDENT DimenConstExp {
    auto ast = new VarDefAST1();
    ast->ident = *$1;
    ast->line = line_number;
    ast->dimen_const_exp = shared_cast<DimenConstExpAST>($2);
    $$ = ast;

    delete $1;
  }
  
  ;

VarDef
  : IDENT '=' InitVal {
    auto ast = new VarDefAST2();
    ast->ident = *$1;
    ast->line = line_number;
    ast->dimen_const_exp = nullptr;
    ast->init_val = shared_cast<InitValAST>($3);
    $$ = ast;

    delete $1;
  }
  
  ;

VarDef
  : IDENT DimenConstExp '=' InitVal {
    auto ast = new VarDefAST2();
    ast->line = line_number;
    ast->ident = *$1;
    ast->dimen_const_exp = shared_cast<DimenConstExpAST>($2);
    ast->init_val = shared_cast<InitValAST>($4);
    $$ = ast;

    delete $1;
  }
  
  ;

InitVal
  : Exp {
    auto ast = new InitValAST1();
    ast->line = line_number;
    ast->exp = shared_cast<ExpAST>($1);
    $$ = ast;
  }
  
  ;

InitVal
  : '{' '}' {
    auto ast = new InitValAST2();
    ast->line = line_number;
    ast->init_vals = nullptr;
    $$ = ast;
  }
  
  ;

InitVal
  : '{' InitVals '}' {
    auto ast = new InitValAST2();
    ast->line = line_number;
    ast->init_vals = shared_cast<InitValsAST>($2);
    $$ = ast;
  }
  
  ;

InitVals
  : InitVal {
    auto ast = new InitValsAST();
    ast->init_val = shared_cast<InitValAST>($1);
    ast->line = line_number;
    ast->init_vals = nullptr;
    $$ = ast;
  }
  
  ;

InitVals
  : InitVal ',' InitVals {
    auto ast = new InitValsAST();
    ast->line = line_number;
    ast->init_val = shared_cast<InitValAST>($1);
    ast->init_vals = shared_cast<InitValsAST>($3);
    $$ = ast;
  }
  
  ;

FuncFParams
  : FuncFParam {
    auto ast = new FuncFParamsAST();
    ast->line = line_number;
    ast->func_fparam = shared_cast<FuncFParamAST>($1);
    ast->func_fparams = nullptr;
    $$ = ast;
  }
  
  ;

FuncFParams
  : FuncFParam ',' FuncFParams {
    auto ast = new FuncFParamsAST();
    ast->func_fparam = shared_cast<FuncFParamAST>($1);
    ast->line = line_number;
    ast->func_fparams = shared_cast<FuncFParamsAST>($3);
    $$ = ast;
  }
  
  ;

FuncFParam
  : BType IDENT {
    auto ast = new FuncFParamAST();
    ast->btype = shared_cast<BTypeAST>($1);
    ast->line = line_number;
    ast->ident = *$2;
    ast->dimen_const_exp_wrap = nullptr;
    $$ = ast;

    delete $2;
  }
  
  ;

FuncFParam
  : BType IDENT '[' ']' {
    auto ast = new FuncFParamAST();
    ast->line = line_number;
    ast->btype = shared_cast<BTypeAST>($1);
    ast->ident = *$2;

    std::shared_ptr<DimenConstExpAST>* ptr = new std::shared_ptr<DimenConstExpAST>(nullptr);
    ast->dimen_const_exp_wrap = std::shared_ptr<std::shared_ptr<DimenConstExpAST>>(ptr);
    $$ = ast;

    delete $2;
  }
  
  ;

FuncFParam
  : BType IDENT '[' ']' DimenConstExp {
    auto ast = new FuncFParamAST();
    ast->btype = shared_cast<BTypeAST>($1);
    ast->ident = *$2;
    ast->line = line_number;
    
    std::shared_ptr<DimenConstExpAST>* ptr = new std::shared_ptr<DimenConstExpAST>(dynamic_cast<DimenConstExpAST*>($5));
    ast->dimen_const_exp_wrap = std::shared_ptr<std::shared_ptr<DimenConstExpAST>>(ptr);
    $$ = ast;

    delete $2;
  }
  
  ;

FuncRParams
  : Exps {
    auto ast = new FuncRParamsAST();
    ast->line = line_number;
    ast->exps = shared_cast<ExpsAST>($1);
    $$ = ast;
  }
  
  ;

Exps
  : Exp {
    auto ast = new ExpsAST();
    ast->line = line_number;
    ast->exp = shared_cast<ExpAST>($1);
    ast->exps = nullptr;
    $$ = ast;
  }
  
  ;

Exps
  : Exp ',' Exps {
    auto ast = new ExpsAST();
    ast->exp = shared_cast<ExpAST>($1);
    ast->line = line_number;
    ast->exps = shared_cast<ExpsAST>($3);
    $$ = ast;
  }
  
  ;

%%

void yyerror(std::unique_ptr<RootAST>& ast_root, const char* s)
{
    std::cerr << "Error type [" << s 
              << "] at line [" << line_number 
              << "] : " << "说明信息不做要求，等到语义检查中再做补充" << std::endl;
}