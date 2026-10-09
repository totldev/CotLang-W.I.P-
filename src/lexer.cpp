#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>

//init
Lexer::Lexer(const std::string& source)
	: source(source)
{
}

//keywords
std::vector<std::string> Keywords = {
	"print"
};

//tokenizing
void Lexer::tokenize() {
	int line = 1;
	int charr = 0;
	for (size_t i = 0; i < source.size(); i++) {
		char c = source[i];
		charr++;
		if (c == '\n') { line++; charr = 0; }

		if (std::isspace(static_cast<unsigned char>(c))) { continue; }
		
		Token token;
		token.line = line;
		token.charr = charr;

		//operators
		if (c == '=') {
			token.name = std::string(1, c);
			token.token = Tokens::EQUALS;
			tokens.push_back(token);
			continue;
		}

		//braces
		if (c == '{') { 
			token.name = std::string(1, c);
			token.token = Tokens::LBRACE;
			tokens.push_back(token);
			continue;
		}
		if (c == '}') {
			token.name = std::string(1, c);
			token.token = Tokens::RBRACE;
			tokens.push_back(token);
			continue;
		}

		//bkts
		if (c == '(') {
			token.name = std::string(1, c);
			token.token = Tokens::LBKT;
			tokens.push_back(token);
			continue;
		}
		if (c == ')') {
			token.name = std::string(1, c);
			token.token = Tokens::RBKT;
			tokens.push_back(token);
			continue;
		}

		//idenfitiers
		if (std::isalpha(c)) {
			std::string name;

			while (i < source.size() && !std::isspace(static_cast<unsigned char>(source[i])) && (std::isalpha(static_cast<unsigned char>(source[i])) || std::isdigit(static_cast<unsigned char>(source[i])))) {
				charr++;
				name += source[i];
				i++;
			}
			charr--;
			i--;
			if (std::find(Keywords.begin(), Keywords.end(), name) != Keywords.end())
			{
				token.name = name;
				token.token = Tokens::KEYWORD;
				tokens.push_back(token);
				continue;
			}
			if (name == "true" || name == "false") {
				token.name = name;
				token.token = Tokens::BOOL;
				tokens.push_back(token);
				continue;
			}
			token.name = name;
			token.token = Tokens::IDENFITIER;
			tokens.push_back(token);
			continue;
		}

		if (c == '"') {
			std::string str;
			i++;

			while (i < source.size() && source[i] != '"' && source[i] != '\'') {
				str += source[i];
				charr++;
				i++;
			}
			token.name = str;
			token.token = Tokens::STRING;
			tokens.push_back(token);
			continue;
		}

		if (std::isdigit(c)) {
			std::string num;
			
			while (i < source.size() && std::isdigit(source[i])) {
				num += source[i];
				charr++;
				i++;
			}
			charr--;
			i--;
			token.name = num;
			token.token = Tokens::NUMBER;
			tokens.push_back(token);
			continue;
		}

		token.name = c;
		token.token = Tokens::UNKNOWN;
		tokens.push_back(token);
		continue;
	}

	//print all tokens
	
	//for (const Token& token : tokens)
	//{
	//	std::cout << token.name << " | " << tokenTypeToString(token.token) << "\n";
	//}

	//success
	std::cout << "Successful lexicalization\n";
	Parser parser(tokens);
	parser.parse();
}