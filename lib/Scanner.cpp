#include "./../include/Scanner.h"

Scanner::Scanner(std::string* source) 
{
    this->start = 0;
    this->current = 0;
    this->line = 1;

    this->source = source;

    tokens = new std::vector<Token*>();
}

std::vector<Token*>* Scanner::scanTokens() 
{
    while (!isAtEnd()) {

        start = current;
        scanToken();
    }

    // Adding End Of File
    tokens->push_back(new Token(TokenType::EOF_, nullptr, nullptr, line));
    return tokens;
}

void Scanner::addToken(TokenType type)
{
    addToken(type, nullptr);
}

void Scanner::addToken(TokenType type, std::string* literal)
{
    std::string* text = new std::string(source->substr(start, current - start));
    tokens->push_back(new Token(type, text, literal, line));
}

char Scanner::advance()
{
    current++;
    return (*source)[current - 1];
}

void Scanner::scanToken()
{
    char c = advance();

    switch (c) {
        // Matching Single Length possible lexemes
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;

        // Matching 2 Length possible lexemes
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;

        // Handling '/'
        // Division can also lead to Comment '//'
        case '/':
            if (match('/')) {
                // Comment found, skip the whole line
                // Consume till end of line
                // Token for a comment is not Added.
                while (peek() != '\n' && !isAtEnd()) {
                    advance();
                } 
            } else {
                // lexeme is Division
                addToken(TokenType::SLASH);
            }
            break;

        case ' ':
        case '\r':  // Carriage Return Character 
        case '\t':
            // Ignore Whitespaces
            break;

        case '\n':
            line++;
            break;

        case '"':
            string();
            break;

        default:
            // Error
            // Lox::error(line, "Unexpected character. ");
            break;
    }
}

/**
 * @brief Matches more than one length lexemes for possibility of token. 
 * Matches for lexeme specific code.
 * @param expected - Character to match with
 * @return true - more than one length lexeme
 * @return false - one length lexeme
 */
bool Scanner::match(char expected)
{
    if (isAtEnd()) {
        return false;
    }

    if (source->at(current) != expected) {
        return false;
    }

    current++;
    return true;
}

/**
 * @brief Difference between peek() and advance() is this doesn't consume current character
 * 
 * @return char 
 */
char Scanner::peek()
{
    if (isAtEnd()) {
        return '\0';
    }
    return source->at(current);
}

void Scanner::string()
{
    while (peek() != '"' && !isAtEnd()) {
        // Lox supports multiline Strings
        // Checking for single line string is more complex
        if (peek() == '\n') {
            line++;
        }

        advance();
    }

    if (isAtEnd()) {
        Lox::error(line, "Unterminated string.");
        return;
    }

    // The closing "
    advance();

    std::string* value = new std::string(
        source->substr(start + 1, current - start - 2)
    );

    std::cout << *value << std::endl;
    addToken(TokenType::STRING, value);
}

bool Scanner::isAtEnd()
{
    return (unsigned)current >= source->length();
}
