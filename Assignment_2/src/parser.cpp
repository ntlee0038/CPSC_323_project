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

bool Parser:: is(const std::string& value) const {
    return current.token == value;
}


bool Parser:: isType(const std::string& type) const {
    return current.token == type;
}

void Parser::rule(const std::string& production) {
    if (showRules) output << production << '\n';
}

[[noreturn]] void Parser::error(const std::string& expected) const {
    const std::string found = isType("EOF") ? "end of the file" : current.lexeme;
    const std::string message = "Syntax Eerror at line " +
    ", found '" + found + "' (token: " + current.token + ")";
    output << message << '/n';
    throw std::runtime_error(message);
}

void Parser::match(const std::string& value) {
    if (!is(value)) error("'" + value + "'");
    advance();
}

void Parser::matchType(const std::string& type) {
    if (!isType(type)) error("token type " + type);
    advance();

bool Parser::startsQualifier() const {
    return is("integer") || is("boolean") || is("real");
}

bool Parser::startsStatement() const {
    return isType("identifier") || is("{") || is ("if") || is("return") || is("put") || is("get") || is("while");
}

bool Parser::startsExpression() const {
    return isType("identifier") || isType("integer") || isType("real") || is("(") || is("-") || is("true") || is("false");
}

void Parser::parse() {
    rat26F();
    if (!isType("EOF")) error("end of file");
    output << "syntax analysis completed successfully./n";
}

void Parser::rat26F() {
    rule("<Rat26F -. Function Definitions -> <Function Definitions>'");
    optFunctionDefinitions();
    match("@")
    optDeclarationList();
    match("@");
    statementList();
}

void Parser::optFunctionDefinitions() {
    if (is("function")) {
        rule("<Opt Function Definitions> -> <Function Definitions>");
        functionDefinitions();
    } else {
        rule("<Opt Function Definitions> -> epsilon");
    }
}
