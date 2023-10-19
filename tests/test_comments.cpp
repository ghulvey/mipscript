#include <iostream>
#include "../src/parser/parser.hpp"
#include "../src/parser/syntaxTree.hpp"
#include "../src/compiler/compiler.hpp"
#include <gtest/gtest.h>

TEST(Comment, NonIncludedComment) {
  std::string statement = "# This is a comment";
  Parser p;
  p.parseStatement(p.getAST()->getRoot(), statement);
  SyntaxNode* root = p.getAST()->getRoot();
  EXPECT_EQ(root->getChildren().size(), 0);

  Compiler c(p.getAST());
  c.evaluate();
  std::vector<std::string> instructions = c.getInstructions();
  EXPECT_EQ(instructions.size(), 0);
}

TEST(Comment, IncludedComment) {
  std::string statement = "## This is a comment";
  Parser p;
  p.parseStatement(p.getAST()->getRoot(), statement);
  SyntaxNode* root = p.getAST()->getRoot();
  EXPECT_EQ(root->getChildren().size(), 1);
  EXPECT_EQ(root->getChildren()[0]->getType(), COMMENT);
  EXPECT_EQ(root->getChildren()[0]->getValue(), "This is a comment");

  Compiler c(p.getAST());
  c.evaluate();
  std::vector<std::string> instructions = c.getInstructions();
  EXPECT_EQ(instructions.size(), 1);
}

TEST(Comment, IncludedCommentNoSpace) {
  std::string statement = "##This is a comment";
  Parser p;
  p.parseStatement(p.getAST()->getRoot(), statement);
  SyntaxNode* root = p.getAST()->getRoot();
  EXPECT_EQ(root->getChildren().size(), 1);
  EXPECT_EQ(root->getChildren()[0]->getType(), COMMENT);
  EXPECT_EQ(root->getChildren()[0]->getValue(), "This is a comment");

  Compiler c(p.getAST());
  c.evaluate();
  std::vector<std::string> instructions = c.getInstructions();
  EXPECT_EQ(instructions.size(), 1);
}