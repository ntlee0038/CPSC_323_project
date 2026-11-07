#include "lexer.h"
#include <iostream>
#include <cctype> // character checking function

using namespace std;

bool isIdentifier(const string& lexeme)
{
    int state = 0;
    
    for (char ch : lexeme)
    {
        switch (state)
        {
            case 0:
            if (isalpha(ch))
            {
                state = 1;
            }
            else{
                return false;
            }
            break;

            case 1:
            if (isalnum(ch) || ch == '_')
            {
                state =1;
            }
            else
            {
                return false;
            }
            break;
        }
    }
    return state == 1;
}

bool isKeyword(const string& lexeme)
{
    string lowerLexeme = lexeme;

    for (char& ch : lowerLexeme)
    {
        ch = tolower(ch);
    }

    string keywords[] =
    {
        "integer", "boolean", "real",
        "if", "else", "fi", "while",
        "return", "get", "put",
        "function", "true", "false"
    };

    for (const string& keyword : keywords)
    {
        if (lowerLexeme == keyword)
        {
            return true;
        }
    }

    return false;
}
bool isInteger(const string& lexeme)
{
    int state = 0;
    for (char ch : lexeme)
    {
        switch (state)
        {
            case 0:
            if (isdigit(ch))
            {
                state = 1;
            }
            else
            {
                return false;
            }
            break;

             case 1:
        if (isdigit(ch))
        {
            state = 1;
        }
        else
        {
            return false;
        }
        break;
        }
    }
    return state == 1;
}

bool isReal(const string& lexeme)
{
    int state = 0;

    for (char ch : lexeme)
    {
        switch (state)
        {
            case 0:
            if (isdigit(ch))
            {
                state = 1;
            }
            else if (ch == '.')
            {
                state = 2;
            }
            else
            {
                return false;
            }
            break;

            case 1:
            if (isdigit(ch))
            {
                state = 1;
            }
            else if (ch == '.')
            {
                state = 2;
            }
            else
            {
                return false;
            }
            break;

            case 2:
            if (isdigit(ch))
            {
                state = 3;
            }
            else
            {
                return false;
            }
            break;

            case 3:
        if (isdigit(ch))
        {
            state = 3;
        }
        else
        {
            return false;
        }
        break;
        }

    }
    return state == 3;
}

bool isSeparator(char ch)
{
    return ch == '(' ||
           ch == ')' ||
           ch == '{' ||
           ch == '}' ||
           ch == ',' ||
           ch == ';' ||
           ch == '@';
}

bool isOperator(const string& lexeme)
{
    return lexeme == "=" ||
    lexeme == "+" ||
    lexeme == "-" ||
    lexeme == "*" ||
    lexeme == "/" ||
    lexeme == "==" ||
    lexeme == "!=" ||
    lexeme == ">" ||
    lexeme == "<" ||
    lexeme == "<=" ||
    lexeme == ">=";
    
}

Token lexer(ifstream& inputFile)
{
    Token result;
    char ch;

    // Skip whitespace and comments
    while (inputFile.get(ch))
    {
        if (isspace(ch))
        {
            continue;
        }

        // Comment starts with ! unless it is !=
        if (ch == '!' && inputFile.peek() != '=')
        {
            while (inputFile.get(ch) && ch != '!')
            {
                // Ignore comment contents
            }

            continue;
        }

        break;
    }

    // End of file
    if (!inputFile)
    {
        result.token = "EOF";
        result.lexeme = "";
        return result;
    }

    // Identifier or keyword
    if (isalpha(ch))
    {
        string lexeme;
        lexeme += ch;

        while (inputFile.peek() != EOF &&
               (isalnum(inputFile.peek()) || inputFile.peek() == '_'))
        {
            lexeme += static_cast<char>(inputFile.get());
        }

        if (isKeyword(lexeme))
        {
            result.token = "keyword";
        }
        else if (isIdentifier(lexeme))
        {
            result.token = "identifier";
        }
        else
        {
            result.token = "unknown";
        }

        result.lexeme = lexeme;
        return result;
    }

    // Integer or real
    if (isdigit(ch) || ch == '.')
    {
        string lexeme;
        lexeme += ch;

        bool hasDecimal = (ch == '.');

        while (inputFile.peek() != EOF)
        {
            char next = static_cast<char>(inputFile.peek());

            if (isdigit(next))
            {
                lexeme += static_cast<char>(inputFile.get());
            }
            else if (next == '.' && !hasDecimal)
            {
                lexeme += static_cast<char>(inputFile.get());
                hasDecimal = true;
            }
            else
            {
                break;
            }
        }

        if (isReal(lexeme))
        {
            result.token = "real";
        }
        else if (isInteger(lexeme))
        {
            result.token = "integer";
        }
        else
        {
            result.token = "unknown";
        }

        result.lexeme = lexeme;
        return result;
    }

    // Separator
    if (isSeparator(ch))
    {
        result.token = "separator";
        result.lexeme = string(1, ch);
        return result;
    }

    // Operator
    string op;
    op += ch;

    if (ch == '=' || ch == '<' || ch == '>' || ch == '!')
    {
        if (inputFile.peek() != EOF)
        {
            char next = static_cast<char>(inputFile.peek());
            string twoCharOp = op + next;

            if (isOperator(twoCharOp))
            {
                inputFile.get();
                result.token = "operator";
                result.lexeme = twoCharOp;
                return result;
            }
        }
    }

    if (isOperator(op))
    {
        result.token = "operator";
        result.lexeme = op;
        return result;
    }

    // Anything else is unknown
    result.token = "unknown";
    result.lexeme = string(1, ch);

    return result;
}