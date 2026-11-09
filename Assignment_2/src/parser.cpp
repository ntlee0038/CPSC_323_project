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

void Parser::advance() {
    current = lexer(input);
    const std::streampos pos = input.tellg();
    const std:: size_t end = (pos == std::streampos(-1))
        ? source.size() : static_cast<std::size_t>(pos);
    const std::size_t begin = (end >= current.lexeme.size())
        ? end - current.lexeme.size() : 0;
    currentLine = 1 + static_cast<std::size_t>(
        std:: lower_bound(newlineOffsets.begin(), newlineOffsets.end(), begin)
    - newlineOffsets.begin());

    if (current.token == "unknown") error("a recognized Rat26F token");
}

