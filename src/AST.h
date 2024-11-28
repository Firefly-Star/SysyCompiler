#pragma once

#include <memory>
#include <string>
#include <iostream>
#include "SysyType.h"
#include "KoopaIR.h"

class BaseAST
{
public:
    virtual ~BaseAST() = default;
    virtual void Dump() const = 0;
};

class CompUnitAST : public BaseAST
{
public:
    KoopaComponent program;
public:
    std::unique_ptr<BaseAST> func_def;
    virtual void Dump() const
    {
        program.functions.push_back(func_def->function);
        func_def->Dump();
    }
};

class FuncDefAST : public BaseAST
{
public:
    std::shared_ptr<KoopaComponent> function;
public:
    std::unique_ptr<BaseAST> func_type;
    std::string ident;
    std::unique_ptr<BaseAST> block;
public:
    virtual void Dump() const
    {
        fucntion
    }
};

class FuncTypeAST : public BaseAST
{
public:
    SysyType type = SysyType::INT;
    virtual void Dump() const
    {
        switch(type)
        {
            case SysyType::INT : std::cout << "int "; break;
            case SysyType::FLOAT : std::cout << "float "; break;
            default: std::cerr << "Unkown type ";break;
        }
    }
};

class BlockAST : public BaseAST
{
public:
    std::unique_ptr<BaseAST> stmt;
    virtual void Dump() const
    {
        std::cout << "{ ";
        stmt->Dump();
        std::cout << "} ";
    }
};

class StmtAST : public BaseAST
{
public:
    int number;
    virtual void Dump() const
    {
        std::cout << "return ";
        std::cout << number << " ; ";
    }
};
