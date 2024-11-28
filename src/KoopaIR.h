#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant>

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
    std::variant<int, float> value;
    std::string name;
    bool isGlobal;

public:
    KoopaValue(const std::string& name, bool isGlobal) 
        : name(name), isGlobal(isGlobal) {}

    void Dump() const override
    {
        if(isGlobal)
        {
            koopaOut << "@" << name << ": ";
        }
        else
        {
            koopaOut << "%" << name << ": ";
        }
    }
};

// ָ��
class KoopaInstruction : public KoopaComponent {
public:
    enum class InstructionType 
    { 
        BINARY, ASSIGN, CALL, RETURN 
    };

public:
    InstructionType type;
    KoopaValue result;
    std::vector<KoopaValue> operands;

public:
    KoopaInstruction(InstructionType type, KoopaValue result)
        : type(type), result(result) {}

    void Dump() const override
    {
        if (type == InstructionType::RETURN) 
        {
        }
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
    std::vector<KoopaValue> params;
    std::shared_ptr<KoopaBasicBlock> entryBlock;

public:
    KoopaFunction(const std::string& name) 
        : name(name) {}

    void Dump() const override
    {
        koopaOut << "fun @" << name << "(): i32 {\n"; // ���践�������� i32
        if (entryBlock) 
        {
            entryBlock->Dump();
        }
        koopaOut << "}\n";
    }
};

// ����
class KoopaProgram : public KoopaComponent {
public:
    std::vector<KoopaValue> globals;
    std::vector<KoopaFunction> functions;

public:
    void Dump() const override
    {
        for (auto const& function : functions)
        {
            function.Dump();
        }
    }
};