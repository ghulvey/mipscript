#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include <string>
#include "../parser/parser.hpp"
#include "../parser/syntaxTree.hpp"
#include <map>

const int S_REGISTERS = 8;
const int S_REGISTER_OFFSET = 16;
const int T_REGISTERS = 8;
const int T_REGISTER_OFFSET = 8;
const int A_REGISTERS = 4;
const int A_REGISTER_OFFSET = 4;
const int V_REGISTERS = 2;
const int V_REGISTER_OFFSET = 2;
class Evaluator {
public:
    Evaluator();
    Evaluator(SyntaxTree* ast) : Evaluator() { this->ast = ast; }
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
};

#endif