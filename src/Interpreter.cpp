#include "Interpreter.hpp"

#include "modules/error-handler/ErrorHandler.hpp"

tkom::Interpreter::Interpreter(const std::vector<std::string>& arguments)
{
    try
    {
        modules::ErrorHandler::error("Hello world!");
    }
    catch (std::exception& e)
    {}

    modules::ErrorHandler::warning("Hello world!");
    modules::ErrorHandler::notice("Hello world!");

    // Main program body
}
