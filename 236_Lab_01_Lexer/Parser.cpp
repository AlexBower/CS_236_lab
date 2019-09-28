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
		DatalogProgram();

		Match(EOF_TOKEN);
		outString << "Success!" << endl;
	}
	catch (Token error)
	{
		cout << "Failure!" << endl;
		cout << "  " << error.ToString();
	}
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

void Parser::DatalogProgram(void)
{
	/*datalogProgram	->	SCHEMES COLON scheme schemeList
		        FACTS COLON factList
		        RULES COLON ruleList
		        QUERIES COLON query queryList*/
	Match(SCHEMES);
	Match(COLON);
	Scheme();
	SchemeList();
	Match(FACTS);
	Match(COLON);
	FactList();
	Match(RULES);
	Match(COLON);
	RuleList();
	Match(QUERIES);
	Match(COLON);
	Query();
	QueryList();
}

void Parser::SchemeList(void)
{
	/*schemeList	->	scheme schemeList | lambda*/
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == ID)
	{
		Scheme();
		SchemeList();
	}
}

void Parser::FactList(void)
{
	/*factList	->	fact factList | lambda*/
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == ID)
	{
		Fact();
		FactList();
	}
}

void Parser::RuleList(void)
{
	/*ruleList	->	rule ruleList | lambda*/
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == ID)
	{
		Rule();
		RuleList();
	}
}

void Parser::QueryList(void)
{
	/*queryList	->	query queryList | lambda*/
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == ID)
	{
		Query();
		QueryList();
	}
}

void Parser::Scheme(void)
{
	/*scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN*/
	Match(ID);
	Match(LEFT_PAREN);
	Match(ID);
	IdList();
	Match(RIGHT_PAREN);
}

void Parser::Fact(void)
{
	/*fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD*/
	Match(ID);
	Match(LEFT_PAREN);
	Match(STRING);
	StringList();
	Match(RIGHT_PAREN);
	Match(PERIOD);
}

void Parser::Rule(void)
{
	/*rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD*/
	HeadPredicate();
	Match(COLON_DASH);
	Predicate();
	PredicateList();
	Match(PERIOD);
}

void Parser::Query(void)
{
	/*query		->	predicate Q_MARK*/
	Predicate();
	Match(Q_MARK);
}

void Parser::HeadPredicate(void)
{
	/*headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN*/
	Match(ID);
	Match(LEFT_PAREN);
	Match(ID);
	IdList();
	Match(RIGHT_PAREN);
}

void Parser::Predicate(void)
{
	/*predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN*/
	Match(ID);
	Match(LEFT_PAREN);
	Parameter();
	ParameterList();
	Match(RIGHT_PAREN);
}

void Parser::PredicateList(void)
{
	/*predicateList	->	COMMA predicate predicateList | lambda*/
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == COMMA)
	{
		Match(COMMA);
		Predicate();
		PredicateList();
	}
}

void Parser::ParameterList(void)
{
	/*parameterList	-> 	COMMA parameter parameterList | lambda*/
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == COMMA)
	{
		Match(COMMA);
		Parameter();
		ParameterList();
	}
}

void Parser::StringList(void)
{
	/*stringList	-> 	COMMA STRING stringList | lambda*/
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == COMMA)
	{
		Match(COMMA);
		Match(STRING);
		StringList();
	}
}

void Parser::IdList(void)
{
	/*idList  	-> 	COMMA ID idList | lambda*/
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == COMMA)
	{
		Match(COMMA);
		Match(ID);
		IdList();
	}
}

void Parser::Parameter(void)
{
	/*parameter->STRING | ID | expression*/
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == STRING)
	{
		Match(STRING);
	}
	else if (currentToken.getTokenType() == ID)
	{
		Match(ID);
	}
	else if (currentToken.getTokenType() == LEFT_PAREN)
	{
		Expression();
	}
	else
	{
		throw currentToken;
	}
}

void Parser::Expression(void)
{
	/*expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN*/
	Match(LEFT_PAREN);
	Parameter();
	Operator();
	Parameter();
	Match(RIGHT_PAREN);
}

void Parser::Operator(void)
{
	/*operator	->	ADD | MULTIPLY*/
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == ADD)
	{
		Match(ADD);
	}
	else if (currentToken.getTokenType() == MULTIPLY)
	{
		Match(MULTIPLY);
	}
	else
	{
		throw currentToken;
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