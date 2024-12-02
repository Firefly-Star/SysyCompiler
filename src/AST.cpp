#include "AST.h"

int nodeNumber = 0;

std::string GenName()
{
    std::string name = "node" + std::to_string(nodeNumber);
    ++nodeNumber;
    return name;
}

void FuncTypeAST::Dump(std::ofstream& stream) const
{
}

// FuncType ::= "int" | "void"
void FuncTypeAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"FuncType\"];\n";

    std::string name1 = GenName();
    std::string typeName;
    switch(type)
    {
        case SysyType::INT: typeName = "int"; break; 
        case SysyType::VOID: typeName = "void"; break;
        default: typeName = "unknown"; 
    }
    stream << name << " -> " << name1 << ";\n";
    stream << name1 << " [label=\"" << typeName << "\"];\n";
}

// Block ::= "{" [BlockItems] "}"
void BlockAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Block\"];\n";  // 节点标题为 "Block"

    std::string blockStart = GenName();  // 开始符号的节点名称
    stream << name << " -> " << blockStart << ";\n";
    stream << blockStart << " [label=\"{\"];\n";  // 开始符号

    if (block_items)
    {
        std::string blockItemsNode = GenName();  // BlockItems 的节点名称
        stream << name << " -> " << blockItemsNode << ";\n";  // 连接
        block_items->Print(stream, blockItemsNode);  // 递归打印 block_items
    }

    std::string blockEnd = GenName();  // 结束符号的节点名称
    stream << name << " -> " << blockEnd << ";\n";  // 连接
    stream << blockEnd << " [label=\"}\"];\n";  // 结束符号
}

void BlockAST::Dump(std::ofstream& stream) const
{
}

void ExpAST::Dump(std::ofstream& stream) const
{
}

// Exp ::= LOrExp
void ExpAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Exp\"];\n";  // 创建父节点 "Exp"

    if (l_or_exp)
    {
        std::string lOrExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << lOrExpNode << ";\n";  // 连接 "Exp" 到 "LOrExp"
        l_or_exp->Print(stream, lOrExpNode);  // 递归打印 LOrExp
    }
}

void UnaryExpAST1::Dump(std::ofstream& stream) const
{
}

// UnaryExp ::= PrimaryExp
void UnaryExpAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"UnaryExp\"];\n";  // 创建父节点 "UnaryExp"

    if (primary_exp)
    {
        std::string primaryExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << primaryExpNode << ";\n";  // 连接 "UnaryExp" 到 "PrimaryExp"
        primary_exp->Print(stream, primaryExpNode);  // 递归打印 PrimaryExp
    }
}

// PrimaryExp  ::= "(" Exp ")"
void PrimaryExpAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"PrimaryExp\"];\n";  // 创建父节点 "PrimaryExp"

    // 创建左括号节点
    std::string openParenNode = GenName();
    stream << name << " -> " << openParenNode << ";\n";
    stream << openParenNode << " [label=\"(\"];\n";  // 创建左括号

    // 连接到表达式
    if (exp)
    {
        std::string expNode = GenName();
        stream << name << " -> " << expNode << ";\n";  
        exp->Print(stream, expNode);  // 递归打印表达式
    }

    // 创建右括号节点
    std::string closeParenNode = GenName();
    stream << name << " -> " << closeParenNode << ";\n";
    stream << closeParenNode << " [label=\")\"];\n";  // 创建右括号
}

void UnaryExpAST2::Dump(std::ofstream& stream) const
{
}

// UnaryExp ::= UnaryOp UnaryExp
void UnaryExpAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"UnaryExp\"];\n";  // 创建父节点 "UnaryExp"

    // 创建操作符节点
    std::string opNode = GenName();
    stream << name << " -> " << opNode << ";\n";  // 连接 "UnaryExp" 到操作符
    stream << opNode << " [label=\"" << op << "\"];\n";  // 创建子节点操作符

    if (unary_exp)
    {
        std::string unaryExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << unaryExpNode << ";\n";  // 连接 "UnaryExp" 到另一个 UnaryExp
        unary_exp->Print(stream, unaryExpNode);  // 递归打印子一元表达式
    }
}

void PrimaryExpAST1::Dump(std::ofstream& stream) const
{
}

void PrimaryExpAST2::Dump(std::ofstream& stream) const
{
}

// AddExp ::= MulExp
void AddExpAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"AddExp\"];\n";  // 创建父节点 "AddExp"

    if (mul_exp)
    {
        std::string mulExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << mulExpNode << ";\n";  // 连接 "AddExp" 到 "MulExp"
        mul_exp->Print(stream, mulExpNode);  // 递归打印乘法表达式
    }
}

// AddExp ::= AddExp ("+" | "-") MulExp
void AddExpAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"AddExp\"];\n";  // 创建父节点 "AddExp"

    if (add_exp)
    {
        std::string leftAddExpNode = GenName();  // 生成左侧子节点名称
        stream << name << " -> " << leftAddExpNode << ";\n";  // 连接 "AddExp" 到左侧 AddExp
        add_exp->Print(stream, leftAddExpNode);  // 递归打印左侧 AddExp
    }

    // 创建操作符节点
    std::string opNode = GenName();
    stream << name << " -> " << opNode << ";\n";  // 连接 "AddExp" 到操作符
    stream << opNode << " [label=\"" << op << "\"];\n";  // 创建操作符节点

    if (mul_exp)
    {
        std::string rightMulExpNode = GenName();  // 生成右侧子节点名称
        stream << name << " -> " << rightMulExpNode << ";\n";  // 连接 "AddExp" 到右侧 MulExp
        mul_exp->Print(stream, rightMulExpNode);  // 递归打印乘法表达式
    }
}

// PrimaryExp  ::= Number
void PrimaryExpAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"PrimaryExp\"];\n";  // 创建父节点 "PrimaryExp"

    // 创建数字节点
    std::string numberNode = GenName();
    stream << name << " -> " << numberNode << ";\n";  
    stream << numberNode << " [label=\"" << number << "\"];\n";  // 创建数字节点
}

void AddExpAST1::Dump(std::ofstream& stream) const
{
}

void AddExpAST2::Dump(std::ofstream& stream) const
{
}

void MulExpAST1::Dump(std::ofstream& stream) const
{
}

