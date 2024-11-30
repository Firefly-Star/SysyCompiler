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
}

void ExpAST::Dump(Stream &stream) const
{
}

void UnaryExpAST1::Dump(Stream &stream) const
{
}

void UnaryExpAST2::Dump(Stream &stream) const
{
}

void PrimaryExpAST1::Dump(Stream &stream) const
{
}

void PrimaryExpAST2::Dump(Stream &stream) const
{
}

void AddExpAST1::Dump(Stream &stream) const
{
}

void AddExpAST2::Dump(Stream &stream) const
{
}

void MulExpAST1::Dump(Stream &stream) const
{
}

void MulExpAST2::Dump(Stream &stream) const
{
}

void LOrExpAST1::Dump(Stream &stream) const
{
}

void LOrExpAST2::Dump(Stream &stream) const
{
}

void LAndExpAST1::Dump(Stream &stream) const
{
}

void LAndExpAST2::Dump(Stream &stream) const
{
}

void EqExpAST1::Dump(Stream &stream) const
{
}

void EqExpAST2::Dump(Stream &stream) const
{
}

void RelExpAST1::Dump(Stream &stream) const
{
}

void RelExpAST2::Dump(Stream &stream) const
{
}
