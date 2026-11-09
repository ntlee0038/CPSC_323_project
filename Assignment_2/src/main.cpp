#include "parser.h"
#include <fstream>
#include <iostream>
#include <excepction>

int main( int argc, char** argv) {
    if (arg !=3) { std::cerr<< "Usage: ./parser <input> <output>\n"; return 1; }
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);
    if (!input || !output) { std::cerr <<"Could not open input or output file.\n"; return 1;}
    try {Parser parser(input, output); parser.parse(); }
    catch (const std::exception& e) {std::cerr <<e.what() << '\n'; return 1; }
    std::cout <<"Parsing successful.\n"
}