// MulExp ::= UnaryExp
void MulExpAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"MulExp\"];\n";  // 创建父节点 "MulExp"

    if (unary_exp)
    {
        std::string unaryExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << unaryExpNode << ";\n";  // 连接 "MulExp" 到 "UnaryExp"
        unary_exp->Print(stream, unaryExpNode);  // 递归打印一元表达式
    }
}

void MulExpAST2::Dump(std::ofstream& stream) const
{
}

// MulExp ::= MulExp ("*" | "/" | "%") UnaryExp
void MulExpAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"MulExp\"];\n";  // 创建父节点 "MulExp"

    if (mul_exp)
    {
        std::string leftMulExpNode = GenName();  // 生成左侧子节点名称
        stream << name << " -> " << leftMulExpNode << ";\n";  // 连接 "MulExp" 到左侧 MulExp
        mul_exp->Print(stream, leftMulExpNode);  // 递归打印左侧 MulExp
    }

    // 创建操作符节点
    std::string opNode = GenName();
    stream << name << " -> " << opNode << ";\n";  // 连接 "MulExp" 到操作符
    stream << opNode << " [label=\"" << op << "\"];\n";  // 创建操作符节点

    if (unary_exp)
    {
        std::string rightUnaryExpNode = GenName();  // 生成右侧子节点名称
        stream << name << " -> " << rightUnaryExpNode << ";\n";  // 连接 "MulExp" 到右侧 UnaryExp
        unary_exp->Print(stream, rightUnaryExpNode);  // 递归打印一元表达式
    }
}

void LOrExpAST1::Dump(std::ofstream& stream) const
{
}

// LOrExp ::= LAndExp
void LOrExpAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"LOrExp\"];\n";  // 创建父节点 "LOrExp"

    if (l_and_exp)
    {
        std::string lAndExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << lAndExpNode << ";\n";  // 连接 "LOrExp" 到 "LAndExp"
        l_and_exp->Print(stream, lAndExpNode);  // 递归打印逻辑与表达式
    }
}

void LOrExpAST2::Dump(std::ofstream& stream) const
{
}

// LOrExp ::= LOrExp "||" LAndExp
void LOrExpAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"LOrExp\"];\n";  // 创建父节点 "LOrExp"

    if (l_or_exp)
    {
        std::string leftLOrExpNode = GenName();  // 生成左侧子节点名称
        stream << name << " -> " << leftLOrExpNode << ";\n";  // 连接 "LOrExp" 到左侧 LOrExp
        l_or_exp->Print(stream, leftLOrExpNode);  // 递归打印左侧逻辑或表达式
    }

    // 创建运算符节点
    std::string opNode = GenName();
    stream << name << " -> " << opNode << ";\n";  // 连接 "LOrExp" 到操作符
    stream << opNode << " [label=\"||\"];\n";  // 创建 "||" 操作符节点

    if (l_and_exp)
    {
        std::string rightLAndExpNode = GenName();  // 生成右侧子节点名称
        stream << name << " -> " << rightLAndExpNode << ";\n";  // 连接 "LOrExp" 到右侧 LAndExp
        l_and_exp->Print(stream, rightLAndExpNode);  // 递归打印逻辑与表达式
    }
}

void LAndExpAST1::Dump(std::ofstream& stream) const
{
}

// LAndExp ::= EqExp
void LAndExpAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"LAndExp\"];\n";  // 创建父节点 "LAndExp"

    if (eq_exp)
    {
        std::string eqExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << eqExpNode << ";\n";  // 连接 "LAndExp" 到 "EqExp"
        eq_exp->Print(stream, eqExpNode);  // 递归打印等式表达式
    }
}

void LAndExpAST2::Dump(std::ofstream& stream) const
{
}

// LAndExp ::= LAndExp "&&" EqExp
void LAndExpAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"LAndExp\"];\n";  // 创建父节点 "LAndExp"

    if (l_and_exp)
    {
        std::string leftLAndExpNode = GenName();  // 生成左侧子节点名称
        stream << name << " -> " << leftLAndExpNode << ";\n";  // 连接 "LAndExp" 到左侧 LAndExp
        l_and_exp->Print(stream, leftLAndExpNode);  // 递归打印左侧逻辑与表达式
    }

    // 创建运算符节点
    std::string opNode = GenName();
    stream << name << " -> " << opNode << ";\n";  // 连接 "LAndExp" 到操作符
    stream << opNode << " [label=\"&&\"];\n";  // 创建 "&&" 操作符节点

    if (eq_exp)
    {
        std::string rightEqExpNode = GenName();  // 生成右侧子节点名称
        stream << name << " -> " << rightEqExpNode << ";\n";  // 连接 "LAndExp" 到右侧 EqExp
        eq_exp->Print(stream, rightEqExpNode);  // 递归打印等式表达式
    }
}

// EqExp ::= RelExp
void EqExpAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"EqExp\"];\n";  // 创建父节点 "EqExp"

    if (rel_exp)
    {
        std::string relExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << relExpNode << ";\n";  // 连接 "EqExp" 到 "RelExp"
        rel_exp->Print(stream, relExpNode);  // 递归打印关系表达式
    }
}

void EqExpAST1::Dump(std::ofstream& stream) const
{
}

void EqExpAST2::Dump(std::ofstream& stream) const
{
}

// EqExp ::= EqExp ("==" | "!=") RelExp
void EqExpAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"EqExp\"];\n";  // 创建父节点 "EqExp"

    if (eq_exp)
    {
        std::string leftEqExpNode = GenName();  // 生成左侧子节点名称
        stream << name << " -> " << leftEqExpNode << ";\n";  // 连接 "EqExp" 到左侧 EqExp
        eq_exp->Print(stream, leftEqExpNode);  // 递归打印左侧 EqExp
    }

    // 创建操作符节点
    std::string opNode = GenName();
    stream << name << " -> " << opNode << ";\n";  // 连接 "EqExp" 到操作符
    stream << opNode << " [label=\"" << op << "\"];\n";  // 创建操作符节点

    if (rel_exp)
    {
        std::string rightRelExpNode = GenName();  // 生成右侧子节点名称
        stream << name << " -> " << rightRelExpNode << ";\n";  // 连接 "EqExp" 到右侧 RelExp
        rel_exp->Print(stream, rightRelExpNode);  // 递归打印关系表达式
    }
}

