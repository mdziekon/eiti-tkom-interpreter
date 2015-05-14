#ifndef TKOM_MODULES_UTILS_TOKENTYPE_HPP
#define TKOM_MODULES_UTILS_TOKENTYPE_HPP

#include <unordered_map>
#include <string>

namespace tkom { namespace modules { namespace utils
{
    enum class TokenType: unsigned int
    {
        Function = 0,
        ParenthOpen = 1,
        ParenthClose = 2,
        BracketOpen = 3,
        BracketClose = 4,
        SquareBracketOpen = 5,
        SquareBracketClose = 6,
        Comma = 7,
        Semicolon = 8,
        If = 9,
        While = 10,
        Else = 11,
        Return = 12,
        Continue = 13,
        Break = 14,
        Var = 15,
        Negation = 16,
        Assignment = 17,
        Or = 18,
        And = 19,
        Equality = 20,
        Inequality = 21,
        Less = 22,
        Greater = 23,
        LessOrEqual = 24,
        GreaterOrEqual = 25,
        Plus = 26,
        Minus = 27,
        Multiply = 28,
        Divide = 29,
        Modulo = 30,
        Infinity = 31,
        Dot = 32,
        Identifier = 33,
        NumberLiteral = 34,
        Invalid = 35,
        EndOfFile = 36
    };

    const std::unordered_map<unsigned int, std::string> tokenTypeNames = {
        { 0, "Function"},
        { 1, "ParenthOpen"},
        { 2, "ParenthClose"},
        { 3, "BracketOpen"},
        { 4, "BracketClose"},
        { 5, "SquareBracketOpen"},
        { 6, "SquareBracketClose"},
        { 7, "Comma"},
        { 8, "Semicolon"},
        { 9, "If"},
        { 10, "While"},
        { 11, "Else"},
        { 12, "Return"},
        { 13, "Continue"},
        { 14, "Break"},
        { 15, "Var"},
        { 16, "Negation"},
        { 17, "Assignment"},
        { 18, "Or"},
        { 19, "And"},
        { 20, "Equality"},
        { 21, "Inequality"},
        { 22, "Less"},
        { 23, "Greater"},
        { 24, "LessOrEqual"},
        { 25, "GreaterOrEqual"},
        { 26, "Plus"},
        { 27, "Minus"},
        { 28, "Multiply"},
        { 29, "Divide"},
        { 30, "Modulo"},
        { 31, "Infinity"},
        { 32, "Dot"},
        { 33, "Identifier"},
        { 34, "NumberLiteral"},
        { 35, "Invalid"},
        { 36, "EndOfFile"}
    };

    inline const std::string getTokenTypeName(const TokenType& tokenType)
    {
        return tokenTypeNames.at((unsigned int) tokenType);
    };
}}}

#endif
