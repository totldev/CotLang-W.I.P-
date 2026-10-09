#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "lexer.hpp"

enum class NodeType {
	FUNCTION,
	VAR_DECL
};

struct ASTNode {
	NodeType type;
	virtual ~ASTNode() = default;
};

struct Function: ASTNode
{
	Function() { type = NodeType::FUNCTION; }
	std::string name;
	std::vector<Token> arguments;
};

struct Var : ASTNode {
	Var() { type = NodeType::VAR_DECL; }
	std::string name;
	Token value;
	std::string varType;
};

inline void error(const Token& tkn, const std::string& err)
{
	std::cout << "Error:\n";
	std::cout << err;
	std::cout << "Line: " << tkn.line
		<< "\nChar: " << tkn.charr << "\n";

	std::exit(1);
}

class Parser {
	public:
		Parser(const std::vector<Token>& tokens);
		void parse();
	private:
		std::vector<Token> tokens;
		std::vector<std::unique_ptr<ASTNode>> tree;
		std::vector<std::string> ids;
		std::unordered_map<std::string, std::string> symbolTable;
};