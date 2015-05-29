#include "ErrorHandler.hpp"

#include <sstream>
#include <iostream>

using ErrorHandler = tkom::modules::ErrorHandler;
using Exception = tkom::modules::ErrorHandler::Exception;

// Exception class
Exception::Exception(const std::string& error) noexcept:
error(error)
{}

const char* Exception::what() const noexcept
{
    return this->error.c_str();
}


// ErrorHandler class
void ErrorHandler::debugFatal(const std::string& message)
{
    ErrorHandler::printLabel("Fatal", "magenta");
    std::cout << message << std::endl;

    throw ErrorHandler::Exception(message);
}

void ErrorHandler::error(const std::string& message, const bool& noThrow)
{
    ErrorHandler::printLabel("Error", "red");
    std::cout << message << std::endl;

    if (noThrow)
    {
        return;
    }

    throw ErrorHandler::Exception(message);
}

void ErrorHandler::warning(const std::string& message)
{
    ErrorHandler::printLabel("Warn", "yellow");
    std::cout << message << std::endl;
}

void ErrorHandler::notice(const std::string& message)
{
    ErrorHandler::printLabel("Note", "cyan");
    std::cout << message << std::endl;
}
