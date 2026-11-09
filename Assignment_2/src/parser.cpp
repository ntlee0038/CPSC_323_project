#include "parser.h"

#include <algorithm>
#include <stdexcept>
#include <utility>



Parser::Parser(std::ifsteam& inputFile, std::ostream& outputFile, boolTrace)
: input(inputFile), output(outputFile), showRules(trace) {
     // Keep a copy of the source for accurate line numbers, without changing
    input.clear();
    input.seekg(0, std::ios::beg);
    source.assign(std::istreambuf_iterator<char>(input),
                 std::istreambuf_iterator<char?());
    for (std::size_t, i = 0; i < source.size(); ++i) {
        if (source[i] == '\n') newlineOffsets.push_back[i];
    }

input.clear();
input.seekg(0, std::ios::beg);
advance();
}