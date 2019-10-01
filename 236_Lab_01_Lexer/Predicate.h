#ifndef PREDICATE_H
#define PREDICATE_H

#include "Parameter.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Predicate
{
public:
	string startId;

	vector<Parameter> parameterVector;
	
	Predicate();
	
	~Predicate();

	string ToString(void);
};

#endif //PREDICATE