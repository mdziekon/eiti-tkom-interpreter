#include "Parser.hpp"

#include "../lexer/Lexer.hpp"

#include <iostream>

using Parser = tkom::modules::Parser;
using Lexer = tkom::modules::Lexer;

Parser::Parser(Lexer& lexer):
lexer(lexer)
{}

void Parser::parse()
{
    Token token;

    do
    {
        token = this->lexer.nextToken();

        std::cout << tkom::modules::utils::getTokenTypeName(token.type) << " = " << token.value << std::endl;
    }
    while(token.type != TokenType::Invalid && token.type != TokenType::EndOfFile);
}
