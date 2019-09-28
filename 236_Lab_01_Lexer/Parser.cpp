#include "Parser.h"


Parser::Parser(vector<Token> vectorOfTokens) :
	tokenVector(vectorOfTokens), currentTokenIndex(0), outString(""),
	schemesCount(0), factsCount(0), rulesCount(0), queriesCount(0)
{
	domainSet = set<string>();
}


Parser::~Parser()
{
}

void Parser::Parse()
{
	try
	{
		currentTokenIndex = 0;
		schemesCount = 0;
		factsCount = 0;
		rulesCount = 0;
		queriesCount = 0;
		domainSet.clear();
		outString = ostringstream("");
		// Go through once to count number of each lists.
		DatalogProgram();

		Match(EOF_TOKEN);

		// Go through again to print out.
		currentTokenIndex = 0;
		outString = ostringstream("");
		domainSet.clear();
		outString << "Success!" << endl;
		DatalogProgram();

		outString << "Domain(" << domainSet.size() << "):" << endl;
		for (set<string>::iterator itr = domainSet.begin();
			itr != domainSet.end(); ++itr)
		{
			outString << INDENT_SPACE << *itr << endl;
		}
	}
	catch (Token error)
	{
		outString = ostringstream("");
		outString << "Failure!" << endl;
		outString << "  " << error.ToString();
	}
}

void Parser::Match(TokenType typeOfToken)
{
	while (tokenVector.at(currentTokenIndex).getTokenType() == COMMENT)
	{
		currentTokenIndex++;
	}
	if (typeOfToken == COMMENT)
	{
		// We use this to 'clean' out COMMENTS before if statements
		return;
	}
	
	if (tokenVector.at(currentTokenIndex).getTokenType() == typeOfToken)
	{
		outString << tokenVector.at(currentTokenIndex).getValue();
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
	outString << "(" << schemesCount << ")";
	Match(COLON);
	outString << endl;
	Scheme();
	SchemeList();
	Match(FACTS);
	outString << "(" << factsCount << ")";
	Match(COLON);
	outString << endl;
	FactList();
	Match(RULES);
	outString << "(" << rulesCount << ")";
	Match(COLON);
	outString << endl;
	RuleList();
	Match(QUERIES);
	outString << "(" << queriesCount << ")";
	Match(COLON);
	outString << endl;
	Query();
	QueryList();
}

void Parser::SchemeList(void)
{
	/*schemeList	->	scheme schemeList | lambda*/
	Match(COMMENT);
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
	Match(COMMENT);
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
	Match(COMMENT);
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
	Match(COMMENT);
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
	outString << INDENT_SPACE;
	Match(ID);
	Match(LEFT_PAREN);
	Match(ID);
	IdList();
	Match(RIGHT_PAREN);

	schemesCount++;
	outString << endl;
}

void Parser::Fact(void)
{
	/*fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD*/
	outString << INDENT_SPACE;
	Match(ID);
	Match(LEFT_PAREN);
	Match(COMMENT);
	if (tokenVector.at(currentTokenIndex).getTokenType() == STRING)
	{
		domainSet.insert(tokenVector.at(currentTokenIndex).getValue());
	}
	Match(STRING);
	StringList(true);
	Match(RIGHT_PAREN);
	Match(PERIOD);

	factsCount++;
	outString << endl;
}

void Parser::Rule(void)
{
	/*rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD*/
	outString << INDENT_SPACE;
	HeadPredicate();
	outString << " ";
	Match(COLON_DASH);
	outString << " ";
	Predicate();
	PredicateList();
	Match(PERIOD);

	rulesCount++;
	outString << endl;
}

void Parser::Query(void)
{
	/*query		->	predicate Q_MARK*/
	outString << INDENT_SPACE;
	Predicate();
	Match(Q_MARK);

	queriesCount++;
	outString << endl;
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
	Match(COMMENT);
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
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == COMMA)
	{
		Match(COMMA);
		Parameter();
		ParameterList();
	}
}

void Parser::StringList(bool isFromFacts)
{
	/*stringList	-> 	COMMA STRING stringList | lambda*/
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == COMMA)
	{
		Match(COMMA);
		if (tokenVector.at(currentTokenIndex).getTokenType() == STRING
			&& isFromFacts)
		{
			domainSet.insert(tokenVector.at(currentTokenIndex).getValue());
		}
		Match(STRING);
		StringList(isFromFacts);
	}
}

void Parser::IdList(void)
{
	/*idList  	-> 	COMMA ID idList | lambda*/
	Match(COMMENT);
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
	Match(COMMENT);
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
	Match(COMMENT);
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