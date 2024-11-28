#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant>

// 为了方便，就把类的成员全部暴露出来了，改的时候注意一点

// 全局的一个输出流，未来可以替换成fstream
std::ostream& koopaOut = std::cout;

// 抽象类，用于定义一个通用的 Koopa 组件接口
class KoopaComponent {
public:
    virtual ~KoopaComponent() = default; // 虚析构函数
    virtual void Dump() const = 0;        // 用于生成代码
};

// 值（全局变量和函数参数） 目前支持浮点数和32位有符号整数
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

// 指令
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
        koopaOut << "%" << name << ":\n";
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
    std::vector<KoopaValue> params;
    std::shared_ptr<KoopaBasicBlock> entryBlock;

public:
    KoopaFunction(const std::string& name) 
        : name(name) {}

    void Dump() const override
    {
        koopaOut << "fun @" << name << "(): i32 {\n"; // 假设返回类型是 i32
        if (entryBlock) 
        {
            entryBlock->Dump();
        }
        koopaOut << "}\n";
    }
};

// 程序
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