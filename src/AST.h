#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "SysyType.h"
#include "KoopaIR.h"

template<typename Target, typename Source>
inline std::shared_ptr<Target> shared_cast(Source* ptr)
{
    return std::shared_ptr<Target>(dynamic_cast<Target*>(ptr));
}

class BaseAST;
class RootAST;
class CompUnitAST;
class FuncDefAST;
class FuncTypeAST;
class BlockAST;
class StmtAST;
class ExpAST;
class UnaryExpAST;
class PrimaryExpAST;
class AddExpAST;
class MulExpAST;
class LOrExpAST;
class LAndExpAST;
class EqExpAST;
class RelExpAST;
class DeclAST;
class ConstDeclAST;
class BTypeAST;
class ConstDefAST;
class ConstDefsAST;
class ConstInitValAST;
class BlockItemAST;
class BlockItemsAST;
class LValAST;
class ConstExpAST;
class VarDeclAST;
class VarDefAST;
class VarDefsAST;
class InitValAST;
class FuncFParamsAST;
class FuncFParamAST;
class FuncRParamsAST;
class ExpsAST;
class DimenConstExpAST;
class ConstInitValsAST;
class InitValsAST;
class DimenExpAST;

using Stream = std::ofstream;
class BaseAST
{
public:
    virtual ~BaseAST() = default;

    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// Root ::= CompUnit
class RootAST : public BaseAST
{
public:
    std::shared_ptr<CompUnitAST> comp_unit;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class CompUnitAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// CompUnit ::= [CompUnit] FuncDef
class CompUnitAST1 : public CompUnitAST
{
public:
    std::shared_ptr<CompUnitAST> comp_unit;
    std::shared_ptr<FuncDefAST> func_def;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// CompUnit ::= [CompUnit] Decl
class CompUnitAST2 : public CompUnitAST
{
public:
    std::shared_ptr<CompUnitAST> comp_unit;
    std::shared_ptr<DeclAST> decl;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// FuncDef ::= FuncType IDENT "(" [FuncFParams] ")" Block
class FuncDefAST : public BaseAST
{
public:
    std::shared_ptr<FuncTypeAST> func_type;
    std::string ident;
    std::shared_ptr<FuncFParamsAST> func_fparams;
    std::shared_ptr<BlockAST> block;
public:
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};


// FuncType ::= "int" | "void"
class FuncTypeAST : public BaseAST
{
public:
    SysyType type;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// Block ::= "{" [BlockItems] "}"
class BlockAST : public BaseAST
{
public:
    std::shared_ptr<BlockItemsAST> block_items;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class StmtAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// Stmt ::= "return" [Exp] ";"
class StmtAST1 : public StmtAST
{
public:
    std::shared_ptr<ExpAST> exp;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// Stmt ::= LVal "=" Exp ";"
class StmtAST2 : public StmtAST
{
public:
    std::shared_ptr<LValAST> lval;
    std::shared_ptr<ExpAST> exp;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// Stmt ::= [Exp] ";"
class StmtAST3 : public StmtAST
{
public:
    std::shared_ptr<ExpAST> exp;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// Stmt ::= Block
class StmtAST4 : public StmtAST
{
public:
    std::shared_ptr<BlockAST> block;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// Stmt ::= "if" "(" Exp ")" Stmt ["else" Stmt]
class StmtAST5 : public StmtAST
{
public:
    std::shared_ptr<ExpAST> exp;
    std::shared_ptr<StmtAST> true_stmt;
    std::shared_ptr<StmtAST> false_stmt;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// Stmt ::= "while" "(" Exp ")" Stmt
class StmtAST6 : public StmtAST
{
public:
    std::shared_ptr<ExpAST> exp;
    std::shared_ptr<StmtAST> stmt;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// Stmt ::= "break" ";"
class StmtAST7 : public StmtAST
{
public:
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// Stmt ::= "continue" ";"
class StmtAST8 : public StmtAST
{
public:
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// Exp ::= LOrExp
class ExpAST : public BaseAST
{
public:
    std::shared_ptr<LOrExpAST> l_or_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class UnaryExpAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// UnaryExp ::= PrimaryExp
class UnaryExpAST1 : public UnaryExpAST
{
public:
    std::shared_ptr<PrimaryExpAST> primary_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// UnaryExp ::= UnaryOp UnaryExp
class UnaryExpAST2 : public UnaryExpAST
{
public:
    std::string op;
    std::shared_ptr<UnaryExpAST> unary_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// UnaryExp ::= IDENT "(" [FuncRParams] ")"
class UnaryExpAST3 : public UnaryExpAST
{
public:
    std::string ident;
    std::shared_ptr<FuncRParamsAST> func_rparams;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class PrimaryExpAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// PrimaryExp  ::= "(" Exp ")"
class PrimaryExpAST1 : public PrimaryExpAST
{
public: 
    std::shared_ptr<ExpAST> exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// PrimaryExp  ::= Number
class PrimaryExpAST2 : public PrimaryExpAST
{
public:
    int number;
    
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// PrimaryExp ::= LVal
class PrimaryExpAST3 : public PrimaryExpAST
{
public:
    std::shared_ptr<LValAST> lval;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class AddExpAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// AddExp ::= MulExp
class AddExpAST1 : public AddExpAST
{
public:
    std::shared_ptr<MulExpAST> mul_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// AddExp ::= AddExp ("+" | "-") MulExp
class AddExpAST2 : public AddExpAST
{
public:
    std::shared_ptr<AddExpAST> add_exp;
    std::string op;
    std::shared_ptr<MulExpAST> mul_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class MulExpAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// MulExp ::= UnaryExp
class MulExpAST1 : public MulExpAST
{
public:
    std::shared_ptr<UnaryExpAST> unary_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// MulExp ::= MulExp ("*" | "/" | "%") UnaryExp
class MulExpAST2 : public MulExpAST
{
public:
    std::shared_ptr<MulExpAST> mul_exp;
    std::string op;
    std::shared_ptr<UnaryExpAST> unary_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class LOrExpAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// LOrExp ::= LAndExp
class LOrExpAST1 : public LOrExpAST
{
public:
    std::shared_ptr<LAndExpAST> l_and_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// LOrExp ::= LOrExp "||" LAndExp
class LOrExpAST2 : public LOrExpAST
{
public:
    std::shared_ptr<LOrExpAST> l_or_exp;
    std::shared_ptr<LAndExpAST> l_and_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class LAndExpAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// LAndExp ::= EqExp
class LAndExpAST1 : public LAndExpAST
{
public:
    std::shared_ptr<EqExpAST> eq_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// LAndExp ::= LAndExp "&&" EqExp
class LAndExpAST2 : public LAndExpAST
{
public:
    std::shared_ptr<LAndExpAST> l_and_exp;
    std::shared_ptr<EqExpAST> eq_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class EqExpAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// EqExp ::= RelExp
class EqExpAST1 : public EqExpAST
{
public:
    std::shared_ptr<RelExpAST> rel_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// EqExp ::= EqExp ("==" | "!=") RelExp
class EqExpAST2 : public EqExpAST
{
public:
    std::shared_ptr<EqExpAST> eq_exp;
    std::string op;
    std::shared_ptr<RelExpAST> rel_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class RelExpAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// RelExp ::= AddExp
class RelExpAST1 : public RelExpAST
{
public:
    std::shared_ptr<AddExpAST> add_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// RelExp ::= RelExp ("<" | ">" | "<=" | ">=") AddExp
class RelExpAST2 : public RelExpAST
{
public:
    std::shared_ptr<RelExpAST> rel_exp;
    std::string op;
    std::shared_ptr<AddExpAST> add_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class DeclAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// Decl ::= ConstDecl
class DeclAST1 : public DeclAST
{
public:
    std::shared_ptr<ConstDeclAST> const_decl;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// Decl ::= VarDecl
class DeclAST2 : public DeclAST
{
public:
    std::shared_ptr<VarDeclAST> var_decl;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// ConstDecl ::= "const" BType ConstDefs ";"
class ConstDeclAST : public BaseAST
{
public:
    std::shared_ptr<BTypeAST> btype;
    std::shared_ptr<ConstDefsAST> const_defs;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// BType ::= "int"
class BTypeAST : public BaseAST
{
public:
    SysyType type = SysyType::INT;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// ConstDef ::= IDENT [DimenConstExp] "=" ConstInitVal
class ConstDefAST : public BaseAST
{
public:
    std::string ident;
    std::shared_ptr<DimenConstExpAST> dimen_const_exp;
    std::shared_ptr<ConstInitValAST> const_init_val;
    
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// ConstDefs ::= ConstDef ["," ConstDefs]
class ConstDefsAST : public BaseAST
{
public:
    std::shared_ptr<ConstDefAST> const_def;
    std::shared_ptr<ConstDefsAST> const_defs;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class ConstInitValAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// ConstInitVal ::= ConstExp
class ConstInitValAST1 : public ConstInitValAST
{
public:
    std::shared_ptr<ConstExpAST> const_exp;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// ConstInitVal ::= "{" [ConstInitVals] "}"
class ConstInitValAST2 : public ConstInitValAST
{
public:
    std::shared_ptr<ConstInitValsAST> const_init_vals;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class BlockItemAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// BlockItem ::= Decl
class BlockItemAST1 : public BlockItemAST
{
public:
    std::shared_ptr<DeclAST> decl;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// BlockItem ::= Stmt
class BlockItemAST2 : public BlockItemAST
{
public:
    std::shared_ptr<StmtAST> stmt;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// BlockItems ::= BlockItem [BlockItems]
class BlockItemsAST : public BaseAST
{
public:
    std::shared_ptr<BlockItemAST> block_item;
    std::shared_ptr<BlockItemsAST> block_items;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// LVal ::= IDENT [DimenExp]
class LValAST : public BaseAST
{
public:
    std::string ident;
    std::shared_ptr<DimenExpAST> dimen_exp;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// ConstExp ::= Exp
class ConstExpAST : public BaseAST
{
public:
    std::shared_ptr<ExpAST> exp;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// VarDecl ::= BType VarDefs ";"
class VarDeclAST : public BaseAST
{
public:
    std::shared_ptr<BTypeAST> btype;
    std::shared_ptr<VarDefsAST> var_defs;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// VarDefs ::= VarDef ["," VarDefs]
class VarDefsAST : public BaseAST
{
public:
    std::shared_ptr<VarDefAST> var_def;
    std::shared_ptr<VarDefsAST> var_defs;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class VarDefAST : public BaseAST
{
public:
    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// VarDef ::= IDENT [DimenConstExp]
class VarDefAST1 : public VarDefAST
{
public:
    std::string ident;
    std::shared_ptr<DimenConstExpAST> dimen_const_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// VarDef ::= IDENT [DimenConstExp] "=" InitVal
class VarDefAST2 : public VarDefAST
{
public:
    std::string ident;
    std::shared_ptr<DimenConstExpAST> dimen_const_exp;

    std::shared_ptr<VarDefAST> init_val;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

class InitValAST : public BaseAST
{
public:
    std::shared_ptr<ExpAST> exp;

    virtual void Dump(std::ofstream& stream) const = 0;
    virtual void Print(std::stringstream& stream, std::string& name) const = 0;
};

// InitVal ::= Exp
class InitValAST1 : public InitValAST
{
public:
    std::shared_ptr<ExpAST> exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// InitVal ::= "{" [InitVals] "}"
class InitValAST2 : public InitValAST
{
public:
    std::shared_ptr<InitValsAST> init_vals;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// FuncFParams ::= FuncFParam ["," FuncFParams]
class FuncFParamsAST : public BaseAST
{
public:
    std::shared_ptr<FuncFParamAST> func_fparam;
    std::shared_ptr<FuncFParamsAST> func_fparams;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// FuncFParam ::= BType IDENT ["[" "]" [DimenConstExp]]
class FuncFParamAST : public BaseAST
{
public:
    std::shared_ptr<BTypeAST> btype;
    std::string ident;
    std::shared_ptr<std::shared_ptr<DimenConstExpAST>> dimen_const_exp_wrap;
    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// FuncRParams ::= Exps
class FuncRParamsAST : public BaseAST
{
public:
    std::shared_ptr<ExpsAST> exps;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// Exps ::= Exp ["," Exps]
class ExpsAST : public BaseAST
{
public:
    std::shared_ptr<ExpAST> exp;
    std::shared_ptr<ExpsAST> exps;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// DimenConstExp ::= "[" ConstExp "]" [DimenConstExp]
class DimenConstExpAST : public BaseAST
{
public:
    std::shared_ptr<ConstExpAST> const_exp;
    std::shared_ptr<DimenConstExpAST> dimen_const_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// ConstInitVals ::= ConstInitVal ["," ConstInitVals]
class ConstInitValsAST : public BaseAST
{
public:
    std::shared_ptr<ConstInitValAST> const_init_val;
    std::shared_ptr<ConstInitValsAST> const_init_vals;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};


// InitVals ::= InitVal ["," InitVals]
class InitValsAST : public BaseAST
{
public:
    std::shared_ptr<InitValAST> init_val;
    std::shared_ptr<InitValsAST> init_vals;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};

// DimenExp ::= "[" Exp "]" [DimenExp]
class DimenExpAST : public BaseAST
{
public:
    std::shared_ptr<ExpAST> exp;
    std::shared_ptr<DimenExpAST> dimen_exp;

    virtual void Dump(std::ofstream& stream) const override;
    virtual void Print(std::stringstream& stream, std::string& name) const override;
};