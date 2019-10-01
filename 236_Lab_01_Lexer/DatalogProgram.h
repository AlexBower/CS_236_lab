#ifndef DATALOG_PROGRAM_H
#define DATALOG_PROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <set>

using namespace std;

class DatalogProgram
{
private:
	set<string> domainSet;
public:
	vector<Predicate> schemesVector;

	vector<Predicate> factsVector;

	vector<Predicate> queriesVector;

	vector<Rule> rulesVector;

	DatalogProgram();

	~DatalogProgram();

	string ToString(void);
};

#endif //DATALOG_PROGRAM