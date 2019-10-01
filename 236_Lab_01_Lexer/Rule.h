#ifndef RULE_H
#define RULE_H

#include "Predicate.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Rule
{
public:
	Predicate headPredicate;
	
	vector<Predicate> bodyPredicatesVector;

	Rule();

	~Rule();

	string ToString(void);
};

#endif //RULE