// Alex Bower CS236 Lab 01 Lexer

#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "DatalogProgram.h"

using namespace std;

int main(int argc, char* argv[])
{
	string inFileName = argv[1];

	Scanner scanner(inFileName);
	scanner.Tokenize();

	// cout << scanner.ToString();

	Parser parser(scanner.getVector());
	// cout << parser.VecToString();

	DatalogProgram datalogProgram;

	datalogProgram = parser.Parse();
	cout << datalogProgram.ToString();

	system("pause");

	return 0;
}