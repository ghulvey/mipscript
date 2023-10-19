#include "./parser/parser.hpp"
#include "./parser/syntaxTree.hpp"
#include "./evaluator/evaluator.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <emscripten/bind.h>

using namespace emscripten;


std::string evalCode(std::string code) {

    std::vector<std::string> lines;
    std::istringstream iss(code);
    std::string line;
    while (std::getline(iss, line)) {
        lines.push_back(line);
    }

    Parser p;

    for(int i = 0; i < lines.size(); ++i) {
        p.parseStatement(p.getAST()->getRoot(), lines[i]);
    }
    
    
    SyntaxNode* root = p.getAST()->getRoot();

    Compiler e(p.getAST());
    e.evaluate();

    std::vector<std::string> instructions = e.getInstructions();
    // for(int i = 0; i < instructions.size(); ++i) {
    //     std::cout << instructions[i] << std::endl;
    // }

    std::string instructionsString = "";
    for(int i = 0; i < instructions.size(); ++i) {
        instructionsString += instructions[i] + "\n";
    }

    return instructionsString;
}


EMSCRIPTEN_BINDINGS(mipscript_wasm) {
    function("evalCode", &evalCode, allow_raw_pointers());
}

