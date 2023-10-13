
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
    removeLeadingWhitespace(statement);
    if(statement == "") {
        newLine(root);
        return;
    }

    int i = 0;
    // Check if the statement is a comment
    if(statement[i] == '#') {
        ++i;
        if(statement[i] == '#') {
            ++i;
            while(statement[i] == ' ') {++i;}
            // Add the comment to the syntax tree
            std::cout << "Adding comment: " << statement.substr(i) << std::endl;
            SyntaxNode* comment = new SyntaxNode(COMMENT, statement.substr(i));
            root->addChild(comment);
            return;
        }
        return;
    }
    
    // Get the type of the statement
    char c = statement[i];
    while(c != ' ' && c != '(' && c != '}' && c != ';') {
        i++;
        c = statement[i];
    }
    std::string type = statement.substr(0, i);

    // Check for variable assignment
    if(statement[i] == '=' || statement[i+1] == '=') {
        std::string value = "";
        while(c != ';') {
            if(c != ' ' && c != '=') {value += c;}
            i++;
            c = statement[i];
        }
        SyntaxNode* assign = new SyntaxNode(ASSIGNMENT, type);
        assign->addChild(new SyntaxNode(VALUE, value));
        root->addChild(assign);
        return;
    }

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