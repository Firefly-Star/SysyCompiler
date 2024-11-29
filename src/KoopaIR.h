#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <fstream>
#include <type_traits>
#include "SysyType.h"

// 为了方便，就把类的成员全部暴露出来了，改的时候注意一点

// 全局的一个输出流，未来可以替换成fstream

// 抽象类，用于定义一个通用的 Koopa 组件接口
class KoopaComponent {
public:
    virtual ~KoopaComponent() = default; // 虚析构函数
    virtual void Dump() const = 0;        // 用于生成代码
};

inline std::ostream& koopaOut = std::cout;

// 值（全局变量和函数参数） 目前支持浮点数和32位有符号整数
class KoopaValue : public KoopaComponent {
public:
    std::variant<int, float, NoneType_t> value;
    std::string name;
    bool isGlobal;

public:
    virtual void Dump() const override = 0;
};

inline void DumpValue(std::variant<int, float, NoneType_t> const& value)
{
    std::visit([](auto const& value){
        using value_type = std::remove_const_t<std::remove_reference_t<decltype(value)>>;
        if constexpr(std::is_same_v<value_type, int> || std::is_same_v<value_type, float>)
        {
            koopaOut << value << " ";
        }
    }, value);
}

class KoopaConstant : public KoopaValue
{
public:
    virtual void Dump() const override
    {
        
    }
};

class KoopaImmediate : public KoopaConstant
{
public:
    virtual void Dump() const override
    {
        DumpValue(value);
    }
};

// 指令
class KoopaInstruction : public KoopaComponent {
public:
    void Dump() const = 0;
};

class KoopaReturnInstruction : public KoopaInstruction
{
public:
    std::shared_ptr<KoopaValue> returnValue;
public:
    void Dump() const override
    {
        koopaOut << "ret ";
        returnValue->Dump();
        koopaOut << "\n";
    }
};

// 基本块
class KoopaBasicBlock : public KoopaComponent {
public:
    std::string name;
    std::vector<std::shared_ptr<KoopaInstruction>> instructions;

public:
    KoopaBasicBlock(const std::string& name) 
        : name(name) {}

    void Dump() const override
    {
        koopaOut << name << ":\n";
        for (const auto& instruction : instructions) 
        {
            instruction->Dump();
        }
    }
};

// 函数
class KoopaFunction : public KoopaComponent {
public:
    std::string name;
    SysyType returnType;
    std::vector<std::shared_ptr<KoopaValue>> params;
    std::vector<std::shared_ptr<KoopaBasicBlock>> blocks;

public:
    KoopaFunction(const std::string& name) 
        : name(name) {}

    void Dump() const override
    {
        std::string returnTypeDeclaration;
        switch(returnType)
        {
            case SysyType::INT: returnTypeDeclaration = "i32";
        }
        koopaOut << "fun " << name << "(): " << returnTypeDeclaration << "{";
        for (auto const& block : blocks)
        {
            block->Dump();
        }
        koopaOut << "}";
    }
};

// 程序
class KoopaProgram : public KoopaComponent {
public:
    std::vector<std::shared_ptr<KoopaValue>> globals;
    std::vector<std::shared_ptr<KoopaFunction>> functions;

public:
    void Dump() const override
    {
        for (auto const& function : functions)
        {
            function->Dump();
        }
    }
};