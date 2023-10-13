#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP


#include <vector>
#include <string>

enum StatementType {
    INT_DEC,
    ASSIGNMENT,
    ADD,
    SUB,
    MUL,
    DIV,
    COMMENT,
    NEWLINE,
    VALUE,
    BLOCK
};

const std::string STATEMENT_NAMES[10] = {
    "INT_DEC",
    "ASSIGN",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "COMMENT",
    "NEWLINE",
    "VALUE",
    "BLOCK",
};

class SyntaxNode {
    public:
        SyntaxNode(StatementType type, std::string value);
        SyntaxNode(StatementType type);
        SyntaxNode(StatementType type, std::vector<SyntaxNode*> children);

        void removeChild(SyntaxNode* child);
        void addChild(SyntaxNode* child);

        StatementType getType();
        std::vector<SyntaxNode*> getChildren();
        std::string getValue();

        ~SyntaxNode();


    private:
        StatementType type;
        std::vector<SyntaxNode*> children;
        std::string value;
};

class SyntaxTree {
    public:
        SyntaxTree();
        ~SyntaxTree();
        SyntaxNode* getRoot();
        void setRoot(SyntaxNode* root);
        
        void printTree(SyntaxNode* node, int depth);

    private:
        SyntaxNode* root;

};

#endif
