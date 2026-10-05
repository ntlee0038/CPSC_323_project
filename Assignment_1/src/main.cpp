#include "lexer.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
   ifstream inputFile("../tests/test1.txt");

   ofstream outputFile("../output/output1.txt");

   if (inputFile.is_open())
   {
    cout << "Error: could not open input file." << endl;
    return 1;
   }

if (!outputFile.is_open())
{
    cout << "Error: could not open output file." << endl;
    return 1;
}

outputFile << left
<< setw(15) << "Token"
<< "Lexeme" << endl;


outputFile << " -------------- " << endl;

while (true)
{
    Token currentToken = lexer(inputFile);

    if (currentToken.token == "EOF")
    {
        break;
    }

    outputFile << left
    << setw(15) << currentToken.token
    << currentToken.lexeme << endl;
}

inputFile.close();
outputFile.close();

cout << "lexical analysis complete. " << endl;
cout << "results written to output1.txt" << endl;

return 0;
}