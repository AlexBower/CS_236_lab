// Alex Bower CS236 Lab 01 Lexer

#include <iostream>
#include "Scanner.h"

using namespace std;

int main(int argc, char* argv[])
{
	string inFileName = argv[1];

	Scanner scanner(inFileName);
	scanner.Tokenize();
	cout << scanner.toString();

	return 0;
}