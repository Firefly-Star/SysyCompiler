#include <cassert>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include "AST.h"

using namespace std;

// 声明 lexer 的输入, 以及 parser 函数
// 为什么不引用 sysy.tab.hpp 呢? 因为首先里面没有 yyin 的定义
// 其次, 因为这个文件不是我们自己写的, 而是被 Bison 生成出来的
// 你的代码编辑器/IDE 很可能找不到这个文件, 然后会给你报错 (虽然编译不会出错)
// 看起来会很烦人, 于是干脆采用这种看起来 dirty 但实际很有效的手段
extern FILE *yyin;
extern std::stringstream lexOutss;
extern int yyparse(unique_ptr<RootAST> &ast);

int main(int argc, const char *argv[]) {
    std::vector<std::ofstream> lexOutFiles;
    std::vector<std::ofstream> syntaxOutFiles;

    // compiler 输入文件 { 模式 输出文件 }
    assert(((argc % 2) == 0) && argc >= 4);

    auto input = argv[1];
    
    for (int i = 0;i < (argc - 2) / 2; ++i)
    {
        std::string mode = argv[i * 2 + 2];
        auto output = argv[i * 2 + 3];
        ofstream outFile(output);
        if (!outFile.is_open())
        {
            std::cout << "无法打开文件: " << output << "\n";
            return -1;
        }
        else
        {
            if (mode == "-l") // 词法分析输出
            {
                lexOutFiles.push_back(std::move(outFile));
            }
            else if (mode == "-s") // 抽象语法树输出 
            {
                syntaxOutFiles.push_back(std::move(outFile));
            }
            // TODO: 
            // 中间代码输出
            // riscv汇编代码输出
            else
            {
                std::cout << "未知的模式: " << mode << "\n";
                return -1;
            }
        }
    }
    yyin = fopen(input, "r");

    // 打开输入文件, 并且指定 lexer 在解析的时候读取这个文件
    assert(yyin);

    // 调用 parser 函数, parser 函数会进一步调用 lexer 解析输入文件的
    unique_ptr<RootAST> ast;
    auto ret = yyparse(ast);
    if (ret)
    {
        std::cout << "\n语法分析失败\n";
        return ret;
    }

    for (auto& lexOutFile : lexOutFiles)
    {
        lexOutFile << lexOutss.str();
    }

    std::stringstream ss;
    std::string name = "rootnode";
    ast->Print(ss, name);
    std::string syntaxOutstr = ss.str();
    for (auto& syntaxOutFile : syntaxOutFiles)
    {
        syntaxOutFile << syntaxOutstr;
    }
}