void RelExpAST1::Dump(std::ofstream& stream) const
{
}

// RelExp ::= AddExp
void RelExpAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"RelExp\"];\n";  // 创建父节点 "RelExp"

    if (add_exp)
    {
        std::string addExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << addExpNode << ";\n";  // 连接 "RelExp" 到 "AddExp"
        add_exp->Print(stream, addExpNode);  // 递归打印加法表达式
    }
}

void RelExpAST2::Dump(std::ofstream& stream) const
{
}

// RelExp ::= RelExp ("<" | ">" | "<=" | ">=") AddExp
void RelExpAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"RelExp\"];\n";  // 创建父节点 "RelExp"

    if (rel_exp)
    {
        std::string leftRelExpNode = GenName();  // 生成左侧子节点名称
        stream << name << " -> " << leftRelExpNode << ";\n";  // 连接 "RelExp" 到左侧 RelExp
        rel_exp->Print(stream, leftRelExpNode);  // 递归打印左侧 RelExp
    }

    // 创建操作符节点
    std::string opNode = GenName();
    stream << name << " -> " << opNode << ";\n";  // 连接 "RelExp" 到操作符
    stream << opNode << " [label=\"" << op << "\"];\n";  // 创建操作符节点

    if (add_exp)
    {
        std::string rightAddExpNode = GenName();  // 生成右侧子节点名称
        stream << name << " -> " << rightAddExpNode << ";\n";  // 连接 "RelExp" 到右侧 AddExp
        add_exp->Print(stream, rightAddExpNode);  // 递归打印加法表达式
    }
}

void PrimaryExpAST3::Dump(std::ofstream& stream) const
{
}

// PrimaryExp ::= LVal
void PrimaryExpAST3::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"PrimaryExp\"];\n";  // 创建父节点 "PrimaryExp"

    if (lval)
    {
        std::string lvalNode = GenName();  // 生成子节点名称
        stream << name << " -> " << lvalNode << ";\n";  // 连接 "PrimaryExp" 到 "LVal"
        lval->Print(stream, lvalNode);  // 递归打印 LVal
    }
}

void DeclAST1::Dump(std::ofstream& stream) const
{
}

// Decl ::= ConstDecl
void DeclAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Decl\"];\n";  // 创建父节点 "Decl"

    if (const_decl)
    {
        std::string constDeclNode = GenName();  // 生成子节点名称
        stream << name << " -> " << constDeclNode << ";\n";  // 连接 "Decl" 到 "ConstDecl"
        const_decl->Print(stream, constDeclNode);  // 递归打印常量声明
    }
}

void ConstDeclAST::Dump(std::ofstream& stream) const
{
}

// ConstDecl ::= "const" BType ConstDefs  ";"
void ConstDeclAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"ConstDecl\"];\n";  // 创建父节点 "ConstDecl"

    // 创建 "const" 关键字的节点
    std::string constNode = GenName();
    stream << name << " -> " << constNode << ";\n";  // 连接到 "const" 关键字
    stream << constNode << " [label=\"const\"];\n";  // 定义 "const" 关键字节点

    if (btype)
    {
        std::string bTypeNode = GenName();  // 生成子节点名称
        stream << name << " -> " << bTypeNode << ";\n";  // 连接 "ConstDecl" 到 "BType"
        btype->Print(stream, bTypeNode);  // 递归打印基本类型
    }

    if (const_defs)
    {
        std::string constDefsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << constDefsNode << ";\n";  // 连接 "ConstDecl" 到 "ConstDefs"
        const_defs->Print(stream, constDefsNode);  // 递归打印常量定义
    }

    // 创建终结符 ";" 的节点
    std::string semicolonNode = GenName();
    stream << name << " -> " << semicolonNode << ";\n";  // 连接到 ";"
    stream << semicolonNode << " [label=\";\"];\n";  // 定义分号节点
}

void ConstDefAST::Dump(std::ofstream& stream) const
{
}

// ConstDef ::= IDENT [DimenConstExp] "=" ConstInitVal
void ConstDefAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"ConstDef\"];\n";  // 创建父节点 "ConstDef"

    // 创建标识符的子节点
    std::string identNode = GenName();
    stream << name << " -> " << identNode << ";\n";  // 连接到标识符
    stream << identNode << " [label=\"" << ident << "\"];\n";  // 定义标识符节点

    // 如果存在维度常量表达式，则打印它
    if (dimen_const_exp)
    {
        std::string dimenConstExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << dimenConstExpNode << ";\n";  // 连接 "ConstDef" 到 "DimenConstExp"
        dimen_const_exp->Print(stream, dimenConstExpNode);  // 递归打印维度常量表达式
    }

    // 创建等号节点
    std::string equalNode = GenName();
    stream << name << " -> " << equalNode << ";\n";  // 连接到 "="
    stream << equalNode << " [label=\"=\"];\n";  // 定义等号节点

    // 打印常量初始化值
    if (const_init_val)
    {
        std::string constInitValNode = GenName();  // 生成子节点名称
        stream << name << " -> " << constInitValNode << ";\n";  // 连接 "ConstDef" 到 "ConstInitVal"
        const_init_val->Print(stream, constInitValNode);  // 递归打印常量初始化值
    }
}

void BlockItemAST1::Dump(std::ofstream& stream) const
{
}

// BlockItem ::= Decl
void BlockItemAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"BlockItem1\"];\n";  // 创建父节点 "BlockItem1"

    // 打印声明
    if (decl)
    {
        std::string declNode = GenName();  // 生成子节点名称
        stream << name << " -> " << declNode << ";\n";  // 连接 "BlockItem1" 到 "Decl"
        decl->Print(stream, declNode);  // 递归打印声明
    }
}

void BlockItemAST2::Dump(std::ofstream& stream) const
{
}

// BlockItem ::= Stmt
void BlockItemAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"BlockItem2\"];\n";  // 创建父节点 "BlockItem2"

    // 打印语句
    if (stmt)
    {
        std::string stmtNode = GenName();  // 生成子节点名称
        stream << name << " -> " << stmtNode << ";\n";  // 连接 "BlockItem2" 到 "Stmt"
        stmt->Print(stream, stmtNode);  // 递归打印语句
    }
}

void LValAST::Dump(std::ofstream& stream) const
{
}

