#include "./../include/Scanner.h"

Scanner::Scanner(std::string* source) 
{
    this->start = 0;
    this->current = 0;
    this->line = 1;

    this->source = source;

    tokens = new std::vector<Token*>();

    fillKeywords();
}

void Scanner::fillKeywords()
{
    keywords = new std::unordered_map<std::string, TokenType>();

    (*keywords)["and"] = TokenType::AND;
    (*keywords)["class"] = TokenType::CLASS;
    (*keywords)["else"] = TokenType::ELSE;
    (*keywords)["false"] = TokenType::FALSE;
    (*keywords)["for"] = TokenType::FOR;
    (*keywords)["fun"] = TokenType::FUN;
    (*keywords)["if"] = TokenType::IF;
    (*keywords)["nil"] = TokenType::NIL;
    (*keywords)["or"] = TokenType::OR;
    (*keywords)["print"] = TokenType::PRINT;
    (*keywords)["return"] = TokenType::RETURN;
    (*keywords)["super"] = TokenType::SUPER;
    (*keywords)["this"] = TokenType::THIS;
    (*keywords)["true"] = TokenType::TRUE;
    (*keywords)["var"] = TokenType::VAR;
    (*keywords)["while"] = TokenType::WHILE;

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
                // Line Comment Support
                // Comment found, skip the whole line
                // Consume till end of line
                // Token for a comment is not Added.
                while (peek() != '\n' && !isAtEnd()) {
                    advance();
                } 
            } else if (match('*')) {
                // Block comment support
                while (peek() != '*' && peekNext() != '/' && !isAtEnd()) {
                    if (advance() == '\n') {
                        line++;
                    }
                }
                // To handle last '*/'
                advance(); advance();
            } else {
                // lexeme is Division
                addToken(TokenType::SLASH);
            }
            break;

        // Handling White spaces
        case ' ':
        case '\r':  // Carriage Return Character 
        case '\t':
            // Ignore Whitespaces
            break;

        case '\n':
            line++;
            break;

        // Handling Strings
        case '"':
            string();
            break;

        default:
            // Handling Numbers
            // Handled like this because every digit switch case is tedious
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                // Error
                Lox::error(line, "Unexpected character. ");
            }

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

char Scanner::peekNext()
{
    if ((unsigned)current + 1 >= source->length()) {
        return '\0';
    }

    return source->at(current + 1);
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

bool Scanner::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c)
{
    // Since identifier can either start with alphabet or underscore
    return  (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
             c == '_';
}

void Scanner::identifier()
{
    while (isAlphaNumeric(peek())) {
        advance();
    }

    std::string text = source->substr(start, current - start);
    if (keywords->find(text) == keywords->end()) {
        addToken(TokenType::IDENTIFIER);
    } else {
        addToken(keywords->at(text));
    }
}

bool Scanner::isAlphaNumeric(char c)
{
    return isAlpha(c) || isDigit(c);
}

void Scanner::number()
{
    while (isDigit(peek())) {
        advance();
    }

    // Looking for Fractional Part
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the '.'
        advance();

        while (isDigit(peek())) {
            advance();
        }
    }

    // Since cpp doesnt support Object type to store 
    // String and Number as Object only
    // Number is also stored as string and will be later typecasted
    addToken(TokenType::NUMBER, new std::string(
        source->substr(start, current - start)
    ));
}

bool Scanner::isAtEnd()
{
    return (unsigned)current >= source->length();
}
