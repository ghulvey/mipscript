#include "./parser/parser.hpp"
#include <iostream>
#include <fstream>


int main(int argc, char** argv) {
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }
    std::fstream file(argv[1]);

    // Parse the file
    Parser p(file);

    // Close the file
    file.close();

    return 0;
}