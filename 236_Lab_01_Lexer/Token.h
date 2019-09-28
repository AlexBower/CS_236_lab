#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

enum TokenType
{
	COMMA, PERIOD, Q_MARK, LEFT_PAREN,
	RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY,
	ADD, SCHEMES, FACTS, RULES, QUERIES,
	ID, STRING, COMMENT, UNDEFINED, EOF_TOKEN
};

class Token
{
private:
	string actualValue;
	int lineNumber;
	TokenType tokenType;

public:
	Token(string value = "NO VALUE", int line = -1, TokenType type = UNDEFINED) :
		actualValue(value), lineNumber(line), tokenType(type)
	{
	}

	~Token() 
	{
	}

	string getValue() { return actualValue; }

	int getLineNum() { return lineNumber; }

	TokenType getTokenType() { return tokenType; }

	string ToString(void) const;
};

#endif //TOKEN