#include "generator.hpp"
#include "parser.hpp"
#include "main.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <unordered_set>

//init
Generator::Generator(const std::vector<std::unique_ptr<ASTNode>>& tree)
	: tree(tree)
{
}

void Generator::generate()
{
    std::ofstream file("generated.cpp");

    // includes
    file << "#include <iostream>\n";
    file << "#include <string>\n";
    file << "\n";

    // main
    file << "int main(int argc, char* argv[])\n";
    file << "{\n";

    for (const auto& node : tree)
    {
        if (node->type == NodeType::VAR_DECL) {
            Var* var = dynamic_cast<Var*>(node.get());
            if (var) {
                bool isAlreadyDeclared = (declaredVars.find(var->name) != declaredVars.end());
                if (!isAlreadyDeclared) {
                    if (var->varType == "STRING") {
                        file << "   std::string " << var->name << " = \"" << var->value.name << "\";\n";
                    }
                    else if (var->varType == "NUMBER") {
                        file << "   int " << var->name << " = " << var->value.name << ";\n";
                    }
                    else if (var->varType == "BOOL") {
                        file << "   bool " << var->name << " = " << var->value.name << ";\n";
                    }
                    declaredVars.insert(var->name);
                } else {
                    if (var->varType == "STRING") {
                        file << "   " << var->name << " = \"" << var->value.name << "\";\n";
                    }
                    else if (var->varType == "NUMBER") {
                        file << "   " << var->name << " = " << var->value.name << ";\n";
                    }
                    else if (var->varType == "BOOL") {
                        file << "   " << var->name << " = " << var->value.name << ";\n";
                    }
                }
            }
        } else if (node->type == NodeType::FUNCTION) {
            Function* function = dynamic_cast<Function*>(node.get());
            if (function == nullptr)
                continue;
            if (function->name == "print")
            {
                file << "   std::cout << std::boolalpha";


                for (const Token& argument : function->arguments)
                {
                    if (argument.token == Tokens::STRING) {
                        file << " << \"" << argument.name << "\"";
                    }
                    else {
                        file << " << " << argument.name;
                    }
                }

                file << ";\n";
            }
        }
    }

    // end of main
    file << "    std::cout << \"\\nPress any key to exit...\";\n";
    file << "    std::cin.get();\n";
    file << "   return 0;";
    file << "}\n";

    file.close();

    std::cout << "Successful generating\n";

    compile();
}

void Generator::compile()
{
    Main main;
    std::string filename = main.getFileName();
    std::string command = "gcc\\w64devkit\\bin\\g++.exe generated.cpp -o " + filename + ".exe -mconsole";
    std::string runcmd = filename + ".exe";

    int result = std::system(command.c_str());

    if (result == 0) {
        std::cout << "Successful compiling\n";
        std::system(runcmd.c_str());
    } else {
        std::cout << "Compilation failed\n";
    }
}