#include "Rule.h"



Rule::Rule()
{
}


Rule::~Rule()
{
}

string Rule::ToString(void)
{
	ostringstream outString;

	outString << headPredicate.ToString() << " :- ";

	for (int i = 0; i < bodyPredicatesVector.size(); i++)
	{
		if (i != 0)
		{
			outString << ",";
		}
		outString << bodyPredicatesVector.at(i).ToString();
	}

	return outString.str();
}