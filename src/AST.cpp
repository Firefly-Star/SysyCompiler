#include "AST.h"

void CompUnitAST::Dump(Stream& stream) const
{
    func_def->Dump(stream);
}

void FuncDefAST::Dump(Stream& stream) const
{
    stream << "fun @" << ident << ": ";
    func_type->Dump(stream);
    stream << "{\n";
    block->Dump(stream);
    stream << "}";
}

void FuncTypeAST::Dump(Stream& stream) const
{
    switch(type)
    {
        case SysyType::INT: stream << "i32 "; break;
        default: break;
    }
}

void BlockAST::Dump(Stream& stream) const
{
    stream << "%entry: \n";
    stmt->Dump(stream);
}

void StmtAST::Dump(Stream& stream) const
{
    stream << "ret " << number << "\n";
}