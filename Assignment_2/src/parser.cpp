#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <cstddef>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

class Parser {
    public:
        Parser(std::ifstream& input, std::ostream& output, bool showRules = true);
        void parse();

    private:
        std::ifstream& input;
        std::ostream& output;
        Token currentl;
        bool showRules;
        std::string source;
        std:: vector<std::size_t> newlineOffsets;
        std::size_t currentLine =1;

        void advance();
        void match(const std::string& lexeme);
        void matchType(const std::string& type);
        void rule(const std::string& production);
        [[noreturn]] void error(const std:: string& expected) const;
        bool is(const std:: string& lexeme) const;
        bool isType(const std:: string& type) const;
        bool startsStatement() const;
        bool startsExpression() const;
        bool startsQualifier() const;


}