// LVal ::= IDENT [DimenExp]
void LValAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"LVal\"];\n";  // 创建父节点 "LVal"

    // 创建标识符的子节点
    std::string identNode = GenName();
    stream << name << " -> " << identNode << ";\n";  // 连接到标识符
    stream << identNode << " [label=\"" << ident << "\"];\n";  // 定义标识符节点

    // 如果存在维度表达式，则打印它
    if (dimen_exp)
    {
        std::string dimenExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << dimenExpNode << ";\n";  // 连接 "LVal" 到 "DimenExp"
        dimen_exp->Print(stream, dimenExpNode);  // 递归打印维度表达式
    }
}

void ConstExpAST::Dump(std::ofstream& stream) const
{
}

// ConstExp ::= Exp
void ConstExpAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"ConstExp\"];\n";  // 创建父节点 "ConstExp"

    // 打印表达式
    if (exp)
    {
        std::string expNode = GenName();  // 生成子节点名称
        stream << name << " -> " << expNode << ";\n";  // 连接 "ConstExp" 到 "Exp"
        exp->Print(stream, expNode);  // 递归打印表达式
    }
}

void BTypeAST::Dump(std::ofstream& stream) const
{
}

// BType ::= "int"
void BTypeAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"BType\"];\n";  // 创建父节点 "BType"
    std::string name1 = GenName();
    stream << name << " -> " << name1 << ";\n";  // 创建描述类型的子节点
    std::string typeName;
    switch(type)
    {
        case SysyType::INT: typeName = "int"; break;
        case SysyType::FLOAT: typeName = "float"; break;
        default: typeName = "unknown"; break;
    }
    stream << name << " [label=\"" << typeName << "\"];\n";  // 输出基本类型
}

// Decl ::= VarDecl
void DeclAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Decl\"];\n";  // 创建父节点 "Decl"

    if (var_decl)
    {
        std::string varDeclNode = GenName();  // 生成子节点名称
        stream << name << " -> " << varDeclNode << ";\n";  // 连接 "Decl" 到 "VarDecl"
        var_decl->Print(stream, varDeclNode);  // 递归打印变量声明
    }
}

void DeclAST2::Dump(std::ofstream& stream) const
{
}

void VarDeclAST::Dump(std::ofstream& stream) const
{
}

// VarDef ::= IDENT [DimenConstExp]
void VarDefAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"VarDef1\"];\n";  // 创建父节点 "VarDef1"

    // 创建标识符的子节点
    std::string identNode = GenName();
    stream << name << " -> " << identNode << ";\n";  // 连接到标识符
    stream << identNode << " [label=\"" << ident << "\"];\n";  // 定义标识符节点

    // 如果存在维度常量表达式，则打印它
    if (dimen_const_exp)
    {
        std::string dimenConstExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << dimenConstExpNode << ";\n";  // 连接 "VarDef1" 到 "DimenConstExp"
        dimen_const_exp->Print(stream, dimenConstExpNode);  // 递归打印维度常量表达式
    }
}

// VarDecl ::= BType VarDefs ";"
void VarDeclAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"VarDecl\"];\n";  // 创建父节点 "VarDecl"

    // 打印基本类型
    if (btype)
    {
        std::string bTypeNode = GenName();  // 生成子节点名称
        stream << name << " -> " << bTypeNode << ";\n";  // 连接 "VarDecl" 到 "BType"
        btype->Print(stream, bTypeNode);  // 递归打印基本类型
    }

    // 打印变量定义
    if (var_defs)
    {
        std::string varDefsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << varDefsNode << ";\n";  // 连接 "VarDecl" 到 "VarDefs"
        var_defs->Print(stream, varDefsNode);  // 递归打印变量定义
    }

    // 创建分号节点
    std::string semicolonNode = GenName();
    stream << name << " -> " << semicolonNode << ";\n";  // 连接到 ";"
    stream << semicolonNode << " [label=\";\"];\n";  // 定义分号节点
}

void VarDefAST1::Dump(std::ofstream& stream) const
{
}

void VarDefAST2::Dump(std::ofstream& stream) const
{
}

// VarDef ::= IDENT [DimenConstExp] "=" InitVal
void VarDefAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"VarDef2\"];\n";  // 创建父节点 "VarDef2"

    // 创建标识符的子节点
    std::string identNode = GenName();
    stream << name << " -> " << identNode << ";\n";  // 连接到标识符
    stream << identNode << " [label=\"" << ident << "\"];\n";  // 定义标识符节点

    // 如果存在维度常量表达式，则打印它
    if (dimen_const_exp)
    {
        std::string dimenConstExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << dimenConstExpNode << ";\n";  // 连接 "VarDef2" 到 "DimenConstExp"
        dimen_const_exp->Print(stream, dimenConstExpNode);  // 递归打印维度常量表达式
    }

    // 创建等号节点
    std::string equalNode = GenName();
    stream << name << " -> " << equalNode << ";\n";  // 连接到 "="
    stream << equalNode << " [label=\"=\"];\n";  // 定义等号节点

    // 打印初始化值
    if (init_val)
    {
        std::string initValNode = GenName();  // 生成子节点名称
        stream << name << " -> " << initValNode << ";\n";  // 连接 "VarDef2" 到 "InitVal"
        init_val->Print(stream, initValNode);  // 递归打印初始化值
    }
}

// Stmt ::= "return" [Exp] ";"
void StmtAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Stmt\"];\n";  // 创建父节点 "Stmt"

    std::string returnNode = GenName();
    stream << name << " -> " << returnNode << ";\n";  // 连接 "Stmt" 到 "return"
    stream << returnNode << " [label=\"return\"];\n";  // 创建子节点 "return"

    // 如果有表达式，创建表达式节点并连接
    if (exp)
    {
        std::string expNode = GenName();  // 生成表达式节点名称
        stream << name << " -> " << expNode << ";\n";  // 连接 "Stmt" 到表达式
        exp->Print(stream, expNode);  // 递归打印表达式
    }

    std::string semicolonNode = GenName();  // 创建分号节点名称
    stream << name << " -> " << semicolonNode << ";\n";  // 连接 "Stmt" 到分号
    stream << semicolonNode << " [label=\";\"];\n";  // 创建子节点 ";"
}

void StmtAST1::Dump(std::ofstream& stream) const
{
}

void StmtAST2::Dump(std::ofstream& stream) const
{
}

