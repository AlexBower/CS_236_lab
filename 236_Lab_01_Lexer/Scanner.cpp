#include "Scanner.h"

Scanner::Scanner(string inFileString) :
	inFileName(inFileString), currentLineNumber(1)
{
	tokenVector = vector<Token>();
}

Scanner::~Scanner()
{
}

void Scanner::Tokenize(void)
{
	inFile.open(inFileName);

	if (!inFile)
	{
		cerr << "Unable to open " << inFileName << " for input";
	}

	tokenVector.clear();

	Token tempToken;
	while (inFile.peek() != EOF)
	{
		char currentChar = inFile.peek();

		if (isspace(currentChar))
		{
			if (currentChar == '\n')
			{
				currentLineNumber++;
			}
			inFile.get();
		}
		else if (isalpha(currentChar))
		{
			IDStateMachine();
		}
		else
		{
			switch (currentChar)
			{
			case ',':
				tempToken = Token(",", currentLineNumber, COMMA);
				inFile.get();
				break;
			case '.':
				tempToken = Token(".", currentLineNumber, PERIOD);
				inFile.get();
				break;
			case '?':
				tempToken = Token("?", currentLineNumber, Q_MARK);
				inFile.get();
				break;
			case '(':
				tempToken = Token("(", currentLineNumber, LEFT_PAREN);
				inFile.get();
				break;
			case ')':
				tempToken = Token(")", currentLineNumber, RIGHT_PAREN);
				inFile.get();
				break;
			case ':':
				inFile.get();

				if (inFile.peek() == '-')
				{
					tempToken = Token(":-", currentLineNumber, COLON_DASH);
					inFile.get();
				}
				else
				{
					tempToken = Token(":", currentLineNumber, COLON);
				}
				break;
			case '*':
				tempToken = Token("*", currentLineNumber, MULTIPLY);
				inFile.get();
				break;
			case '+':
				tempToken = Token("+", currentLineNumber, ADD);
				inFile.get();
				break;
			case '\'':
				tempToken = StringStateMachine();
				break;
			case '#':
				tempToken = CommentStateMachine();
				break;
			default:
				string tempString = "";
				tempString += currentChar;
				tempToken = Token(tempString, currentLineNumber, UNDEFINED);
				inFile.get();
				break;
			}
			tokenVector.push_back(tempToken);
		}
	}

	tempToken = Token("", currentLineNumber, EOF_TOKEN);
	tokenVector.push_back(tempToken);

	inFile.close();
	return;
}

void Scanner::IDStateMachine(void)
{
	string charBuffer = "";
	while (isalnum(inFile.peek()))
	{
		charBuffer += inFile.get();
	}

	// Check if the charBuffer matches a Keyword

	Token tempToken;
	if (charBuffer == "Schemes")
	{
		// The charBuffer matches "Schemes" so it is not an ID, but is SCHEMES
		tempToken = Token(charBuffer, currentLineNumber, SCHEMES);
	}
	else if (charBuffer == "Facts")
	{
		tempToken = Token(charBuffer, currentLineNumber, FACTS);
	}
	else if (charBuffer == "Rules")
	{
		tempToken = Token(charBuffer, currentLineNumber, RULES);
	}
	else if (charBuffer == "Queries")
	{
		tempToken = Token(charBuffer, currentLineNumber, QUERIES);
	}
	else
	{
		// Does not match a keyword so we know it's an ID
		tempToken = Token(charBuffer, currentLineNumber, ID);
	}
	tokenVector.push_back(tempToken);
}

Token Scanner::StringStateMachine(void)
{
	string charBuffer = "";

	int initialLineNumber = currentLineNumber;

	charBuffer += inFile.get();
	while (inFile.peek() != EOF)
	{
		if (inFile.peek() == '\'')
		{
			charBuffer += inFile.get();

			if (inFile.peek() == '\'')
			{
				// There are two 's in a row
				charBuffer += inFile.get();
				continue;
			}
			// There is one ' so end the String
			return Token(charBuffer, initialLineNumber, STRING);
		}
		else if (inFile.peek() == '\n')
		{
			currentLineNumber++;
		}
		charBuffer += inFile.get();
	}

	return Token(charBuffer, initialLineNumber, UNDEFINED);
}

Token Scanner::CommentStateMachine(void)
{
	string charBuffer = "";

	charBuffer += inFile.get();

	if (inFile.peek() == '|')
	{
		// We know that we have a multi line comment
		charBuffer += inFile.get();
		return MultiLineCommentStateMachine(charBuffer);
	}

	while (inFile.peek() != EOF && inFile.peek() != '\n')
	{
		// We know that we have a single line comment
		// Keep going until End of File or newline
		charBuffer += inFile.get();
	}

	return Token(charBuffer, currentLineNumber, COMMENT);;
}

Token Scanner::MultiLineCommentStateMachine(string initialCharBuffer)
{
	string charBuffer = initialCharBuffer;

	int initialLineNumber = currentLineNumber;

	while (inFile.peek() != EOF)
	{
		if (inFile.peek() == '\n')
		{
			currentLineNumber++;
		}
		else if (inFile.peek() == '|')
		{
			// The comment might Be closing
			charBuffer += inFile.get();
			if (inFile.peek() == '#')
			{
				// The comment is closed
				charBuffer += inFile.get();
				return Token(charBuffer, initialLineNumber, COMMENT);
			}
			// The comment had a | but is not closed
			continue;
		}
		charBuffer += inFile.get();
	}

	// In this case the Comment is not properly ended EOF
	return Token(charBuffer, initialLineNumber, UNDEFINED);
}

string Scanner::ToString(void)
{
	ostringstream outString;

	for (int i = 0; i < tokenVector.size(); i++)
	{
		outString << tokenVector.at(i).ToString();
	}

	outString << "Total Tokens = " << tokenVector.size();

	return outString.str();
}