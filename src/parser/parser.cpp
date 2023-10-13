
#include "parser.hpp"
#include "syntaxTree.hpp"
#include <iostream>
#include <fstream>

void removeLeadingWhitespace(std::string &str) {
    int i = 0;
    char c = str[i];
    while(c == ' ') {
        i++;
        c = str[i];
    }
    str = str.substr(i);
}

Parser::Parser() {
    ast = new SyntaxTree();
}

Parser::Parser(std::fstream &file) {
    std::string line;
    ast = new SyntaxTree();
    while(std::getline(file, line)) {
        std::cout << line << std::endl;
        // Determine the type of statement
        removeLeadingWhitespace(line);
        if(line == "") {
            newLine(ast->getRoot());
        } else {
            parseStatement(ast->getRoot(), line);
        }
    } 

    ast->printTree(ast->getRoot(), 0);
}

Parser::~Parser() {
    delete this->ast;
}

SyntaxTree* Parser::getAST() {
    return this->ast;
}

void Parser::newLine(SyntaxNode* root) {
    root->addChild(new SyntaxNode(NEWLINE));
}

void Parser::parseStatement(SyntaxNode* root, std::string &statement) {
    
    // Get the type of the statement
    int i = 0;
    char c = statement[i];
    while(c != ' ' && c != '(' && c != '}') {
        i++;
        c = statement[i];
    }
    std::string type = statement.substr(0, i);

    if(type == "int") {
        // Get the variable name
        std::string variableName = "";
        while(c != '=') {
            if(c != ' ') {variableName += c;}
            c = statement[i];
            i++;
        }
    
        // Get the value
        std::string value = "";
        while(c != ';') {
            if(c != ' ' && c != '=') {value += c;}
            i++;
            c = statement[i];
        }

        if(value == "") {value = "0";}

        // Add to syntax tree
        SyntaxNode* dec = new SyntaxNode(INT_DEC, variableName);
        dec->addChild(new SyntaxNode(VALUE, value));
        root->addChild(dec);
    }

}