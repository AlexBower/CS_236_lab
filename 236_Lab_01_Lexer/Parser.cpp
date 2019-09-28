#include "Parser.h"


Parser::Parser(vector<Token> vectorOfTokens) :
	tokenVector(vectorOfTokens), currentTokenIndex(0), outString("")
{
}


Parser::~Parser()
{
}

void Parser::Parse()
{
	try
	{
		Match(COMMA);
	}
	catch (Token error)
	{
		cout << "Failure!" << endl;
		cout << error.ToString();
	}

	outString << "Success!" << endl;
}

void Parser::Match(TokenType typeOfToken)
{
	while (tokenVector.at(currentTokenIndex).getTokenType() == COMMENT)
	{
		currentTokenIndex++;
	}
	if (tokenVector.at(currentTokenIndex).getTokenType() == typeOfToken)
	{
		currentTokenIndex++;
		return;
	}
	else
	{
		throw tokenVector.at(currentTokenIndex);
	}
	
}

string Parser::VecToString(void)
{
	ostringstream outStr;
	for (int i = 0; i < tokenVector.size(); i++)
	{
		outStr << tokenVector.at(i).ToString();
	}
	return outStr.str();
}

string Parser::ToString(void)
{
	return outString.str();
}