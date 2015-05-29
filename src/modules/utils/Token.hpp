#ifndef TKOM_MODULES_UTILS_TOKEN_HPP
#define TKOM_MODULES_UTILS_TOKEN_HPP

#include <string>

#include "TokenType.hpp"

using TokenType = tkom::modules::utils::TokenType;

namespace tkom { namespace modules { namespace utils
{
    struct Token
    {
        Token() = default;
        Token(const TokenType& type): type(type) {}

        TokenType type = TokenType::Invalid;
        std::string value = "";

        unsigned int line = 0;
        unsigned int pos = 0;
    };
}}}

#endif
