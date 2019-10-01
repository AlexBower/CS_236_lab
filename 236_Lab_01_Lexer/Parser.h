#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Parser
{
private:
	vector<Token> tokenVector;
	vector<Parameter> tempParameterVector;
	vector<Predicate> tempPredicateVector;
	int currentTokenIndex;
	DatalogProgram datalogProgram;
public:
	Parser(vector<Token> vectorOfTokens = vector<Token>());

	~Parser(void);
	
	DatalogProgram Parse(void);
	
	string Match(TokenType typeOfToken);

	void ParseDatalog(void);

	void ParseSchemeList(void);

	void ParseFactList(void);

	void ParseRuleList(void);

	void ParseQueryList(void);

	void ParseScheme(void);

	void ParseFact(void);

	void ParseRule(void);
	
	void ParseQuery(void);

	Predicate ParseHeadPredicate(void);

	void ParsePredicate(void);

	void ParsePredicateList(void);

	void ParseParameterList(void);

	void ParseStringList(void);

	void ParseIdList(void);

	string ParseParameter(void);

	string ParseExpression(void);

	string ParseOperator(void);

	string VecToString(void);

	string ToString(void);
};

#endif //PARSER