#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <string>
#include "../parser/parser.hpp"
#include "../parser/syntaxTree.hpp"
#include <map>

const std::string REGISTER_NAMES[32] = {
    "$zero",
    "$at",
    "$v0",
    "$v1",
    "$a0",
    "$a1",
    "$a2",
    "$a3",
    "$t0",
    "$t1",
    "$t2",
    "$t3",
    "$t4",
    "$t5",
    "$t6",
    "$t7",
    "$s0",
    "$s1",
    "$s2",
    "$s3",
    "$s4",
    "$s5",
    "$s6",
    "$s7",
    "$t8",
    "$t9",
    "$k0",
    "$k1",
    "$gp",
    "$sp",
    "$fp",
    "$ra"
};

const int S_REGISTERS = 8;
const int S_REGISTER_OFFSET = 16;
const int T_REGISTERS = 8;
const int T_REGISTER_OFFSET = 8;
const int A_REGISTERS = 4;
const int A_REGISTER_OFFSET = 4;
const int V_REGISTERS = 2;
const int V_REGISTER_OFFSET = 2;
class Compiler {
public:
    Compiler();
    Compiler(SyntaxTree* ast) : Compiler() { this->ast = ast; }
    void evaluate();
    void evaluate(SyntaxNode* node);
    std::vector<std::string> getInstructions();

private:
    SyntaxTree* ast;
    std::map<std::string, int> variables;
    std::map<std::string, int> functions;
    int sRegisters[8];
    int tRegisters[8];
    int aRegisters[4];
    int vRegisters[2];
    bool sRegistersAllocated[8];
    bool tRegistersAllocated[8];
    bool aRegistersAllocated[4];
    bool vRegistersAllocated[2];
    int memory[1024];
    std::vector<std::string> instructions;

    int line = 1;

    int availableStorageRegister();
    void arithmeticEvaluation(SyntaxNode*, int reg);
};

#endif