// Stmt ::= LVal "=" Exp ";"
void StmtAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Stmt\"];\n";  // 创建父节点 "Stmt"

    if (lval)
    {
        std::string lvalNode = GenName();  // 生成左值节点名称
        stream << name << " -> " << lvalNode << ";\n";  // 连接 "Stmt" 到左值
        lval->Print(stream, lvalNode);  // 递归打印左值
    }

    std::string assignNode = GenName();
    stream << name << " -> " << assignNode << ";\n";  // 连接 "Stmt" 到 "="
    stream << assignNode << " [label=\"=\"];\n";  // 创建 "=" 节点

    if (exp)
    {
        std::string expNode = GenName();  // 生成表达式节点名称
        stream << name << " -> " << expNode << ";\n";  // 连接 "Stmt" 到表达式
        exp->Print(stream, expNode);  // 递归打印表达式
    }

    std::string semicolonNode = GenName();
    stream << name << " -> " << semicolonNode << ";\n";  // 连接 "Stmt" 到分号
    stream << semicolonNode << " [label=\";\"];\n";  // 创建子节点 ";"
}

void InitValAST::Dump(std::ofstream& stream) const
{
}

void StmtAST3::Dump(std::ofstream& stream) const
{
}

// Stmt ::= [Exp] ";"
void StmtAST3::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Stmt\"];\n";  // 创建父节点 "Stmt"

    // 如果有表达式，创建表达式节点并连接
    if (exp)
    {
        std::string expNode = GenName();  // 生成表达式节点名称
        stream << name << " -> " << expNode << ";\n";  // 连接 "Stmt" 到表达式
        exp->Print(stream, expNode);  // 递归打印表达式
    }

    // 创建分号节点
    std::string semicolonNode = GenName();  
    stream << name << " -> " << semicolonNode << ";\n";  // 连接 "Stmt" 到分号
    stream << semicolonNode << " [label=\";\"];\n";  // 创建子节点 ";"
}

void StmtAST4::Dump(std::ofstream& stream) const
{
}

// Stmt ::= Block
void StmtAST4::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Stmt\"];\n";  // 创建父节点 "Stmt"

    if (block)
    {
        std::string blockNode = GenName();  // 生成块节点名称
        stream << name << " -> " << blockNode << ";\n";  // 连接 "Stmt" 到 "Block"
        block->Print(stream, blockNode);  // 递归打印块
    }
}

void StmtAST5::Dump(std::ofstream& stream) const
{
}

// Stmt ::= "if" "(" Exp ")" Stmt ["else" Stmt]
void StmtAST5::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Stmt\"];\n";  // 创建父节点 "Stmt"

    std::string ifNode = GenName();
    stream << name << " -> " << ifNode << ";\n";  // 连接 "Stmt" 到 "if"
    stream << ifNode << " [label=\"if\"];\n";  // 创建子节点 "if"

    // 创建括号并连接
    std::string openParenNode = GenName();
    std::string closeParenNode = GenName();
    stream << ifNode << " -> " << openParenNode << ";\n";
    stream << openParenNode << " [label=\"(\"];\n";
    
    std::string expNode = GenName();
    stream << name << " -> " << expNode << ";\n";  // 连接 "Stmt" 到表达式
    exp->Print(stream, expNode);  // 递归打印表达式

    stream << ifNode << " -> " << closeParenNode << ";\n";
    stream << closeParenNode << " [label=\")\"];\n";

    // 连接到真分支
    std::string trueStmtNode = GenName();
    stream << name << " -> " << trueStmtNode << ";\n";  
    true_stmt->Print(stream, trueStmtNode);  // 递归打印真分支

    // 如果有假分支，连接它
    if (false_stmt)
    {
        std::string elseNode = GenName();
        stream << name << " -> " << elseNode << ";\n";  
        stream << elseNode << " [label=\"else\"];\n";  // 创建子节点 "else"
        std::string falseStmtNode = GenName();
        stream << elseNode << " -> " << falseStmtNode << ";\n";  
        false_stmt->Print(stream, falseStmtNode);  // 递归打印假分支
    }
}

void StmtAST6::Dump(std::ofstream& stream) const
{
}

// Stmt ::= "while" "(" Exp ")" Stmt
void StmtAST6::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Stmt\"];\n";  // 创建父节点 "Stmt"

    std::string whileNode = GenName();
    stream << name << " -> " << whileNode << ";\n";  // 连接 "Stmt" 到 "while"
    stream << whileNode << " [label=\"while\"];\n";  // 创建子节点 "while"

    // 创建括号并连接
    std::string openParenNode = GenName();
    std::string closeParenNode = GenName();
    stream << whileNode << " -> " << openParenNode << ";\n";
    stream << openParenNode << " [label=\"(\"];\n";

    std::string expNode = GenName();
    stream << name << " -> " << expNode << ";\n";  // 连接 "Stmt" 到表达式
    exp->Print(stream, expNode);  // 递归打印表达式

    stream << whileNode << " -> " << closeParenNode << ";\n";
    stream << closeParenNode << " [label=\")\"];\n";

    // 连接到循环体
    std::string stmtNode = GenName();
    stream << name << " -> " << stmtNode << ";\n";  
    stmt->Print(stream, stmtNode);  // 递归打印循环体
}

void StmtAST7::Dump(std::ofstream& stream) const
{
}

// Stmt ::= "break" ";"
void StmtAST7::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Stmt\"];\n";  // 创建父节点 "Stmt"

    std::string breakNode = GenName();
    stream << name << " -> " << breakNode << ";\n";  // 连接 "Stmt" 到 "break"
    stream << breakNode << " [label=\"break\"];\n";  // 创建子节点 "break"

    std::string semicolonNode = GenName();
    stream << name << " -> " << semicolonNode << ";\n";  // 连接到分号
    stream << semicolonNode << " [label=\";\"];\n";  // 创建子节点 ";"
}

void StmtAST8::Dump(std::ofstream& stream) const
{
}

// Stmt ::= "continue" ";"
void StmtAST8::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Stmt\"];\n";  // 创建父节点 "Stmt"

    std::string continueNode = GenName();
    stream << name << " -> " << continueNode << ";\n";  // 连接 "Stmt" 到 "continue"
    stream << continueNode << " [label=\"continue\"];\n";  // 创建子节点 "continue"

    std::string semicolonNode = GenName();
    stream << name << " -> " << semicolonNode << ";\n";  // 连接到分号
    stream << semicolonNode << " [label=\";\"];\n";  // 创建子节点 ";"
}

