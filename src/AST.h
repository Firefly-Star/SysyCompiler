#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include "SysyType.h"
#include "KoopaIR.h"

class BaseAST;
class CompUnitAST;
class FuncDefAST;
class FuncTypeAST;
class BlockAST;
class StmtAST;

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
    int number;
    virtual void Dump(Stream& stream) const override;
};