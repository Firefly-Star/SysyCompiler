#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include "SysyType.h"
#include "KoopaIR.h"

template<typename Target, typename Source>
inline std::shared_ptr<Target> shared_cast(Source* ptr)
{
    return std::shared_ptr<Target>(dynamic_cast<Target*>(ptr));
}

class BaseAST;
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

using Stream = std::ofstream;
class BaseAST
{
public:
    virtual ~BaseAST() = default;

    virtual void Dump(Stream& stream) const = 0;
};

// CompUnit ::= FuncDef
class CompUnitAST : public BaseAST
{
public:
    std::shared_ptr<FuncDefAST> func_def;
    virtual void Dump(Stream& stream) const override;
};

// FuncDef ::= FuncType IDENT "(" ")" Block
class FuncDefAST : public BaseAST
{
public:
    std::unique_ptr<FuncTypeAST> func_type;
    std::string ident;
    std::unique_ptr<BlockAST> block;
public:
    virtual void Dump(Stream& stream) const override;
};

// FuncType ::= "int"
class FuncTypeAST : public BaseAST
{
public:
    SysyType type = SysyType::INT;
    virtual void Dump(Stream& stream) const override;
};

// Block ::= "{" BlockItems "}"
class BlockAST : public BaseAST
{
public:
    std::shared_ptr<BlockItemsAST> block_items;
    virtual void Dump(Stream& stream) const override;
};

class StmtAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// Stmt ::= "return" Exp ";"
class StmtAST1 : public StmtAST
{
public:
    std::shared_ptr<ExpAST> exp;
    virtual void Dump(Stream& stream) const override;
};

// Stmt ::= LVal "=" Exp ";"
class StmtAST2 : public StmtAST
{
public:
    std::shared_ptr<LValAST> lval;
    std::shared_ptr<ExpAST> exp;
    virtual void Dump(Stream& stream) const override;
};

// Stmt ::= ";"
class StmtAST3 : public StmtAST
{
public:
    virtual void Dump(Stream& stream) const override;
};

// Stmt ::= Exp ";"
class StmtAST4 : public StmtAST
{
public:
    std::shared_ptr<ExpAST> exp;
    virtual void Dump(Stream& stream) const override;
};

// Stmt ::= Block
class StmtAST5 : public StmtAST
{
public:
    std::shared_ptr<BlockAST> block;
    virtual void Dump(Stream& stream) const override;
};

// Stmt ::= "if" "(" Exp ")" Stmt
class StmtAST6 : public StmtAST
{
public:
    std::shared_ptr<ExpAST> exp;
    std::shared_ptr<StmtAST> true_stmt;
    virtual void Dump(Stream& stream) const override;
};

// Stmt ::= "if" "(" Exp ")" Stmt "else" Stmt
class StmtAST7 : public StmtAST
{
public:
    std::shared_ptr<ExpAST> exp;
    std::shared_ptr<StmtAST> true_stmt;
    std::shared_ptr<StmtAST> false_stmt;
    virtual void Dump(Stream& stream) const override;
};

// Stmt ::= "while" "(" Exp ")" Stmt
class StmtAST8 : public StmtAST
{
public:
    std::shared_ptr<ExpAST> exp;
    std::shared_ptr<StmtAST> stmt;
    virtual void Dump(Stream& stream) const override;
};

// Stmt ::= "break" ";"
class StmtAST9 : public StmtAST
{
public:
    virtual void Dump(Stream& stream) const override;
};

// Stmt ::= "continue" ";"
class StmtAST10 : public StmtAST
{
public:
    virtual void Dump(Stream& stream) const override;
};

// Exp ::= LOrExp
class ExpAST : public BaseAST
{
public:
    std::shared_ptr<LOrExpAST> l_or_exp;

    virtual void Dump(Stream& stream) const override;
};

class UnaryExpAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// UnaryExp ::= PrimaryExp
class UnaryExpAST1 : public UnaryExpAST
{
public:
    std::shared_ptr<PrimaryExpAST> primary_exp;

    virtual void Dump(Stream& stream) const override;
};

// UnaryExp ::= UnaryOp UnaryExp
class UnaryExpAST2 : public UnaryExpAST
{
public:
    std::string op;
    std::shared_ptr<UnaryExpAST> unary_exp;

    virtual void Dump(Stream& stream) const override;
};

class PrimaryExpAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// PrimaryExp  ::= "(" Exp ")"
class PrimaryExpAST1 : public PrimaryExpAST
{
public: 
    std::shared_ptr<ExpAST> exp;

    virtual void Dump(Stream& stream) const override;
};

// PrimaryExp  ::= Number
class PrimaryExpAST2 : public PrimaryExpAST
{
public:
    int number;
    
    virtual void Dump(Stream& stream) const override;
};

// PrimaryExp ::= LVal
class PrimaryExpAST3 : public PrimaryExpAST
{
public:
    std::shared_ptr<LValAST> lval;
    virtual void Dump(Stream& stream) const override;
};

class AddExpAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// AddExp ::= MulExp
class AddExpAST1 : public AddExpAST
{
public:
    std::shared_ptr<MulExpAST> mul_exp;

    virtual void Dump(Stream& stream) const override;
};

// AddExp ::= AddExp ("+" | "-") MulExp
class AddExpAST2 : public AddExpAST
{
public:
    std::shared_ptr<AddExpAST> add_exp;
    std::string op;
    std::shared_ptr<MulExpAST> mul_exp;

    virtual void Dump(Stream& stream) const override;
};

class MulExpAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// MulExp ::= UnaryExp
class MulExpAST1 : public MulExpAST
{
public:
    std::shared_ptr<UnaryExpAST> unary_exp;

    virtual void Dump(Stream& stream) const override;
};

// MulExp ::= MulExp ("*" | "/" | "%") UnaryExp
class MulExpAST2 : public MulExpAST
{
public:
    std::shared_ptr<MulExpAST> mul_exp;
    std::string op;
    std::shared_ptr<UnaryExpAST> unary_exp;

    virtual void Dump(Stream& stream) const override;
};

class LOrExpAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// LOrExp ::= LAndExp
class LOrExpAST1 : public LOrExpAST
{
public:
    std::shared_ptr<LAndExpAST> l_and_exp;

    virtual void Dump(Stream& stream) const override;
};

// LOrExp ::= LOrExp "||" LAndExp
class LOrExpAST2 : public LOrExpAST
{
public:
    std::shared_ptr<LOrExpAST> l_or_exp;
    std::shared_ptr<LAndExpAST> l_and_exp;

    virtual void Dump(Stream& stream) const override;
};

class LAndExpAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// LAndExp ::= EqExp
class LAndExpAST1 : public LAndExpAST
{
public:
    std::shared_ptr<EqExpAST> eq_exp;

    virtual void Dump(Stream& stream) const override;
};

// LAndExp ::= LAndExp "&&" EqExp
class LAndExpAST2 : public LAndExpAST
{
public:
    std::shared_ptr<LAndExpAST> l_and_exp;
    std::shared_ptr<EqExpAST> eq_exp;

    virtual void Dump(Stream& stream) const override;
};

class EqExpAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// EqExp ::= RelExp
class EqExpAST1 : public EqExpAST
{
public:
    std::shared_ptr<RelExpAST> rel_exp;

    virtual void Dump(Stream& stream) const override;
};

// EqExp ::= EqExp ("==" | "!=") RelExp
class EqExpAST2 : public EqExpAST
{
public:
    std::shared_ptr<EqExpAST> eq_exp;
    std::string op;
    std::shared_ptr<RelExpAST> rel_exp;

    virtual void Dump(Stream& stream) const override;
};

class RelExpAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// RelExp ::= AddExp
class RelExpAST1 : public RelExpAST
{
public:
    std::shared_ptr<AddExpAST> add_exp;

    virtual void Dump(Stream& stream) const override;
};

// RelExp ::= RelExp ("<" | ">" | "<=" | ">=") AddExp
class RelExpAST2 : public RelExpAST
{
public:
    std::shared_ptr<RelExpAST> rel_exp;
    std::string op;
    std::shared_ptr<AddExpAST> add_exp;

    virtual void Dump(Stream& stream) const override;
};

class DeclAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// Decl ::= ConstDecl
class DeclAST1 : public DeclAST
{
public:
    std::shared_ptr<ConstDeclAST> const_decl;
    virtual void Dump(Stream& stream) const override;
};

// Decl ::= ConstDecl | VarDecl
class DeclAST2 : public DeclAST
{
public:
    std::shared_ptr<VarDeclAST> var_decl;
    virtual void Dump(Stream& stream) const override;
};

