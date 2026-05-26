# SysY Compiler

A compiler for the SysY programming language (a subset of C), built with C++ using Flex and Bison.

## Description

SysY Compiler translates SysY source code into target code through lexical analysis, syntax analysis, semantic analysis, and code generation. SysY is a simplified C-like language used for compiler design education.

## Features

- Lexical analysis with Flex
- Syntax analysis with Bison (LALR parser)
- Abstract Syntax Tree (AST) generation
- Support for int/float types, arrays, functions, control flow

## Recognized Grammar

The compiler supports a complete subset of SysY grammar including:
- Variable declarations (int, float, const)
- Function definitions
- Control flow statements
- Multi-dimensional arrays
- Initializer expressions

## Build

```bash
make
```

## Tech Stack

- C++
- Flex (lexical analysis)
- Bison (syntax analysis)
