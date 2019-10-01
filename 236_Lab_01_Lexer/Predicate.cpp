#include "Predicate.h"



Predicate::Predicate()
{
}


Predicate::~Predicate()
{
}

string Predicate::ToString(void)
{
	ostringstream outString;

	outString << startId << "(";

	for (int i = 0; i < parameterVector.size(); i++)
	{
		if (i != 0)
		{
			outString << ",";
		}
		outString << parameterVector.at(i).ToString();
	}

	outString << ")";

	return outString.str();
}