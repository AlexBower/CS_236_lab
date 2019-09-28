#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Parser
{
private:
	vector<Token> tokenVector;
	int currentTokenIndex;
	ostringstream outString;
public:
	Parser(vector<Token> vectorOfTokens = vector<Token>());

	~Parser(void);
	
	void Parse(void);
	
	void Match(TokenType typeOfToken);

	string VecToString(void);

	string ToString(void);
};

#endif //PARSER