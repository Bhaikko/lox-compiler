#include "./../include/Lox.h"

bool Lox::hadError = false;
bool Lox::hadRuntimeError = false;
Interpreter* Lox::interpreter = new Interpreter();

void Lox::report(int line, std::string where, std::string message) 
{
    std::cerr       << 
        "[line "    <<
        line        <<
        "] Error"   <<
        where       <<
        ": "        <<
        message     <<
    std::endl;

    Lox::hadError = true;
}

void Lox::error(Token* token, std::string message)
{
    if (token->type == TokenType::EOF_) {
        report(token->line, " at end", message);
    } else {
        report(token->line, " at '" + *(token->lexeme) + "'", message);
    }
}

void Lox::runtimeError(RuntimeError error)
{
    std::cerr << "[line " << error.token->line << " ] " << error.what() << std::endl;

    hadRuntimeError = true;
}

void Lox::error(int line, std::string message) 
{
    report(line, "", message);
}

void Lox::run(std::string* srcCode) 
{
    Scanner* scanner = new Scanner(srcCode);
    std::vector<Token*>* tokens = scanner->scanTokens();
    
    Parser* parser = new Parser(tokens);
    std::vector<Stmt::Stmt*>* statements = parser->parse();

    if (hadError) {
        return;
    }

    if (Lox::hadRuntimeError) {
        return;
    }

    interpreter->interpret(statements);
}

void Lox::runFile(char* filepath) 
{
    Lox::hadError = false;

    std::ifstream file(filepath);

    if (file) {
        std::ostringstream buffer;
        buffer << file.rdbuf();

        std::string content = buffer.str();

        run(&content);

        if (Lox::hadError) {
            exit(1);
        }

        if (Lox::hadRuntimeError) {
            exit(1);
        }
    }

}

void Lox::runPrompt() 
{
    Lox::hadError = false;

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
