#ifndef _TOKEN_H
#define _TOKEN_H

#include <string>

class Token
{
private:
	std::string myToken;
	int id;
	int symType;
public:
	bool isString;
	bool isStringComplete;
	bool isChar;
	bool isCharComplete;
	std::string arr[10] = {"IDTYPE_IDENTIFIER", "IDTYPE_NUMBER", "IDTYPE_RESERVEDWORD", "IDTYPE_SYMBOL", "IDTYPE_STRING", "IDTYPE_CHAR"
						, "IDTYPE_METASTATEMENT", "IDTYPE_TABSPACE", "IDTYPE_INVALID", "IDTYPE_EMPTY"};
public:
	static enum IDTYPE{
		IDTYPE_IDENTIFIER,
		IDTYPE_NUMBER,
		IDTYPE_RESERVEDWORD,
		IDTYPE_SYMBOL,
		IDTYPE_STRING,
		IDTYPE_CHAR,
		IDTYPE_METASTATEMENT,
		IDTYPE_TABSPACE,
		IDTYPE_INVALID,
		IDTYPE_EMPTY
	}ID;

	static enum SYMBOLTYPE{
		SYMTYPE_FULL_STOP,
		SYMTYPE_IMPLIES,
		SYMTYPE_LEFT_PARENTHESIS,
		SYMTYPE_RIGHT_PARENTHESIS,
		SYMTYPE_LEFT_BRACE,
		SYMTYPE_RIGHT_BRACE,	
		SYMTYPE_LEFT_BRACKET,
		SYMTYPE_RIGHT_BRACKET,
		SYMTYPE_COMMA,
		SYMTYPE_SEMICOLON,
		SYMTYPE_PLUS,
		SYMTYPE_MINUS,
		SYMTYPE_STAR,
		SYMTYPE_MOD,
		SYMTYPE_FORWARD_SLASH,
		SYMTYPE_DOUBLE_EQUAL,
		SYMTYPE_NT_EQUAL,
		SYMTYPE_GT,
		SYMTYPE_GT_EQUAL,
		SYMTYPE_LT,
		SYMTYPE_LT_EQUAL,
		SYMTYPE_EQUAL,
		SYMTYPE_DOUBLE_AND,
		SYMTYPE_DOUBLE_OR,
		SYMTYPE_INVALID
	}STYPE;

public:
	Token();
	
	void push(char c);

	void setID(int newID);

	int getID();

	std::string getStringID();

	void setSymType(int newSymType);

	int getSymType();

	std::string getTokenName();

	char last();
};
#endif