// ConstDecl ::= "const" BType ConstDef ConstDefs ";"
class ConstDeclAST : public BaseAST
{
public:
    std::shared_ptr<BTypeAST> btype;
    std::shared_ptr<ConstDefAST> const_def;
    std::shared_ptr<ConstDefsAST> const_defs;

    virtual void Dump(Stream& stream) const override;
};

// BType ::= "int"
class BTypeAST : public BaseAST
{
public:
    SysyType type = SysyType::INT;
    virtual void Dump(Stream& stream) const override;
};

// ConstDef ::= IDENT "=" ConstInitVal
class ConstDefAST : public BaseAST
{
public:
    std::string ident;
    std::shared_ptr<ConstInitValAST> const_init_val;
    
    virtual void Dump(Stream& stream) const override;
};

class ConstDefsAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// ConstDefs ::= epsilon
class ConstDefsAST1 : public ConstDefsAST
{
public:
    virtual void Dump(Stream& stream) const override;
};

// ConstDefs ::= "," ConstDef ConstDefs
class ConstDefsAST2 : public ConstDeclAST
{
public:
    std::shared_ptr<ConstDefAST> const_def;
    std::shared_ptr<ConstDefsAST> const_defs;

    virtual void Dump(Stream& stream) const override;
};

// ConstInitVal ::= ConstExp
class ConstInitValAST : public BaseAST
{
public:
    std::shared_ptr<ConstExpAST> const_exp;
    virtual void Dump(Stream& stream) const override;
};

class BlockItemAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// BlockItem ::= Decl
class BlockItemAST1 : public BlockItemAST
{
public:
    std::shared_ptr<DeclAST> decl;
    virtual void Dump(Stream& stream) const override;
};

// BlockItem ::= Stmt
class BlockItemAST2 : public BlockItemAST
{
public:
    std::shared_ptr<StmtAST> stmt;
    virtual void Dump(Stream& stream) const override;
};

class BlockItemsAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// BlockItems ::= epsilon
class BlockItemsAST1 : public BlockItemsAST
{
public:
    virtual void Dump(Stream& stream) const override;
};

// BlockItems ::= BlockItem BlockItems
class BlockItemsAST2 : public BlockItemsAST
{
public:
    std::shared_ptr<BlockItemAST> block_item;
    std::shared_ptr<BlockItemsAST> block_items;

    virtual void Dump(Stream& stream) const override;
};

// LVal ::= IDENT
class LValAST : public BaseAST
{
public:
    std::string ident;
    virtual void Dump(Stream& stream) const override;
};

// ConstExp ::= Exp
class ConstExpAST : public BaseAST
{
public:
    std::shared_ptr<ExpAST> exp;
    virtual void Dump(Stream& stream) const override;
};

// VarDecl ::= BType VarDef VarDefs ";"
class VarDeclAST : public BaseAST
{
public:
    std::shared_ptr<BTypeAST> btype;
    std::shared_ptr<VarDefAST> var_def;
    std::shared_ptr<VarDefsAST> var_defs;
    virtual void Dump(Stream& stream) const override;
};

class VarDefsAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// VarDefs ::= epsilon
class VarDefsAST1 : public VarDefsAST
{
public:
    virtual void Dump(Stream& stream) const override;
};

// VarDefs ::= VarDef VarDefs
class VarDefsAST2 : public VarDefsAST
{
public:
    std::shared_ptr<VarDefAST> var_def;
    std::shared_ptr<VarDefsAST> var_defs;
    virtual void Dump(Stream& stream) const override;
};


class VarDefAST : public BaseAST
{
public:
    virtual void Dump(Stream& stream) const = 0;
};

// VarDef ::= IDENT
class VarDefAST1 : public VarDefAST
{
public:
    std::string ident;

    virtual void Dump(Stream& stream) const override;
};

// VarDef ::= IDENT "=" InitVal
class VarDefAST2 : public VarDefAST
{
public:
    std::string ident;
    std::shared_ptr<VarDefAST> init_val;

    virtual void Dump(Stream& stream) const override;
};

// InitVal ::= Exp
class InitValAST : public BaseAST
{
public:
    std::shared_ptr<ExpAST> exp;

    virtual void Dump(Stream& stream) const override;
};

