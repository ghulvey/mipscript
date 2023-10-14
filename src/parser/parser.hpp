#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "syntaxTree.hpp"
#include <map>

class Parser {
public:
    Parser(std::fstream&);
    Parser();
    ~Parser();
    SyntaxTree* getAST();

    void parseStatement(SyntaxNode*, std::string&);
    void newLine(SyntaxNode*);
private:
    SyntaxTree* ast;
    std::map<std::string, StatementType> symbolTable;
    int lineNumber = 1;
};

#endif