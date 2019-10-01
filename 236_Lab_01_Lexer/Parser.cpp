#include "Parser.h"


Parser::Parser(vector<Token> vectorOfTokens) :
	tokenVector(vectorOfTokens), currentTokenIndex(0)
{
}


Parser::~Parser()
{
}

DatalogProgram Parser::Parse()
{
	try
	{
		datalogProgram = DatalogProgram();

		currentTokenIndex = 0;

		ParseDatalog();

		Match(EOF_TOKEN);

		cout << "Success!" << endl;

		return datalogProgram;
	}
	catch (Token error)
	{
		cout << "Failure!" << endl;
		cout << "  " << error.ToString();
		return DatalogProgram();
	}
}

string Parser::Match(TokenType typeOfToken)
{
	while (tokenVector.at(currentTokenIndex).getTokenType() == COMMENT)
	{
		currentTokenIndex++;
	}
	if (typeOfToken == COMMENT)
	{
		// We use this to 'clean' out COMMENTS before if statements
		return "";
	}
	
	if (tokenVector.at(currentTokenIndex).getTokenType() == typeOfToken)
	{
		string tempString = tokenVector.at(currentTokenIndex).getValue();
		currentTokenIndex++;
		return tempString;
	}
	else
	{
		throw tokenVector.at(currentTokenIndex);
	}
}

void Parser::ParseDatalog(void)
{
	/*datalogProgram	->	SCHEMES COLON scheme schemeList
		        FACTS COLON factList
		        RULES COLON ruleList
		        QUERIES COLON query queryList*/
	Match(SCHEMES);
	Match(COLON);
	ParseScheme();
	ParseSchemeList();
	Match(FACTS);
	Match(COLON);
	ParseFactList();
	Match(RULES);
	Match(COLON);
	ParseRuleList();
	Match(QUERIES);
	Match(COLON);
	ParseQuery();
	ParseQueryList();
}

void Parser::ParseSchemeList(void)
{
	/*schemeList	->	scheme schemeList | lambda*/
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == ID)
	{
		ParseScheme();
		ParseSchemeList();
	}
}

void Parser::ParseFactList(void)
{
	/*factList	->	fact factList | lambda*/
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == ID)
	{
		ParseFact();
		ParseFactList();
	}
}

void Parser::ParseRuleList(void)
{
	/*ruleList	->	rule ruleList | lambda*/
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == ID)
	{
		ParseRule();
		ParseRuleList();
	}
}

void Parser::ParseQueryList(void)
{
	/*queryList	->	query queryList | lambda*/
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == ID)
	{
		ParseQuery();
		ParseQueryList();
	}
}

void Parser::ParseScheme(void)
{
	/*scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN*/
	Predicate tempScheme;

	tempScheme.startId = Match(ID);
	Match(LEFT_PAREN);

	tempParameterVector.clear();
	tempParameterVector.push_back(Parameter(Match(ID)));
	ParseIdList();
	tempScheme.parameterVector = tempParameterVector;

	Match(RIGHT_PAREN);

	datalogProgram.schemesVector.push_back(tempScheme);
}

void Parser::ParseFact(void)
{
	/*fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD*/
	Predicate tempFact;

	tempFact.startId = Match(ID);
	Match(LEFT_PAREN);

	tempParameterVector.clear();
	tempParameterVector.push_back(Parameter(Match(STRING)));
	ParseStringList();
	tempFact.parameterVector = tempParameterVector;

	Match(RIGHT_PAREN);
	Match(PERIOD);
	
	datalogProgram.factsVector.push_back(tempFact);
}

void Parser::ParseRule(void)
{
	/*rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD*/
	Rule tempRule;

	tempRule.headPredicate = ParseHeadPredicate();
	Match(COLON_DASH);

	tempPredicateVector.clear();
	ParsePredicate();
	ParsePredicateList();

	tempRule.bodyPredicatesVector = tempPredicateVector;

	Match(PERIOD);

	datalogProgram.rulesVector.push_back(tempRule);
}

void Parser::ParseQuery(void)
{
	/*query		->	predicate Q_MARK*/
	Predicate tempQuery;

	tempPredicateVector.clear();
	ParsePredicate();
	tempQuery = tempPredicateVector.at(0);
	Match(Q_MARK);

	datalogProgram.queriesVector.push_back(tempQuery);
}

Predicate Parser::ParseHeadPredicate(void)
{
	/*headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN*/
	Predicate tempPredicate;

	tempPredicate.startId = Match(ID);
	Match(LEFT_PAREN);

	tempParameterVector.clear();
	tempParameterVector.push_back(Parameter(Match(ID)));
	ParseIdList();
	tempPredicate.parameterVector = tempParameterVector;
	
	Match(RIGHT_PAREN);

	return tempPredicate;
}

void Parser::ParsePredicate(void)
{
	/*predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN*/
	Predicate tempPredicate;

	tempPredicate.startId = Match(ID);
	Match(LEFT_PAREN);

	tempParameterVector.clear();
	tempParameterVector.push_back(Parameter(ParseParameter()));
	ParseParameterList();
	tempPredicate.parameterVector = tempParameterVector;

	Match(RIGHT_PAREN);

	tempPredicateVector.push_back(tempPredicate);
}

void Parser::ParsePredicateList(void)
{
	/*predicateList	->	COMMA predicate predicateList | lambda*/
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == COMMA)
	{
		Match(COMMA);
		ParsePredicate();
		ParsePredicateList();
	}
}

void Parser::ParseParameterList(void)
{
	/*parameterList	-> 	COMMA parameter parameterList | lambda*/
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == COMMA)
	{
		Match(COMMA);
		tempParameterVector.push_back(Parameter(ParseParameter()));
		ParseParameterList();
	}
}

void Parser::ParseStringList(void)
{
	/*stringList	-> 	COMMA STRING stringList | lambda*/
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == COMMA)
	{
		Match(COMMA);
		tempParameterVector.push_back(Parameter(Match(STRING)));
		ParseStringList();
	}
}

void Parser::ParseIdList(void)
{
	/*idList  	-> 	COMMA ID idList | lambda*/
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == COMMA)
	{
		Match(COMMA);
		tempParameterVector.push_back(Parameter(Match(ID)));
		ParseIdList();
	}
}

string Parser::ParseParameter(void)
{
	/*parameter->STRING | ID | expression*/
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == STRING)
	{	
		return Match(STRING);
	}
	else if (currentToken.getTokenType() == ID)
	{
		return Match(ID);
	}
	else if (currentToken.getTokenType() == LEFT_PAREN)
	{
		return ParseExpression();
	}
	else
	{
		throw currentToken;
	}
}

string Parser::ParseExpression(void)
{
	/*expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN*/
	string tempExpression = "";
	tempExpression += Match(LEFT_PAREN);
	tempExpression += ParseParameter();
	tempExpression += ParseOperator();
	tempExpression += ParseParameter();
	tempExpression += Match(RIGHT_PAREN);
	return tempExpression;
}

string Parser::ParseOperator(void)
{
	/*operator	->	ADD | MULTIPLY*/
	Match(COMMENT);
	Token currentToken = tokenVector.at(currentTokenIndex);
	if (currentToken.getTokenType() == ADD)
	{
		return Match(ADD);
	}
	else if (currentToken.getTokenType() == MULTIPLY)
	{
		return Match(MULTIPLY);
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
	return VecToString();
}