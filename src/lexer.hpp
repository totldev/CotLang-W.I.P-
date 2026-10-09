#pragma once
#include <string>
#include <vector>

enum Tokens {
	IDENFITIER,
	LBRACE,
	RBRACE,
	LBKT,
	RBKT,
	KEYWORD,
	STRING,
	NUMBER,
	BOOL,
	EQUALS,
	UNKNOWN
};

struct Token
{
	std::string name;
	Tokens token;

	int line;
	int charr;
};

//enum to string
inline std::string tokenTypeToString(Tokens token)
{
	switch (token)
	{
	case Tokens::IDENFITIER: return "IDENTIFIER";
	case Tokens::LBRACE:     return "LBRACE";
	case Tokens::RBRACE:     return "RBRACE";
	case Tokens::LBKT:       return "LBKT";
	case Tokens::RBKT:       return "RBKT";
	case Tokens::KEYWORD:    return "KEYWORD";
	case Tokens::STRING:     return "STRING";
	case Tokens::NUMBER:     return "NUMBER";
	case Tokens::BOOL:     return "BOOL";
	case Tokens::EQUALS:     return "EQUALS";
	case Tokens::UNKNOWN:    return "UNKNOWN";
	}

	return "UNKNOWN_IN_CONVERTER";
}

class Lexer {
	public:
		Lexer(const std::string& source);
		void tokenize();
	private:
		std::string source;
		std::vector<Token> tokens;
};