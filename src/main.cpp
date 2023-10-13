#include "./parser/parser.hpp"
#include "./evaluator/evaluator.hpp"
#include <iostream>
#include <fstream>


int main(int argc, char** argv) {
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }
    std::fstream file(argv[1]);

    // Parse the file
    Parser p(file);

    // Evaluate the AST
    Evaluator e(p.getAST());
    e.evaluate();

    // Get the instructions
    std::vector<std::string> instructions = e.getInstructions();
    for(int i = 0; i < instructions.size(); ++i) {
        std::cout << instructions[i] << std::endl;
    }

    // Close the file
    file.close();

    return 0;
}