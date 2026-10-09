#pragma once
#include "parser.hpp"

#include <vector>
#include <unordered_set>

class Generator {
	public:
		Generator(const std::vector<std::unique_ptr<ASTNode>>& tree);
		void generate();
		void compile();
	private:
		const std::vector<std::unique_ptr<ASTNode>>& tree;
		std::unordered_set<std::string> declaredVars;
};