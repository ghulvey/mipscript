project(MipScript)
cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(SyntaxTree ./src/parser/syntaxtree.cpp ./src/parser/syntaxnode.cpp ./src/parser/syntaxtree.hpp)
add_library(Parser ./src/parser/parser.cpp ./src/parser/parser.hpp)
add_library(Compiler ./src/compiler/compiler.cpp ./src/compiler/compiler.hpp)

add_executable(MipScript ./src/main.cpp)
target_link_libraries(MipScript SyntaxTree Parser Compiler)

add_executable(IntegerTest ./tests/test_integers.cpp)
target_link_libraries(IntegerTest SyntaxTree Parser Compiler GTest::gtest_main)
add_test(IntegerTest ./build/bin/IntegerTest)

add_executable(WhitespaceTest ./tests/test_whitespace.cpp)
target_link_libraries(WhitespaceTest SyntaxTree Parser Compiler GTest::gtest_main)
add_test(WhitespaceTest ./build/bin/WhitespaceTest)

add_executable(CommentTest ./tests/test_comments.cpp)
target_link_libraries(CommentTest SyntaxTree Parser Compiler GTest::gtest_main)
add_test(CommentTest ./build/bin/CommentTest)

add_executable(AdditionTest ./tests/test_addition.cpp)
target_link_libraries(AdditionTest SyntaxTree Parser Compiler GTest::gtest_main)
#add_test(AdditionTest ./build/bin/AdditionTest)

include(GoogleTest)

