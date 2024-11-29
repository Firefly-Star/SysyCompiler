#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <fstream>
#include <type_traits>
#include "SysyType.h"

// Ϊ�˷��㣬�Ͱ���ĳ�Աȫ����¶�����ˣ��ĵ�ʱ��ע��һ��

// ȫ�ֵ�һ���������δ�������滻��fstream

// �����࣬���ڶ���һ��ͨ�õ� Koopa ����ӿ�
class KoopaComponent {
public:
    virtual ~KoopaComponent() = default; // ����������
    virtual void Dump() const = 0;        // �������ɴ���
};

inline std::ostream& koopaOut = std::cout;

// ֵ��ȫ�ֱ����ͺ��������� Ŀǰ֧�ָ�������32λ�з�������
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

// ָ��
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

// ������
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

// ����
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

// ����
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