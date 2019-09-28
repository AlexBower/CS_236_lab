#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include "Token.h"

using namespace std;

class Scanner
{
private:
	string inFileName;
	int currentLineNumber;
	vector<Token> tokenVector;
	ifstream inFile;

public:
	Scanner(string inFileString = "NO FILE");

	~Scanner();

	void Tokenize(void);

	void IDStateMachine(void);

	Token StringStateMachine(void);

	Token CommentStateMachine(void);

	Token MultiLineCommentStateMachine(string initialCharBuffer);

	string ToString(void);

	vector<Token> getVector() { return tokenVector; }
};

#endif //SCANNER