// UnaryExp ::= IDENT "(" [FuncRParams] ")"
void UnaryExpAST3::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"UnaryExp\"];\n";  // 创建父节点 "UnaryExp"

    // 创建标识符节点
    std::string identNode = GenName();
    stream << name << " -> " << identNode << ";\n";  
    stream << identNode << " [label=\"" << ident << "\"];\n";  // 创建标识符节点

    // 如果有参数，连接参数节点
    if (func_rparams)
    {
        std::string paramsNode = GenName();
        stream << name << " -> " << paramsNode << ";\n";  
        paramsNode = GenName();
        stream << paramsNode << " [label=\"(\"];\n";  // 创建左括号

        func_rparams->Print(stream, paramsNode);  // 递归打印函数参数

        std::string closeParenNode = GenName();
        stream << name << " -> " << closeParenNode << ";\n";  
        stream << closeParenNode << " [label=\")\"];\n";  // 创建右括号
    }
    else
    {
        // 表示没有参数的情况
        std::string openParenNode = GenName();
        std::string closeParenNode = GenName();
        stream << name << " -> " << openParenNode << ";\n";  
        stream << openParenNode << " [label=\"(\"];\n";  // 创建左括号
        
        stream << name << " -> " << closeParenNode << ";\n";  
        stream << closeParenNode << " [label=\")\"];\n";  // 创建右括号
    }
}

void FuncFParamAST::Dump(std::ofstream& stream) const
{
}

// FuncFParam ::= BType IDENT ["[" "]" [DimenConstExp]]
void FuncFParamAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"FuncFParam\"];\n";  // 创建父节点 "FuncFParam"

    // 打印基本类型
    if (btype)
    {
        std::string bTypeNode = GenName();  // 生成子节点名称
        stream << name << " -> " << bTypeNode << ";\n";  // 连接 "FuncFParam" 到 "BType"
        btype->Print(stream, bTypeNode);  // 递归打印基本类型
    }

    // 创建标识符的子节点
    std::string identNode = GenName();
    stream << name << " -> " << identNode << ";\n";  // 连接到标识符
    stream << identNode << " [label=\"" << ident << "\"];\n";  // 定义标识符节点

    // 如果存在维度常量表达式包装，则打印它
    if (dimen_const_exp_wrap)
    {
        std::string name1 = GenName();
        stream << name << " -> " << name1 << ";\n";
        stream << name1 << " [label=\"[]\"];\n";

        if (*dimen_const_exp_wrap)
        {
            std::string dimenConstExpNode = GenName();  // 生成子节点名称
            stream << name << " -> " << dimenConstExpNode << ";\n";  // 连接 "FuncFParam" 到 "DimenConstExp"
            (*dimen_const_exp_wrap)->Print(stream, dimenConstExpNode);  // 递归打印维度常量表达式
        }
    }
}

void UnaryExpAST3::Dump(std::ofstream& stream) const
{
}

void FuncRParamsAST::Dump(std::ofstream& stream) const
{
}

// FuncRParams ::= Exps
void FuncRParamsAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"FuncRParams\"];\n";  // 创建父节点 "FuncRParams"

    // 打印表达式列表
    if (exps)
    {
        std::string expsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << expsNode << ";\n";  // 连接 "FuncRParams" 到 "Exps"
        exps->Print(stream, expsNode);  // 递归打印表达式列表
    }
}

void FuncDefAST::Dump(std::ofstream& stream) const
{
}

// FuncDef ::= FuncType IDENT "(" [FuncFParams] ")" Block
void FuncDefAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"FuncDef\"];\n";
    std::string name1 = GenName();
    std::string name2 = GenName();
    std::string name3 = GenName();
    std::string name4 = GenName();
    std::string name5 = GenName();
    std::string name6 = GenName();
    stream << name << "->" << name1 << ";\n";
    func_type->Print(stream, name1);
    
    stream << name << "->" << name2 << ";\n";
    stream << name2 << " [label=\"" << ident << "\"];\n";

    stream << name << "->" << name3 << ";\n";
    stream << name3 << " [label=\"(\"];\n";

    if (func_fparams)
    {
        stream << name << "->" << name4 << ";\n";
        func_fparams->Print(stream, name4);
    }

    stream << name << "->" << name5 << ";\n";
    stream << name5 << " [label=\")\"];\n";
    
    stream << name << "->" << name6 << ";\n";
    block->Print(stream, name6);
}

void FuncFParamsAST::Dump(std::ofstream& stream) const
{
}

// FuncFParams ::= FuncFParam ["," FuncFParams]
void FuncFParamsAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"FuncFParams\"];\n";  // 创建父节点 "FuncFParams"

    // 打印函数参数
    if (func_fparam)
    {
        std::string funcFParamNode = GenName();  // 生成子节点名称
        stream << name << " -> " << funcFParamNode << ";\n";  // 连接 "FuncFParams" 到 "FuncFParam"
        func_fparam->Print(stream, funcFParamNode);  // 递归打印函数参数
    }

    // 如果存在更多函数参数，则打印逗号连接的下一个函数参数
    if (func_fparams)
    {
        std::string commaNode = GenName();  // 生成符号的子节点名称
        stream << name << " -> " << commaNode << ";\n";  // 连接到 ","
        stream << commaNode << " [label=\",\"];\n";  // 定义逗号节点

        std::string nextFuncFParamsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << nextFuncFParamsNode << ";\n";  // 连接 "FuncFParams" 到下一个 "FuncFParams"
        func_fparams->Print(stream, nextFuncFParamsNode);  // 递归打印下一个函数参数
    }
}

void VarDefsAST::Dump(std::ofstream& stream) const
{
}

