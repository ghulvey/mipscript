#include <iostream>
#include "../../src/parser/parser.hpp"
#include "../../src/parser/syntaxTree.hpp"
#include <gtest/gtest.h>

namespace {

void testIntegerParsingCase(std::string statement, std::string variableName, int num) {
    std::cout << "Testing: " << statement;
    Parser p;
    p.parseStatement(p.getAST()->getRoot(), statement);
    SyntaxNode* root = p.getAST()->getRoot();
    try {
        assert (root->getChildren().size() == 1);
        assert (root->getChildren()[0]->getType() == INT_DEC);
        assert (root->getChildren()[0]->getValue() == variableName);
        assert (root->getChildren()[0]->getChildren().size() == 1);
        assert (root->getChildren()[0]->getChildren()[0]->getType() == VALUE);
        assert (stoi(root->getChildren()[0]->getChildren()[0]->getValue()) == num);
    } catch (std::exception e) {
        std::cout << " [FAIL]" << std::endl;
        return;
    }
    std::cout << " [PASS]" << std::endl;
}

TEST(IntParsing, BasicAssertion) {
    testIntegerParsingCase("int a = 1;", "a", 1);
}

TEST(IntParsing, ZeroAssertion) {
    testIntegerParsingCase("int a = 0;", "a", 0);
}

TEST(IntParsing, NegativeAssertion) {
    testIntegerParsingCase("int a = -1;", "a", -1);
}

TEST(IntParsing, LongAssertion) {
    testIntegerParsingCase("int longName = 123456789;", "longName", 123456789);
}

TEST(IntParsing, MaxAssertion) {
    testIntegerParsingCase("int longNum = 2147483647;", "longNum", 2147483647);
}

TEST(IntParsing, MinAssertion) {
    testIntegerParsingCase("int longNegNum = -2147483648;", "longNegNum", -2147483648);
}

}
