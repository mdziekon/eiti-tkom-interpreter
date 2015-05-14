#include "Interpreter.hpp"

#include "modules/error-handler/ErrorHandler.hpp"
#include "modules/lexer/Lexer.hpp"
#include "modules/parser/Parser.hpp"

using Interpreter = tkom::Interpreter;
using ErrorHandler = tkom::modules::ErrorHandler;
using Lexer = tkom::modules::Lexer;
using Parser = tkom::modules::Parser;

Interpreter::Interpreter(const std::vector<std::string>& arguments)
{
    try
    {
        if (arguments.size() < 1)
        {
            ErrorHandler::error("No input file specified");
        }

        Lexer lexer(arguments.at(0));
        Parser parser(lexer);

        parser.parse();
    }
    catch(ErrorHandler::Exception &e)
    {
        ErrorHandler::error("Terminating...", true);
    }
}
