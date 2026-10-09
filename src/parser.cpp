#include <iostream>
#include "parser.hpp"
#include "lexer.hpp"
#include "generator.hpp"
#include <algorithm>

//init
Parser::Parser(const std::vector<Token>& tokens)
	: tokens(tokens)
{
}

void Parser::parse() {
	for (size_t i = 0; i < tokens.size(); i++) {
		Token token = tokens[i];
		if (token.token == Tokens::KEYWORD) {
			i++;
			auto fnc = std::make_unique<Function>();
			fnc->name = token.name;
			if (i < tokens.size() && tokens[i].token == Tokens::LBKT) {
				i++;
				while (i < tokens.size() && tokens[i].token != Tokens::RBKT) {
					if (tokens[i].token == Tokens::UNKNOWN) {
						error(tokens[i], "Unknown idenfitier: " + tokens[i].name + "\n");
					} else if (tokens[i].token == Tokens::IDENFITIER) {
						if (std::find(ids.begin(), ids.end(), tokens[i].name) == ids.end()) {
							error(tokens[i], "Unknown idenfitier: " + tokens[i].name + "\n");
						}
					}

					fnc->arguments.push_back(tokens[i]);
					i++;
				}
				tree.push_back(std::move(fnc));
			}
		} else if (token.token == Tokens::UNKNOWN) {
			error(token, "Unknown idenfitier: "+token.name+"\n");
		} else if (token.token == Tokens::IDENFITIER) {
			if (i + 1 < tokens.size() && tokens[i + 1].token == Tokens::EQUALS) {
				if (i + 2 >= tokens.size()) {
					error(token, "Expected value after '='\n");
				}
				Token varVal = tokens[i + 2];
				if (varVal.token != Tokens::STRING && varVal.token != Tokens::NUMBER && varVal.token != Tokens::BOOL) {
					error(token, "Variable can't be a " + tokenTypeToString(varVal.token)+"\n");
				}
				if (symbolTable.find(token.name) != symbolTable.end()) {
					std::string existingType = symbolTable[token.name];
					if (existingType != tokenTypeToString(varVal.token)) {
						error(varVal, "Cannot be assigned "+existingType+" to "+tokenTypeToString(varVal.token)+"\n");
					}
				} else {
					symbolTable[token.name] = tokenTypeToString(varVal.token);
					ids.push_back(token.name);
				}

				auto var = std::make_unique<Var>();
				var->name = token.name;
				var->value = varVal;
				var->varType = tokenTypeToString(varVal.token);
				
				tree.push_back(std::move(var));
				i += 2;
				continue;
			}
			if (std::find(ids.begin(), ids.end(), token.name) == ids.end()) {
				error(token, "Unknown idenfitier: " + token.name + "\n");
			}
		}
	}

	//for (size_t i = 0; i < tree.size(); i++)
	//{
	//	ASTNode* node = tree[i].get();
	//	Function* function = dynamic_cast<Function*>(node);
	//	if (function)
	//	{
	//		std::cout << "Function: " << function->name << "\n";
	//		for (const Token& argument : function->arguments)
	//		{
	//			std::cout << "Argument: "
	//				<< argument.name << "\n";
	//		}
	//	}
	//}

	//success
	std::cout << "Successful parsing\n";
	Generator generator(tree);
	generator.generate();
}