// VarDefs ::= VarDef ["," VarDefs]
void VarDefsAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"VarDefs\"];\n";  // 创建父节点 "VarDefs"

    // 打印变量定义
    if (var_def)
    {
        std::string varDefNode = GenName();  // 生成子节点名称
        stream << name << " -> " << varDefNode << ";\n";  // 连接 "VarDefs" 到 "VarDef"
        var_def->Print(stream, varDefNode);  // 递归打印变量定义
    }

    // 如果存在更多变量定义，则打印逗号连接的下一个变量定义
    if (var_defs)
    {
        std::string commaNode = GenName();  // 生成符号的子节点名称
        stream << name << " -> " << commaNode << ";\n";  // 连接到 ","
        stream << commaNode << " [label=\",\"];\n";  // 定义逗号节点

        std::string nextVarDefsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << nextVarDefsNode << ";\n";  // 连接 "VarDefs" 到下一个 "VarDefs"
        var_defs->Print(stream, nextVarDefsNode);  // 递归打印下一个变量定义
    }
}

void ConstDefsAST::Dump(std::ofstream& stream) const
{
}

// ConstDefs ::= ConstDef ["," ConstDefs]
void ConstDefsAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"ConstDefs\"];\n";  // 创建父节点 "ConstDefs"

    // 打印常量定义
    if (const_def)
    {
        std::string constDefNode = GenName();  // 生成子节点名称
        stream << name << " -> " << constDefNode << ";\n";  // 连接 "ConstDefs" 到 "ConstDef"
        const_def->Print(stream, constDefNode);  // 递归打印常量定义
    }

    // 如果存在更多常量定义，则打印逗号连接的下一个常量定义
    if (const_defs)
    {
        std::string commaNode = GenName();  // 生成符号的子节点名称
        stream << name << " -> " << commaNode << ";\n";  // 连接到 ","
        stream << commaNode << " [label=\",\"];\n";  // 定义逗号节点

        std::string nextConstDefsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << nextConstDefsNode << ";\n";  // 连接 "ConstDefs" 到下一个 "ConstDefs"
        const_defs->Print(stream, nextConstDefsNode);  // 递归打印下一个常量定义
    }
}

void BlockItemsAST::Dump(std::ofstream& stream) const
{
}

// BlockItems ::= BlockItem [BlockItems]
void BlockItemsAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"BlockItems\"];\n";  // 创建父节点 "BlockItems"

    // 打印块项
    if (block_item)
    {
        std::string blockItemNode = GenName();  // 生成子节点名称
        stream << name << " -> " << blockItemNode << ";\n";  // 连接 "BlockItems" 到 "BlockItem"
        block_item->Print(stream, blockItemNode);  // 递归打印块项
    }

    // 如果存在更多块项，则递归打印下一个块项
    if (block_items)
    {
        std::string nextBlockItemsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << nextBlockItemsNode << ";\n";  // 连接到下一个 "BlockItems"
        block_items->Print(stream, nextBlockItemsNode);  // 递归打印下一个块项
    }
}

void CompUnitAST1::Dump(std::ofstream& stream) const
{
}

// CompUnit ::= [CompUnit] FuncDef
void CompUnitAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"CompUnit\"];\n";
    std::string name1 = GenName();
    std::string name2 = GenName();
    if (comp_unit)
    {
        stream << name << "->" << name1 << ";\n";
        comp_unit->Print(stream, name1);
    }
    stream << name << "->" << name2 << ";\n";
    func_def->Print(stream, name2);
}

void CompUnitAST2::Dump(std::ofstream& stream) const
{
}

// CompUnit ::= [CompUnit] Decl
void CompUnitAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"CompUnit\"];\n";
    std::string name1 = GenName();
    std::string name2 = GenName();
    if (comp_unit)
    {
        stream << name << "->" << name1 << ";\n";
        comp_unit->Print(stream, name1);
    }
    stream << name << "->" << name2 << ";\n";
    decl->Print(stream, name2);
}

void RootAST::Dump(std::ofstream& stream) const
{
}

// Root ::= CompUnit
void RootAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Root\"];\n";
    std::string name1 = GenName();
    stream << name << " -> " << name1 << ";\n";
    comp_unit->Print(stream, name1);
}

void ExpsAST::Dump(std::ofstream& stream) const
{
}

// Exps ::= Exp ["," Exps]
void ExpsAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"Exps\"];\n";  // 创建父节点 "Exps"

    // 打印表达式
    if (exp)
    {
        std::string expNode = GenName();  // 生成子节点名称
        stream << name << " -> " << expNode << ";\n";  // 连接 "Exps" 到 "Exp"
        exp->Print(stream, expNode);  // 递归打印表达式
    }

    // 如果存在更多表达式，则打印逗号连接的下一个表达式
    if (exps)
    {
        std::string commaNode = GenName();  // 生成符号的子节点名称
        stream << name << " -> " << commaNode << ";\n";  // 连接到 ","
        stream << commaNode << " [label=\",\"];\n";  // 定义逗号节点

        std::string nextExpsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << nextExpsNode << ";\n";  // 连接 "Exps" 到下一个 "Exps"
        exps->Print(stream, nextExpsNode);  // 递归打印下一个表达式
    }
}

void ConstInitValAST1::Dump(std::ofstream& stream) const
{
}

// ConstInitVal ::= ConstExp
void ConstInitValAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"ConstInitVal1\"];\n";  // 创建父节点 "ConstInitVal1"

    // 打印常量表达式
    if (const_exp)
    {
        std::string constExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << constExpNode << ";\n";  // 连接 "ConstInitVal1" 到 "ConstExp"
        const_exp->Print(stream, constExpNode);  // 递归打印常量表达式
    }
}

void ConstInitValAST2::Dump(std::ofstream& stream) const
{
}

// ConstInitVal ::= "{" [ConstInitVals] "}"
void ConstInitValAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"ConstInitVal2\"];\n";  // 创建父节点 "ConstInitVal2"

    // 创建左大括号节点
    std::string leftBraceNode = GenName();
    stream << name << " -> " << leftBraceNode << ";\n";  // 连接到 "{"
    stream << leftBraceNode << " [label=\"{\"];\n";  // 定义左大括号节点

    // 打印常量初始化值列表
    if (const_init_vals)
    {
        std::string constInitValsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << constInitValsNode << ";\n";  // 连接 "ConstInitVal2" 到 "ConstInitVals"
        const_init_vals->Print(stream, constInitValsNode);  // 递归打印常量初始化值列表
    }

    // 创建右大括号节点
    std::string rightBraceNode = GenName();
    stream << name << " -> " << rightBraceNode << ";\n";  // 连接到 "}"
    stream << rightBraceNode << " [label=\"}\"];\n";  // 定义右大括号节点
}

void InitValAST1::Dump(std::ofstream& stream) const
{
}

