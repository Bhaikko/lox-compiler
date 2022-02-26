#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "./../include/Lox.h"

int main(int argc, char** argv)
{
    // // Only for debugging purposes
    // char path[] = "./test/loops.lox";
    // // Only for Debugging Purposes
    // Lox::runFile(path);

    if (argc > 2) {
        std::cout << "Usage: jlox [script]" << std::endl;
        exit(1);
    } else if (argc == 2) {
        // If File path is provided
        Lox::runFile(argv[1]);
    } else {
        // Running an Interactive Console - REPL
        Lox::runPrompt();
    }

    return 0;
}