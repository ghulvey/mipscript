#include "evaluator.hpp"
#include <iostream>

Evaluator::Evaluator() {
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

std::vector<std::string> Evaluator::getInstructions() {
    return this->instructions;
}

int Evaluator::availableStorageRegister() {
    for(int i = 0; i < 8; ++i) {
        if(!sRegistersAllocated[i]) {
            return i;
        }
    }
    return -1;
}

void Evaluator::evaluate() {
    evaluate(ast->getRoot());
}

void Evaluator::evaluate(SyntaxNode* node) {

    std::string instruction = "";
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

        // 1. Value is a constant
        if(node->getChildren()[0]->getType() == VALUE) {
            // Add the variable to the map
            sRegisters[reg] = std::stoi(node->getChildren()[0]->getValue());
            variables[node->getValue()] = reg + 16;

            // Add the instruction to the list
            instruction += "addi \t$s" + std::to_string(reg) + ", \t$zero, \t" + node->getChildren()[0]->getValue();
            variables[node->getValue()] = reg + 16;
        }

        // 2. Value is a variable
        

        // 3. Value is an expression

    } else if(node->getType() == COMMENT) {
        instruction += "# " + node->getValue();
    } else if(node->getType() == ASSIGNMENT) {
        // Get the variable location
        int reg = variables[node->getValue()] - 16;

        // Add the instruction to the list
        instruction += "addi \t$s" + std::to_string(reg) + ", \t$zero, \t" + node->getChildren()[0]->getValue();
        variables[node->getValue()] = reg + 16;
    }
    instructions.push_back(instruction);

    line++;
}
