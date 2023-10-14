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

add_library(SyntaxTree ./src/parser/SyntaxTree.cpp ./src/parser/SyntaxNode.cpp ./src/parser/SyntaxTree.hpp)
add_library(Parser ./src/parser/Parser.cpp ./src/parser/Parser.hpp)
add_library(Evaluator ./src/evaluator/Evaluator.cpp ./src/evaluator/Evaluator.hpp)

add_executable(MipScript ./src/main.cpp)


target_link_libraries(MipScript SyntaxTree Parser Evaluator)



add_executable(IntegerParsingTest ./tests/parsing/test_integers.cpp)
target_link_libraries(IntegerParsingTest SyntaxTree Parser GTest::gtest_main)
add_test(IntegerParsingTest IntegerParsingTest)

add_executable(WhitespaceParsingTest ./tests/parsing/test_whitespace.cpp)
target_link_libraries(WhitespaceParsingTest SyntaxTree Parser GTest::gtest_main)

include(GoogleTest)

