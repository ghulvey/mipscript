#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP


#include <vector>
#include <string>

enum StatementType {
    INT_DEC,
    ASSIGNMENT,
    VARIABLE,
    ADD,
    SUB,
    MUL,
    DIV,
    COMMENT,
    NEWLINE,
    VALUE,
    BLOCK,
    INT_ASSIGN,
    INT_VAR,
    PRINT,
};

const std::string STATEMENT_NAMES[14] = {
    "INT_DEC",
    "ASSIGN",
    "VARIABLE",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "COMMENT",
    "NEWLINE",
    "VALUE",
    "BLOCK",
    "INT_ASSIGN",
    "INT",
    "PRINT"
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
