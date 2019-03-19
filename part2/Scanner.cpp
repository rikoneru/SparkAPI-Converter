#include "Scanner.h"
#include "Token.h"
#include "Util.h"
/*#include <iostream>*/

Scanner::Scanner(const char* inputProgram, bool& isOpen)
{
	inpPgm.open(inputProgram, std::ifstream::in);
	curLine.erase();
	isOpen = inpPgm.is_open();

}

bool Scanner::hasNextLine()
{
	curLine.erase();
	if (std::getline(inpPgm, curLine))
	{
		lineIt = curLine.begin();
		return true;
	}
	else
	{
		curLine.erase();
		return false;
	}
}

bool Scanner::hasNextToken()
{
	if (curLine.empty() || lineIt == curLine.end())
	{
		if (!hasNextLine())
		{
			return false;
		}
		/*std::cout << "\t\tRead next Line\n";*/
	}

	curToken = new Token();
	populateToken();
	return true;
}

Token* Scanner::getNextToken()
{
	return curToken;
}

void Scanner::populateToken()
{
	while (lineIt != curLine.end())
	{
		if (curToken->getID() == Token::IDTYPE_METASTATEMENT)
		{
			/*std::cout << "METASTATEMENT\t" << *lineIt << "\n";*/
			curToken->push(*lineIt);
		}
		else if (curToken->getID() == Token::IDTYPE_STRING)
		{
			/*std::cout << "STRING\t" << *lineIt << "\n";*/
			if (*lineIt != '"')
			{
				curToken->push(*lineIt);
			}
			else
			{
				curToken->push(*lineIt);
				++lineIt;
				curToken->isStringComplete = true;
				break;
			}
		}
		else if(curToken->getID() == Token::IDTYPE_CHAR)
		{
			/*std::cout << "char\t" << *lineIt << "\n";*/
			if (*lineIt != '\'')
			{
				curToken->push(*lineIt);
			}
			else
			{
				curToken->push(*lineIt);
				++lineIt;
				curToken->isCharComplete = true;
				break;
			}
		}
		else if (Util::isDigit(lineIt))
		{
			/*std::cout << "DIGIT\t" << *lineIt << "\n";*/
			if (curToken->getID() == Token::IDTYPE_EMPTY)
			{
				curToken->setID(Token::IDTYPE_NUMBER);
				curToken->push(*lineIt);
			}
			else if (curToken->getID() == Token::IDTYPE_NUMBER || curToken->getID() == Token::IDTYPE_IDENTIFIER)
			{
				curToken->push(*lineIt);
			}
			else
			{
				break;
			}
		}
		else if (Util::isLetter(lineIt))
		{
			/*std::cout << "LETTER\t" << *lineIt << "\n";*/
			if (curToken->getID() == Token::IDTYPE_EMPTY)
			{
				curToken->setID(Token::IDTYPE_IDENTIFIER);
				curToken->push(*lineIt);
			}
			else if (curToken->getID() == Token::IDTYPE_IDENTIFIER)
			{
				curToken->push(*lineIt);
			}
			else
			{
				break;
			}
		}
		
		else if (*lineIt == '"')
		{
			/*std::cout << "QUOTES\t" << *lineIt << "\n";*/
			if (curToken->getID() == Token::IDTYPE_EMPTY)				/*Start of a string so intialize new token*/
			{
				curToken->setID(Token::IDTYPE_STRING);
				curToken->push(*lineIt);
				curToken->isString = true;
			}
			else if (curToken->getID() == Token::IDTYPE_IDENTIFIER && Util::isReservedWord(curToken->getTokenName()))
			{
				curToken->setID(Token::IDTYPE_RESERVEDWORD);
				break;
			}
			else
			{
				break;								/*Start of string so save the previous token*/
			}
		}
		else if (*lineIt == '\'')
		{
			/*std::cout << "QUOTES\t" << *lineIt << "\n";*/
			if (curToken->getID() == Token::IDTYPE_EMPTY)				/*Start of a string so intialize new token*/
			{
				curToken->setID(Token::IDTYPE_CHAR);
				curToken->push(*lineIt);
				curToken->isChar = true;
			}
			else if (curToken->getID() == Token::IDTYPE_IDENTIFIER && Util::isReservedWord(curToken->getTokenName()))
			{
				curToken->setID(Token::IDTYPE_RESERVEDWORD);
				break;
			}
			else
			{
				break;								/*Start of string so save the previous token*/
			}
		}
		else if (*lineIt == '\t' || *lineIt == ' ')
		{
			/*std::cout << "TABSPACE\t[" << *lineIt << "]\n";*/
			if (curToken->getID() == Token::IDTYPE_EMPTY || curToken->getID() == Token::IDTYPE_TABSPACE)
			{
				curToken->setID(Token::IDTYPE_TABSPACE);
				curToken->push(*lineIt);
			}
			else if (curToken->getID() == Token::IDTYPE_IDENTIFIER && Util::isReservedWord(curToken->getTokenName()))
			{
				curToken->setID(Token::IDTYPE_RESERVEDWORD);
				break;
			}
			else
			{
				break;
			}
		}
		else if (Util::isSymbol(lineIt).first || Util::isDoubleSymbol(lineIt).first)
		{
			/*std::cout << "SYMBOL\t" << *lineIt  << "\n";*/
			if (curToken->getID() == Token::IDTYPE_EMPTY)				/*Start of a symbol so intialize new token*/
			{
				if (Util::isMetaChar(lineIt))				/*If the symbol is a meta character, change the token to meta character*/
				{
					curToken->setID(Token::IDTYPE_METASTATEMENT);
					curToken->push(*lineIt);
				}
				else
				{
					curToken->setID(Token::IDTYPE_SYMBOL);			/*If the symbol is a not meta character, initialize the token to symbol*/
					curToken->push(*lineIt);
					if (Util::isDoubleSymbol(lineIt).first)		/*If the symbol consists of 2 parts then 2 positions should be moved forward*/
					{
						curToken->setSymType(Util::isDoubleSymbol(lineIt).second);
						++lineIt;
						curToken->push(*lineIt);
					}
					else
					{
						curToken->setSymType(Util::isSymbol(lineIt).second);
						// if(*lineIt == '.')
						// {
						// 	int len = 1;
						// 	while(*(lineIt + len)! = curLine.end())
						// 	{
						// 		if(len == 7) break;
						// 		len++;
						// 	}
						// 	if(len == 7)
						// 	{
						// 		if(*(lineIt+1) == 'c')
						// 		{
									
						// 			if(*(lineIt+2) == 'o' && *(lineIt+3) == 'l' && *(lineIt+4) == 'l' && *(lineIt+5) == 'e' && *(lineIt+6) == 'c' && *(lineIt+7) == 't')
						// 			{
						// 				for(char c:"collect")
						// 				{
						// 					curToken->push(c);
						// 				}
						// 				curToken->setID(Token::IDTYPE_RESERVEDWORD);
						// 				lineIt = lineIt + 7;
						// 			}
						// 		}
						// 	}					
						// 	else if(len >= 3)
						// 	{
						// 		if(*(lineIt+1) == 'm')
						// 		{
									
						// 			if(*(lineIt+2) == 'a' && *(lineIt+3) == 'p')
						// 			{
						// 				for(char c:"map")
						// 				{
						// 					curToken->push(c);
						// 				}
						// 				curToken->setID(Token::IDTYPE_RESERVEDWORD);
						// 				lineIt = lineIt + 3;
						// 			}
						// 		}	
						// 	}
						// }
					}
					++lineIt;
					break;
				}
			}
			else if (curToken->getID() == Token::IDTYPE_IDENTIFIER && Util::isReservedWord(curToken->getTokenName()))
			{
				curToken->setID(Token::IDTYPE_RESERVEDWORD);
				break;
			}
			else
			{
				break;
			}
		}
		else
		{									/* This branch will execute when the character is not a digit,
											 * letter, symbol, meta character, or part of a string
											 */
			/*std::cout<<"ELSE PART\t [" << *lineIt << "]\n";*/
			if (curToken->getID() == Token::IDTYPE_EMPTY)
			{
				++lineIt;
				curToken->setID(Token::IDTYPE_INVALID);
			} 
			else if (curToken->getID() == Token::IDTYPE_IDENTIFIER && Util::isReservedWord(curToken->getTokenName()))
			{
				curToken->setID(Token::IDTYPE_RESERVEDWORD);
			}
			break;
		}
		++lineIt;
	}

	if (curToken->isString && !curToken->isStringComplete)
	{
		/*std::cout<<"INCOMPLETE STRING\n";*/
		curToken->setID(Token::IDTYPE_INVALID);
	}
	if (curToken->isChar && !curToken->isCharComplete)
	{
		/*std::cout<<"INCOMPLETE STRING\n";*/
		curToken->setID(Token::IDTYPE_INVALID);
	}

}
