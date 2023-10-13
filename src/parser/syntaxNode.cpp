#include "syntaxTree.hpp"

SyntaxNode::SyntaxNode(StatementType type, std::string value) {
    this->type = type;
    this->value = value;
}

SyntaxNode::SyntaxNode(StatementType type) {
    this->type = type;
}

SyntaxNode::SyntaxNode(StatementType type, std::vector<SyntaxNode*> children) {
    this->type = type;
    this->children = children;
}

void SyntaxNode::removeChild(SyntaxNode* child) {
    for (int i = 0; i < this->children.size(); i++) {
        if (this->children[i] == child) {
            this->children.erase(this->children.begin() + i);
            break;
        }
    }
}

SyntaxNode::~SyntaxNode() {
    for(int i = 0; i < this->children.size(); i++) {
        delete this->children[i];
    }
}

void SyntaxNode::addChild(SyntaxNode* child) {
    this->children.push_back(child);
}

StatementType SyntaxNode::getType() {
    return this->type;
}

std::vector<SyntaxNode*> SyntaxNode::getChildren() {
    return this->children;
}

std::string SyntaxNode::getValue() {
    return this->value;
}