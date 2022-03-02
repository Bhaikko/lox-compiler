#pragma once

#include <stdexcept>

namespace Runtime {
    /**
     * @brief Exception because it will be used to return from 
     * Call stack of cpp and return value of Lox function
     * 
     */
    class Return: public std::runtime_error
    {
        public:
            void* value;

        public:
            Return(void* value);
    };
}