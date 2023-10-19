#include "compiler.hpp"
#include <iostream>

Compiler::Compiler() {
    // Initialize all registers and memory to 0
    for(int i = 0; i < S_REGISTERS; ++i) {
        sRegisters[i] = 0;
        sRegistersAllocated[i] = false;
    }
    for(int i = 0; i < T_REGISTERS; ++i) {
        tRegisters[i] = 0;
        tRegistersAllocated[i] = false;
    }
    for(int i = 0; i < A_REGISTERS; ++i) {
        aRegisters[i] = 0;
        aRegistersAllocated[i] = false;
    }
    for(int i = 0; i < V_REGISTERS; ++i) {
        vRegisters[i] = 0;
        vRegistersAllocated[i] = false;
    }
    for(int i = 0; i < 1024; ++i) {
        memory[i] = 0;
    }
}

std::vector<std::string> Compiler::getInstructions() {
    return this->instructions;
}

int Compiler::availableStorageRegister() {
    for(int i = 0; i < 8; ++i) {
        if(!sRegistersAllocated[i]) {
            return i;
        }
    }
    return -1;
}

void Compiler::evaluate() {
    evaluate(ast->getRoot());
}

void Compiler::evaluate(SyntaxNode* node) {

    if(node->getType() == BLOCK) {
        for(int i = 0; i < node->getChildren().size(); ++i) {
            evaluate(node->getChildren()[i]);
        }
    } else if(node->getType() == INT_DEC) {
        int reg = availableStorageRegister();
        if(reg == -1) {
            throw std::runtime_error("No available registers");
        }

        if(variables.find(node->getValue()) != variables.end()) {
            throw std::runtime_error("Line: " + std::to_string(line) + ", Variable " + node->getValue() + " already declared");
        }

        reg = availableStorageRegister();
        sRegistersAllocated[reg] = true;
        variables[node->getValue()] = reg + 16;
        std::cout << variables[node->getValue()] << std::endl;
        arithmeticEvaluation(node, reg + 16);
        return;

    } else if(node->getType() == COMMENT) {
        instructions.push_back("# " + node->getValue());
    } else if(node->getType() == INT_ASSIGN) {
        // Get the variable location
        int reg = variables[node->getValue()];
        arithmeticEvaluation(node, reg);
        return;
    } else if(node->getType() == PRINT) {
        instructions.push_back("addi \t$v0, \t$zero, \t1");
        arithmeticEvaluation(node, 4);
        instructions.push_back("syscall");
    } else {
        instructions.push_back("");
    }

    line++;
}


void Compiler::arithmeticEvaluation(SyntaxNode* node, int reg) {

    // 1. Value is a constant
    if(node->getChildren()[0]->getType() == VALUE) {
        instructions.push_back("addi \t" + REGISTER_NAMES[reg] + ", \t$zero, \t" + node->getChildren()[0]->getValue()); 
    }

    // 2. Value is a variable
    else if(node->getChildren()[0]->getType() == VARIABLE) {
        // Get the variable location
        int varReg = variables[node->getChildren()[0]->getValue()];

        // Add the instruction to the list
        instructions.push_back("add \t" + REGISTER_NAMES[reg] + ", \t$zero, \t" + REGISTER_NAMES[varReg]);
    }

}