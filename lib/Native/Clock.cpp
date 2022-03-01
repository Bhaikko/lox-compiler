#include "./../../include/Native/Clock.h"

unsigned int Clock::arity()
{
    return 0;
}

std::string* Clock::call(Interpreter* interpreter, std::vector<std::string*>* arguements)
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    return new std::string(std::to_string(now_c));
}

std::ostream& operator<<(std::ostream& os, const Clock& t) {
    os << std::string("<native fn>");
    return os;
}