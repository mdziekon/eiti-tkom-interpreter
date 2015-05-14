#include "Interpreter.hpp"

#include "modules/error-handler/ErrorHandler.hpp"
#include "modules/lexer/Lexer.hpp"

#include <iostream>

using Interpreter = tkom::Interpreter;
using ErrorHandler = tkom::modules::ErrorHandler;
using Lexer = tkom::modules::Lexer;

Interpreter::Interpreter(const std::vector<std::string>& arguments)
{
    try
    {
        if (arguments.size() < 1)
        {
            ErrorHandler::error("No input file specified");
        }

        Lexer lexer(arguments.at(0));

        Token token;

        do
        {
            token = lexer.nextToken();

            std::cout << tkom::modules::utils::getTokenTypeName(token.type) << " = " << token.value << std::endl;
        }
        while(token.type != TokenType::Invalid && token.type != TokenType::EndOfFile);
    }
    catch(ErrorHandler::Exception &e)
    {
        ErrorHandler::error("Terminating...", true);
    }
}
