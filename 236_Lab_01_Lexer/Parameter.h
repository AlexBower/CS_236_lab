#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Parameter
{
public:
	string dataString;

	Parameter(string inString = "");

	~Parameter();

	string ToString(void);
};

#endif //PARAMETER