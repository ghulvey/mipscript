#include "../src/parser/parser.hpp"
#include "../src/parser/syntaxTree.hpp"
#include "../src/compiler/compiler.hpp"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(WhiteSpaceParsing, EmptyString) {
  std::string statement = " ";
  Parser p;
  p.parseStatement(p.getAST()->getRoot(), statement);
  SyntaxNode* root = p.getAST()->getRoot();
  EXPECT_EQ(root->getChildren().size(), 1);
  EXPECT_EQ(root->getChildren()[0]->getType(), NEWLINE);
  EXPECT_EQ(root->getChildren()[0]->getChildren().size(), 0);

  Compiler c(p.getAST());
  c.evaluate();
  std::vector<std::string> instructions = c.getInstructions();
  EXPECT_EQ(instructions.size(), 1);
}