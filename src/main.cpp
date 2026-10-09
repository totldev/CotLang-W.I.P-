#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include "lexer.hpp"
#include "main.hpp"

std::filesystem::path curFile;

Main::Main()
{
}

std::string Main::getFileName() {
	return curFile.stem().string();
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "The .cot file is missing";
		return 1;
	}

	std::ifstream file(argv[1]);
	if (!file.is_open()) {
		std::cout << "The file path is incorrect\n";
		return 1;
	}

	curFile = argv[1];
	if (curFile.extension() != ".cot") {
		std::cout << "The file extension is not .cot\n";
		return 1;
	}

	//print all code
	
	//std::string line;
	//while (std::getline(file, line)) {
	//	std::cout << line << "\n";
	//}
	
	std::string source(
		(std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>()
	);

	//success
	std::cout << "Code successfully loaded\n";
	Lexer lexer(source);
	lexer.tokenize();

	return 0;
}