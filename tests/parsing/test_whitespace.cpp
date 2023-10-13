#include "../../src/parser/parser.hpp"
#include "../../src/parser/syntaxTree.hpp"
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
}

TEST(Comment, NonIncludedComment) {
  std::string statement = "# This is a comment";
  Parser p;
  p.parseStatement(p.getAST()->getRoot(), statement);
  SyntaxNode* root = p.getAST()->getRoot();
  EXPECT_EQ(root->getChildren().size(), 0);
}

TEST(Comment, IncludedComment) {
  std::string statement = "## This is a comment";
  Parser p;
  p.parseStatement(p.getAST()->getRoot(), statement);
  SyntaxNode* root = p.getAST()->getRoot();
  EXPECT_EQ(root->getChildren().size(), 1);
  EXPECT_EQ(root->getChildren()[0]->getType(), COMMENT);
  EXPECT_EQ(root->getChildren()[0]->getValue(), "This is a comment");
}

TEST(Comment, IncludedCommentNoSpace) {
  std::string statement = "##This is a comment";
  Parser p;
  p.parseStatement(p.getAST()->getRoot(), statement);
  SyntaxNode* root = p.getAST()->getRoot();
  EXPECT_EQ(root->getChildren().size(), 1);
  EXPECT_EQ(root->getChildren()[0]->getType(), COMMENT);
  EXPECT_EQ(root->getChildren()[0]->getValue(), "This is a comment");
}