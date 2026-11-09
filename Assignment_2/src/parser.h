//header guards
#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <cstddef> //provides std::size_t for sizes and positions
#include <fstream>
#include <ostream> //lets us write output to files or terminal
#include <string>
#include <vector>


//parser class below
class Parser {
    public:
        Parser(std::ifstream& input, std::ostream& output, bool showRules = true);
        void parse();

    private:
        std::ifstream& input;
        std::ostream& output;
        Token current;
        bool showRules;
        std::string source;
        std:: vector<std::size_t> newlineOffsets;
        std::size_t currentLine =1;


        //helper functions 

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


        // Grammaer functions
        void rat26F();
        void optFunctionDefinitions();
        void functionDefinitions();
        void function();
        void optParameterList();
        void parameterList();
        void parameter();
        void qualifier();
        void body();
        void optDeclarationList();
        void declarationList();
        void declaration();
        void ids();
        void statementList();
        void statement();
        void compound();
        void assign();
        void ifStatement();
        void returnStatement();
        void printStatement();
        void scanStatement();
        void whileStatement();
        void condition();
        void relop();
        void expression();
        void expressionPrime();
        void term();
        void termPrime();
        void factor();
        void primary();


};

#endif