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

using Stream = std::ofstream;
class BaseAST
{
public:
    virtual ~BaseAST() = default;

    virtual void Dump(Stream& stream) const = 0;
};

class CompUnitAST : public BaseAST
{
public:
    std::shared_ptr<FuncDefAST> func_def;
    virtual void Dump(Stream& stream) const override;
};

class FuncDefAST : public BaseAST
{
public:
    std::unique_ptr<FuncTypeAST> func_type;
    std::string ident;
    std::unique_ptr<BlockAST> block;
public:
    virtual void Dump(Stream& stream) const override;
};

class FuncTypeAST : public BaseAST
{
public:
    SysyType type = SysyType::INT;
    virtual void Dump(Stream& stream) const override;
};

class BlockAST : public BaseAST
{
public:
    std::unique_ptr<StmtAST> stmt;
    virtual void Dump(Stream& stream) const override;
};

class StmtAST : public BaseAST
{
public:
    std::shared_ptr<ExpAST> exp;
    virtual void Dump(Stream& stream) const override;
};

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

// UnaryExp ::= UNARYOP UnaryExp
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