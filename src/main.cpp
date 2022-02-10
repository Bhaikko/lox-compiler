#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "./../include/Scanner.h"

bool hadError = true;

void report(int line, std::string where, std::string message)
{
    std::cerr       << 
        "[line "    <<
        line        <<
        "] Error"   <<
        where       <<
        ": "        <<
        message;

    hadError = true;
}

void error(int line, std::string message)
{
    report(line, "", message);
}

// Scans the source code and categorizes token
void run(std::string* srcCode)
{
    
    Scanner* scanner = new Scanner(srcCode);
    std::vector<Token*>* tokens = scanner->scanTokens();
    
    // std::cout << tokens->size() << std::endl;
    for (Token* token : (*tokens)) {
    
        // std::cout << *token << std::endl;
        
    }
    
}

void runFile(char* filepath)
{
    std::ifstream file(filepath);

    if (file) {
        std::ostringstream buffer;
        buffer << file.rdbuf();

        std::string content = buffer.str();

        run(&content);

        if (hadError) {
            exit(1);
        }
    }
}

void runPrompt()
{
    std::string line;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.size() == 0) {
            break;
        }

        run(&line);
        hadError = false;
    }
}

int main(int argc, char** argv)
{
    if (argc > 2) {
        std::cout << "Usage: jlox [script]" << std::endl;
        exit(1);
    } else if (argc == 2) {
        // If File path is provided
        runFile(argv[1]);
    } else {
        // Running an Interactive Console - REPL
        runPrompt();
    }

    return 0;
}