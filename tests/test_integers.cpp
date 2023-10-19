#include <iostream>
#include "../src/parser/parser.hpp"
#include "../src/compiler/compiler.hpp"
#include "../src/parser/syntaxTree.hpp"
#include <gtest/gtest.h>

namespace {

void testIntegerParsingCase(std::string statement, std::string variableName, int num, std::string instruction = "") {
    std::cout << "Testing: " << statement;
    Parser p;
    p.parseStatement(p.getAST()->getRoot(), statement);
    SyntaxNode* root = p.getAST()->getRoot();

    EXPECT_EQ(root->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[0]->getType(), INT_DEC);
    EXPECT_EQ(root->getChildren()[0]->getValue(), variableName);
    EXPECT_EQ(root->getChildren()[0]->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getType(), VALUE);
    EXPECT_EQ(stoi(root->getChildren()[0]->getChildren()[0]->getValue()), num);

    Compiler c(p.getAST());
    c.evaluate();
    std::vector<std::string> instructions = c.getInstructions();
    EXPECT_EQ(instructions.size(), 1);
    EXPECT_EQ(instructions[0], instruction);

}

TEST(IntParsing, BasicAssertion) {
    testIntegerParsingCase("int a = 1;", "a", 1, "addi \t$s0, \t$zero, \t1");
    
}

TEST(IntParsing, ZeroAssertion) {
    testIntegerParsingCase("int a = 0;", "a", 0, "addi \t$s0, \t$zero, \t0");
}

TEST(IntParsing, NegativeAssertion) {
    testIntegerParsingCase("int a = -1;", "a", -1, "addi \t$s0, \t$zero, \t-1");
}

TEST(IntParsing, NoAssignment) {
    testIntegerParsingCase("int a;", "a", 0, "addi \t$s0, \t$zero, \t0");
}

TEST(IntParsing, CopyAssignment) {
    std::cout << "Testing: " << "int a = 1; int b = a;" << std::endl;
    std::string statement1 = "int a = 10;";
    std::string statement2 = "int b = a;";
    Parser p;
    p.parseStatement(p.getAST()->getRoot(), statement1);
    p.parseStatement(p.getAST()->getRoot(), statement2);
    SyntaxNode* root = p.getAST()->getRoot();

    EXPECT_EQ(root->getChildren().size(), 2);
    
    EXPECT_EQ(root->getChildren()[0]->getType(), INT_DEC);
    EXPECT_EQ(root->getChildren()[0]->getValue(), "a");
    EXPECT_EQ(root->getChildren()[0]->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[0]->getChildren()[0]->getType(), VALUE);
    EXPECT_EQ(stoi(root->getChildren()[0]->getChildren()[0]->getValue()), 10);

    EXPECT_EQ(root->getChildren()[1]->getType(), INT_DEC);
    EXPECT_EQ(root->getChildren()[1]->getValue(), "b");
    EXPECT_EQ(root->getChildren()[1]->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[1]->getChildren()[0]->getType(), VARIABLE);
    EXPECT_EQ(root->getChildren()[1]->getChildren()[0]->getValue(), "a");

    Compiler c(p.getAST());
    c.evaluate();
    std::vector<std::string> instructions = c.getInstructions();
    EXPECT_EQ(instructions.size(), 2);
    EXPECT_EQ(instructions[0], "addi \t$s0, \t$zero, \t10");
    EXPECT_EQ(instructions[1], "add \t$s1, \t$zero, \t$s0");

}

TEST(IntParsing, LongAssertion) {
    testIntegerParsingCase("int longName = 123456789;", "longName", 123456789, "addi \t$s0, \t$zero, \t123456789");
}

TEST(IntParsing, MaxAssertion) {
    testIntegerParsingCase("int longNum = 2147483647;", "longNum", 2147483647, "addi \t$s0, \t$zero, \t2147483647");
}

TEST(IntParsing, MinAssertion) {
    testIntegerParsingCase("int longNegNum = -2147483648;", "longNegNum", -2147483648, "addi \t$s0, \t$zero, \t-2147483648");
}

TEST(IntParsing, ValueAssignment) {
    std::string statementA = "int a = 1;";
    std::string statementB = "a = 10;";

    Parser p;
    p.parseStatement(p.getAST()->getRoot(), statementA);
    p.parseStatement(p.getAST()->getRoot(), statementB);

    SyntaxNode* root = p.getAST()->getRoot();
    ASSERT_EQ(root->getChildren().size(), 2);
    ASSERT_EQ(root->getChildren()[0]->getType(), INT_DEC);
    ASSERT_EQ(root->getChildren()[0]->getValue(), "a");
    ASSERT_EQ(root->getChildren()[0]->getChildren().size(), 1);
    ASSERT_EQ(root->getChildren()[0]->getChildren()[0]->getType(), VALUE);
    ASSERT_EQ(stoi(root->getChildren()[0]->getChildren()[0]->getValue()), 1);

    ASSERT_EQ(root->getChildren()[1]->getType(), INT_ASSIGN);
    ASSERT_EQ(root->getChildren()[1]->getValue(), "a");
    ASSERT_EQ(root->getChildren()[1]->getChildren().size(), 1);
    ASSERT_EQ(root->getChildren()[1]->getChildren()[0]->getType(), VALUE);
    ASSERT_EQ(stoi(root->getChildren()[1]->getChildren()[0]->getValue()), 10);
}

TEST(IntParsing, VariableAssignment) {
    std::string statementA = "int a = 1;";
    std::string statementB = "int b = 10;";
    std::string statementC = "a = b;";

    Parser p;
    p.parseStatement(p.getAST()->getRoot(), statementA);
    p.parseStatement(p.getAST()->getRoot(), statementB);
    p.parseStatement(p.getAST()->getRoot(), statementC);

    SyntaxNode* root = p.getAST()->getRoot();
    ASSERT_EQ(root->getChildren().size(), 3);

    ASSERT_EQ(root->getChildren()[0]->getType(), INT_DEC);
    ASSERT_EQ(root->getChildren()[0]->getValue(), "a");
    ASSERT_EQ(root->getChildren()[0]->getChildren().size(), 1);
    ASSERT_EQ(root->getChildren()[0]->getChildren()[0]->getType(), VALUE);
    ASSERT_EQ(stoi(root->getChildren()[0]->getChildren()[0]->getValue()), 1);

    ASSERT_EQ(root->getChildren()[1]->getType(), INT_DEC);
    ASSERT_EQ(root->getChildren()[1]->getValue(), "b");
    ASSERT_EQ(root->getChildren()[1]->getChildren().size(), 1);
    ASSERT_EQ(root->getChildren()[1]->getChildren()[0]->getType(), VALUE);
    ASSERT_EQ(stoi(root->getChildren()[1]->getChildren()[0]->getValue()), 10);

    ASSERT_EQ(root->getChildren()[2]->getType(), INT_ASSIGN);
    ASSERT_EQ(root->getChildren()[2]->getValue(), "a");
    ASSERT_EQ(root->getChildren()[2]->getChildren().size(), 1);
    ASSERT_EQ(root->getChildren()[2]->getChildren()[0]->getType(), VARIABLE);
    ASSERT_EQ(root->getChildren()[2]->getChildren()[0]->getValue(), "b");
}

}
