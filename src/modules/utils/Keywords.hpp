#ifndef TKOM_MODULES_UTILS_KEYWORDS
#define TKOM_MODULES_UTILS_KEYWORDS

#include <unordered_map>

#include "TokenType.hpp"

using TokenType = tkom::modules::utils::TokenType;

namespace tkom { namespace modules { namespace utils
{
    const std::unordered_map<std::string, TokenType>& keywords = {
        { "function", TokenType::Function },
        { "if", TokenType::If },
        { "while", TokenType::While },
        { "else", TokenType::Else },
        { "return", TokenType::Return },
        { "continue", TokenType::Continue },
        { "break", TokenType::Break },
        { "var", TokenType::Var },
        { "or", TokenType::Or },
        { "and", TokenType::And },
        { "infinity", TokenType::Infinity }
    };

    const std::unordered_map<char, TokenType>& simpleSigns = {
        { '(', TokenType::ParenthOpen },
        { ')', TokenType::ParenthClose },
        { '{', TokenType::BracketOpen },
        { '}', TokenType::BracketClose },
        { '[', TokenType::SquareBracketOpen },
        { ']', TokenType::SquareBracketClose },
        { ',', TokenType::Comma },
        { ';', TokenType::Semicolon },
        { '+', TokenType::Plus },
        { '-', TokenType::Minus },
        { '*', TokenType::Multiply },
        { '/', TokenType::Divide },
        { '%', TokenType::Modulo },
        { '.', TokenType::Dot }
    };

}}}

#endif
