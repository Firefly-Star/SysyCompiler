#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <type_trait>
#include "SysyType.h"

// Ϊ�˷��㣬�Ͱ���ĳ�Աȫ����¶�����ˣ��ĵ�ʱ��ע��һ��

// ȫ�ֵ�һ���������δ�������滻��fstream
std::ostream& koopaOut = std::cout;

// �����࣬���ڶ���һ��ͨ�õ� Koopa ����ӿ�
class KoopaComponent {
public:
    virtual ~KoopaComponent() = default; // ����������
    virtual void Dump() const = 0;        // �������ɴ���
};

// ֵ��ȫ�ֱ����ͺ��������� Ŀǰ֧�ָ�������32λ�з�������
class KoopaValue : public KoopaComponent {
public:
    std::variant<int, float, Nonetype_t> value;
    std::string name;
    bool isGlobal;

public:
    virtual void Dump() const override = 0;
};

void Dump(std::variant<int, float, NoneType_t> const& value)
{
    std::visit([](auto& value){
        using value_type = std::
    })
}

class KoopaConstant : public KoopaValue
{
public:
    virtual void Dump() const override
    {
        switch(type)
        {
            case
        }
    }
};

// ָ��
class KoopaInstruction : public KoopaComponent {
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
    }
}

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
        koopaOut << "%" << name << ":\n";
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
    std::vector<std::shared_ptr<KoopaValue>> params;
    std::vector<std::shared_ptr<KoopaBasicBlock>> blocks;

public:
    KoopaFunction(const std::string& name) 
        : name(name) {}

    void Dump() const override
    {
        for (auto const& block : blocks)
        {
            block->Dump();
        }
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