// InitVal ::= Exp
void InitValAST1::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"InitVal1\"];\n";  // 创建父节点 "InitVal1"

    // 打印表达式
    if (exp)
    {
        std::string expNode = GenName();  // 生成子节点名称
        stream << name << " -> " << expNode << ";\n";  // 连接 "InitVal1" 到 "Exp"
        exp->Print(stream, expNode);  // 递归打印表达式
    }
}

void InitValAST2::Dump(std::ofstream& stream) const
{
}

// InitVal ::= "{" [InitVals] "}"
void InitValAST2::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"InitVal2\"];\n";  // 创建父节点 "InitVal2"

    // 创建左大括号节点
    std::string leftBraceNode = GenName();
    stream << name << " -> " << leftBraceNode << ";\n";  // 连接到 "{"
    stream << leftBraceNode << " [label=\"{\"];\n";  // 定义左大括号节点

    // 打印初始化值列表
    if (init_vals)
    {
        std::string initValsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << initValsNode << ";\n";  // 连接 "InitVal2" 到 "InitVals"
        init_vals->Print(stream, initValsNode);  // 递归打印初始化值列表
    }

    // 创建右大括号节点
    std::string rightBraceNode = GenName();
    stream << name << " -> " << rightBraceNode << ";\n";  // 连接到 "}"
    stream << rightBraceNode << " [label=\"}\"];\n";  // 定义右大括号节点
}

void DimenConstExpAST::Dump(std::ofstream& stream) const
{
}

// DimenConstExp ::= "[" ConstExp "]" [DimenConstExp]
void DimenConstExpAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"DimenConstExp\"];\n";  // 创建父节点 "DimenConstExp"

    // 创建左方括号节点
    std::string leftBracketNode = GenName();
    stream << name << " -> " << leftBracketNode << ";\n";  // 连接到 "["
    stream << leftBracketNode << " [label=\"[\"];\n";  // 定义左方括号节点

    // 打印常量表达式
    if (const_exp)
    {
        std::string constExpNode = GenName();  // 生成子节点名称
        stream << name << " -> " << constExpNode << ";\n";  // 连接 "DimenConstExp" 到 "ConstExp"
        const_exp->Print(stream, constExpNode);  // 递归打印常量表达式
    }

    // 创建右方括号节点
    std::string rightBracketNode = GenName();
    stream << name << " -> " << rightBracketNode << ";\n";  // 连接到 "]"
    stream << rightBracketNode << " [label=\"]\"];\n";  // 定义右方括号节点

    // 如果存在更多维度常量表达式，则递归打印下一个维度常量表达式
    if (dimen_const_exp)
    {
        dimen_const_exp->Print(stream, name);  // 递归打印
    }
}

void ConstInitValsAST::Dump(std::ofstream& stream) const
{
}

// ConstInitVals ::= ConstInitVal ["," ConstInitVals]
void ConstInitValsAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"ConstInitVals\"];\n";  // 创建父节点 "ConstInitVals"

    // 打印常量初始化值
    if (const_init_val)
    {
        std::string constInitValNode = GenName();  // 生成子节点名称
        stream << name << " -> " << constInitValNode << ";\n";  // 连接 "ConstInitVals" 到 "ConstInitVal"
        const_init_val->Print(stream, constInitValNode);  // 递归打印常量初始化值
    }

    // 如果存在更多常量初始化值，则打印逗号连接的下一个常量初始化值
    if (const_init_vals)
    {
        std::string commaNode = GenName();  // 生成符号的子节点名称
        stream << name << " -> " << commaNode << ";\n";  // 连接到 ","
        stream << commaNode << " [label=\",\"];\n";  // 定义逗号节点

        std::string nextConstInitValsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << nextConstInitValsNode << ";\n";  // 连接 "ConstInitVals" 到下一个 "ConstInitVals"
        const_init_vals->Print(stream, nextConstInitValsNode);  // 递归打印下一个常量初始化值
    }
}

void InitValsAST::Dump(std::ofstream& stream) const
{
}

// InitVals ::= InitVal ["," InitVals]
void InitValsAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"InitVals\"];\n";  // 创建父节点 "InitVals"

    // 打印初始化值
    if (init_val)
    {
        std::string initValNode = GenName();  // 生成子节点名称
        stream << name << " -> " << initValNode << ";\n";  // 连接 "InitVals" 到 "InitVal"
        init_val->Print(stream, initValNode);  // 递归打印初始化值
    }

    // 如果存在更多初始化值，则打印逗号连接的下一个初始化值
    if (init_vals)
    {
        std::string commaNode = GenName();  // 生成符号的子节点名称
        stream << name << " -> " << commaNode << ";\n";  // 连接到 ","
        stream << commaNode << " [label=\",\"];\n";  // 定义逗号节点

        std::string nextInitValsNode = GenName();  // 生成子节点名称
        stream << name << " -> " << nextInitValsNode << ";\n";  // 连接 "InitVals" 到下一个 "InitVals"
        init_vals->Print(stream, nextInitValsNode);  // 递归打印下一个初始化值
    }
}

void DimenExpAST::Dump(std::ofstream& stream) const
{
}

// DimenExp ::= "[" Exp "]" [DimenExp]
void DimenExpAST::Print(std::stringstream& stream, std::string& name) const
{
    stream << name << " [label=\"DimenExp\"];\n";  // 创建父节点 "DimenExp"

    // 创建左方括号节点
    std::string leftBracketNode = GenName();
    stream << name << " -> " << leftBracketNode << ";\n";  // 连接到 "["
    stream << leftBracketNode << " [label=\"[\"];\n";  // 定义左方括号节点

    // 打印表达式
    if (exp)
    {
        std::string expNode = GenName();  // 生成子节点名称
        stream << name << " -> " << expNode << ";\n";  // 连接 "DimenExp" 到 "Exp"
        exp->Print(stream, expNode);  // 递归打印表达式
    }

    // 创建右方括号节点
    std::string rightBracketNode = GenName();
    stream << name << " -> " << rightBracketNode << ";\n";  // 连接到 "]"
    stream << rightBracketNode << " [label=\"]\"];\n";  // 定义右方括号节点

    // 如果存在更多维度表达式，则递归打印下一个维度表达式
    if (dimen_exp)
    {
        dimen_exp->Print(stream, name);  // 递归打印
    }
}

