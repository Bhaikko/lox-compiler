#include "./../../include/Interpreter/RuntimeError.h"

RuntimeError::RuntimeError(Token* token, std::string message) : std::runtime_error(message)
{
    this->token = token;
}