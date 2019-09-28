#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

class Parser
{
private:
	vector<Token> tokenVector;
	int currentTokenIndex;
	ostringstream outString;
	int schemesCount;
	int factsCount;
	int rulesCount;
	int queriesCount;
	set<string> domainSet;
	const string INDENT_SPACE = "  ";
public:
	Parser(vector<Token> vectorOfTokens = vector<Token>());

	~Parser(void);
	
	void Parse(void);
	
	void Match(TokenType typeOfToken);

	void DatalogProgram(void);

	void SchemeList(void);

	void FactList(void);

	void RuleList(void);

	void QueryList(void);

	void Scheme(void);

	void Fact(void);

	void Rule(void);
	
	void Query(void);

	void HeadPredicate(void);

	void Predicate(void);

	void PredicateList(void);

	void ParameterList(void);

	void StringList(bool isFromFacts = false);

	void IdList(void);

	void Parameter(void);

	void Expression(void);

	void Operator(void);

	string VecToString(void);

	string ToString(void);
};

#endif //PARSER