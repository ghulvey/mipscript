#include <iostream>
#include "../src/parser/parser.hpp"
#include "../src/compiler/compiler.hpp"
#include "../src/parser/syntaxTree.hpp"
#include <gtest/gtest.h>

TEST(Addition, TwoValues) {
    std::string statement = "int a = 1 + 2;";
    Parser p;
    p.parseStatement(p.getAST()->getRoot(), statement);
    SyntaxNode* root = p.getAST()->getRoot();

    EXPECT_EQ(root->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[0]->getType(), INT_DEC);
    EXPECT_EQ(root->getChildren()[0]->getValue(), "a");
    EXPECT_EQ(root->getChildren()[0]->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getType(), ADD);
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getChildren().size(), 2);
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getChildren()[0]->getType(), VALUE);
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getChildren()[0]->getValue(), "1");
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getChildren()[1]->getType(), VALUE);
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getChildren()[1]->getValue(), "2");


    Compiler c(p.getAST());
    c.evaluate();
    std::vector<std::string> instructions = c.getInstructions();
    EXPECT_EQ(instructions.size(), 3);
    EXPECT_EQ(instructions[0], "addi \t$s0, \t$zero, \t1");
    EXPECT_EQ(instructions[1], "addi \t$s0, \t$s0, \t2");
}

TEST(Addition, VariableValue) {
    std::string statement = "int a = 1; int b = a + 2;";
    Parser p;
    p.parseStatement(p.getAST()->getRoot(), statement);
    SyntaxNode* root = p.getAST()->getRoot();

    EXPECT_EQ(root->getChildren().size(), 2);
    EXPECT_EQ(root->getChildren()[0]->getType(), INT_DEC);
    EXPECT_EQ(root->getChildren()[0]->getValue(), "a");
    EXPECT_EQ(root->getChildren()[0]->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getType(), VALUE);
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getValue(), "1");

    EXPECT_EQ(root->getChildren()[1]->getType(), INT_DEC);
    EXPECT_EQ(root->getChildren()[1]->getValue(), "b");
    EXPECT_EQ(root->getChildren()[1]->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[1]->getChildren()[0]->getType(), ADD);
    EXPECT_EQ(root->getChildren()[1]->getChildren()[0]->getChildren().size(), 2);
    EXPECT_EQ(root->getChildren()[1]->getChildren()[0]->getChildren()[0]->getType(), VARIABLE);
    EXPECT_EQ(root->getChildren()[1]->getChildren()[0]->getChildren()[0]->getValue(), "a");
    EXPECT_EQ(root->getChildren()[1]->getChildren()[0]->getChildren()[1]->getType(), VALUE);
    EXPECT_EQ(root->getChildren()[1]->getChildren()[0]->getChildren()[1]->getValue(), "2");
}

TEST(Addition, TwoVariable) {
    std::string statement = "int a = 1; int b = 2; int c = a + b;";
    Parser p;
    p.parseStatement(p.getAST()->getRoot(), statement);
    SyntaxNode* root = p.getAST()->getRoot();

    EXPECT_EQ(root->getChildren().size(), 2); // Should be 3
    EXPECT_EQ(root->getChildren()[0]->getType(), INT_DEC);
    EXPECT_EQ(root->getChildren()[0]->getValue(), "a");
    EXPECT_EQ(root->getChildren()[0]->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getType(), VALUE);
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getValue(), "1");

    EXPECT_EQ(root->getChildren()[1]->getType(), INT_DEC);
    EXPECT_EQ(root->getChildren()[1]->getValue(), "b");
    EXPECT_EQ(root->getChildren()[1]->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[1]->getChildren()[0]->getType(), VALUE);
    EXPECT_EQ(root->getChildren()[1]->getChildren()[0]->getValue(), "2");

    EXPECT_EQ(root->getChildren()[2]->getType(), INT_DEC);
    EXPECT_EQ(root->getChildren()[2]->getValue(), "c");
    EXPECT_EQ(root->getChildren()[2]->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[2]->getChildren()[0]->getType(), ADD);
    EXPECT_EQ(root->getChildren()[2]->getChildren()[0]->getChildren().size(), 2);
    EXPECT_EQ(root->getChildren()[2]->getChildren()[0]->getChildren()[0]->getType(), VARIABLE);
    EXPECT_EQ(root->getChildren()[2]->getChildren()[0]->getChildren()[0]->getValue(), "a");
    EXPECT_EQ(root->getChildren()[2]->getChildren()[0]->getChildren()[1]->getType(), VARIABLE);
    EXPECT_EQ(root->getChildren()[2]->getChildren()[0]->getChildren()[1]->getValue(), "b");
}