#include "DatalogProgram.h"



DatalogProgram::DatalogProgram()
{
}


DatalogProgram::~DatalogProgram()
{
}

string DatalogProgram::ToString(void)
{

	if (schemesVector.size() == 0)
	{
		//This means the Parse failed
		return "";
	}
	ostringstream outString;

	outString << "Schemes(" << schemesVector.size() << "):" << endl;

	for (unsigned i = 0; i < schemesVector.size(); i++)
	{
		outString << "  " << schemesVector.at(i).ToString() << endl;
	}

	domainSet.clear();

	outString << "Facts(" << factsVector.size() << "):" << endl;

	for (unsigned i = 0; i < factsVector.size(); i++)
	{
		outString << "  " << factsVector.at(i).ToString() << "." << endl;
		
		for (unsigned j = 0; j < factsVector.at(i).parameterVector.size(); j++)
		{
			//Populate the domain set with strings from Facts
			domainSet.insert(factsVector.at(i).parameterVector.at(j).ToString());
		}
	}

	outString << "Rules(" << rulesVector.size() << "):" << endl;

	for (unsigned i = 0; i < rulesVector.size(); i++)
	{
		outString << "  " << rulesVector.at(i).ToString() << "." << endl;
	}

	outString << "Queries(" << queriesVector.size() << "):" << endl;

	for (unsigned i = 0; i < queriesVector.size(); i++)
	{
		outString << "  " << queriesVector.at(i).ToString() << "?" << endl;
	}

	outString << "Domain(" << domainSet.size() << "):" << endl;

	for (set<string>::iterator itr = domainSet.begin();
		itr != domainSet.end(); ++itr)
	{
		outString << "  " << *itr << endl;
	}

	return outString.str();
}