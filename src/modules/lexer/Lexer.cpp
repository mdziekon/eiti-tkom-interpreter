#include "Lexer.hpp"

#include <cctype>
#include <cstdio>
#include <algorithm>

#include "../utils/Keywords.hpp"

using Lexer = tkom::modules::Lexer;
namespace utils = tkom::modules::utils;

Lexer::Lexer(const std::string& file):
reader(file)
{}

const Token Lexer::nextToken()
{
    Token token;
    auto sign = this->reader.nextSign();

    while(isspace(sign))
    {
        sign = this->reader.nextSign();
    }

    token.line = this->reader.getCurrentLineNo();
    token.pos = this->reader.getCurrentSignPos() - 1;
    token.lineStart = this->reader.getCurrentLinePos();

    if (this->reader.hasFinished())
    {
        token.type = TokenType::EndOfFile;
        return token;
    }

    if (isalpha(sign) || sign == '_' || sign == '$')
    {
        // Keyword or identifier
        std::string buffer;

        do
        {
            buffer.push_back(sign);

            sign = this->reader.nextSign();
        }
        while(isalnum(sign) || sign == '_' || sign == '$');

        this->reader.rewind();
        auto tempBuff = buffer;
        std::transform(tempBuff.begin(), tempBuff.end(), tempBuff.begin(), ::tolower);

        if (utils::keywords.count(tempBuff) == 1)
        {
            // Keyword
            token.type = utils::keywords.at(tempBuff);
        }
        else
        {
            // Identifier
            token.type = TokenType::Identifier;
            token.value = buffer;
        }
    }
    else if (isdigit(sign))
    {
        // Finite number
        std::string buffer;

        do
        {
            buffer.push_back(sign);

            sign = this->reader.nextSign();
        }
        while(isdigit(sign) || sign == '.');

        this->reader.rewind();

        token.type = TokenType::NumberLiteral;
        token.value = buffer;
    }
    else
    {
        // Special characters

        switch (sign)
        {
            case '=':
            {
                if (this->reader.nextSign() == '=')
                {
                    token.type = TokenType::Equality;
                }
                else
                {
                    this->reader.rewind();
                    token.type = TokenType::Assignment;
                }
                break;
            }
            case '<':
            {
                if (this->reader.nextSign() == '=')
                {
                    token.type = TokenType::LessOrEqual;
                }
                else
                {
                    this->reader.rewind();
                    token.type = TokenType::Less;
                }
                break;
            }
            case '>':
            {
                if (this->reader.nextSign() == '=')
                {
                    token.type = TokenType::GreaterOrEqual;
                }
                else
                {
                    this->reader.rewind();
                    token.type = TokenType::Greater;
                }
                break;
            }
            case '!':
            {
                if (this->reader.nextSign() == '=')
                {
                    token.type = TokenType::Inequality;
                }
                else
                {
                    this->reader.rewind();
                    token.type = TokenType::Negation;
                }
                break;
            }
            case '&':
            {
                if (this->reader.nextSign() == '&')
                {
                    token.type = TokenType::And;
                }
                else
                {
                    this->reader.rewind();
                    token.type = TokenType::Invalid;
                }
                break;
            }
            case '|':
            {
                if (this->reader.nextSign() == '|')
                {
                    token.type = TokenType::Or;
                }
                else
                {
                    this->reader.rewind();
                    token.type = TokenType::Invalid;
                }
                break;
            }
            default:
            {
                if (utils::simpleSigns.count(sign) == 1)
                {
                    token.type = utils::simpleSigns.at(sign);
                }
                else
                {
                    token.type = TokenType::Invalid;
                }
                break;
            }
        }
    }

    return token;
}

const std::string Lexer::getLine(const std::streampos& linePos)
{
    return this->reader.getLine(linePos);
}
