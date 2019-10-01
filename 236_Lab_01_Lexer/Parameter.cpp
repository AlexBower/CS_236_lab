#include "Parameter.h"



Parameter::Parameter(string inString) : dataString(inString)
{
}


Parameter::~Parameter()
{
}

string Parameter::ToString(void)
{
	return dataString;
}