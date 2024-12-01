#include "AST.h"

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

void PrimaryExpAST3::Dump(Stream &stream) const
{
}

void DeclAST1::Dump(Stream &stream) const
{
}

void ConstDeclAST::Dump(Stream &stream) const
{
}

void ConstDefAST::Dump(Stream &stream) const
{
}

void BlockItemAST1::Dump(Stream &stream) const
{
}

void BlockItemAST2::Dump(Stream &stream) const
{
}

void LValAST::Dump(Stream &stream) const
{
}

void ConstExpAST::Dump(Stream &stream) const
{
}

void BTypeAST::Dump(Stream &stream) const
{
}

void DeclAST2::Dump(Stream &stream) const
{
}

void VarDeclAST::Dump(Stream &stream) const
{
}

void VarDefAST1::Dump(Stream &stream) const
{
}

void VarDefAST2::Dump(Stream &stream) const
{
}

void StmtAST1::Dump(Stream &stream) const
{
}

void StmtAST2::Dump(Stream &stream) const
{
}

void InitValAST::Dump(Stream &stream) const
{
}

void StmtAST3::Dump(Stream &stream) const
{
}

void StmtAST4::Dump(Stream &stream) const
{
}

void StmtAST5::Dump(Stream &stream) const
{
}

void StmtAST6::Dump(Stream &stream) const
{
}

void StmtAST7::Dump(Stream &stream) const
{
}

void StmtAST8::Dump(Stream &stream) const
{
}

void FuncFParamAST::Dump(Stream &stream) const
{
}

void UnaryExpAST3::Dump(Stream &stream) const
{
}

void FuncRParamsAST::Dump(Stream &stream) const
{
}

void FuncDefAST::Dump(Stream &stream) const
{
}

void FuncFParamsAST::Dump(Stream &stream) const
{
}

void VarDefsAST::Dump(Stream &stream) const
{
}

void ConstDefsAST::Dump(Stream &stream) const
{
}

void BlockItemsAST::Dump(Stream &stream) const
{
}

void CompUnitAST1::Dump(Stream &stream) const
{
}

void CompUnitAST2::Dump(Stream &stream) const
{
}

void RootAST::Dump(Stream &stream) const
{
}

void ExpsAST::Dump(Stream &stream) const
{
}

void ConstInitValAST1::Dump(Stream &stream) const
{
}

void ConstInitValAST2::Dump(Stream &stream) const
{
}

void InitValAST1::Dump(Stream &stream) const
{
}

void InitValAST2::Dump(Stream &stream) const
{
}

void DimenConstExpAST::Dump(Stream &stream) const
{
}

void ConstInitValsAST::Dump(Stream &stream) const
{
}

void InitValsAST::Dump(Stream &stream) const
{
}

void DimenExpAST::Dump(Stream &stream) const
{
}
