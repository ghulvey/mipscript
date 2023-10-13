#include "syntaxTree.hpp"
#include <iostream>

SyntaxTree::SyntaxTree() {
    this->root = new SyntaxNode(BLOCK);
}

SyntaxTree::~SyntaxTree() {
    delete this->root;
}

SyntaxNode* SyntaxTree::getRoot() {
    return this->root;
}

void SyntaxTree::setRoot(SyntaxNode* root) {
    this->root = root;
}

void SyntaxTree::printTree(SyntaxNode* node, int depth) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    std::cout << STATEMENT_NAMES[node->getType()] << ": " << node->getValue() << ";" << std::endl;
    
    for (int i = 0; i < node->getChildren().size(); i++) {
        this->printTree(node->getChildren()[i], depth + 1);
    }
}