#include "ErrorHandler.hpp"

#include <sstream>
#include <iostream>

using ErrorHandler = tkom::modules::ErrorHandler;

void ErrorHandler::error(const std::string& message, const bool& noThrow)
{
    std::cout << ErrorHandler::colorize("[Error]", "red")
              << " " << message
              << std::endl;

    if (noThrow)
    {
        return;
    }

    throw ErrorHandler::Exception(message);
}

void ErrorHandler::warning(const std::string& message)
{
    std::cout << ErrorHandler::colorize("[Warn] ", "yellow")
              << " " << message
              << std::endl;
}

void ErrorHandler::notice(const std::string& message)
{
    std::cout << ErrorHandler::colorize("[Note] ", "cyan")
              << " " << message
              << std::endl;
}

const std::map<std::string, const unsigned int>& ErrorHandler::getColors()
{
    static const std::map<std::string, const unsigned int> colors = {
        { "red", 31 },
        { "yellow", 33 },
        { "cyan", 36 }
    };

    return colors;
}

const std::string ErrorHandler::colorize(const std::string& message, const std::string& color)
{
    if (TKOM_CONFIG_TERMINALCOLORS && ErrorHandler::getColors().count(color) == 1)
    {
        std::stringstream temp;

        temp << "\e[" << ErrorHandler::getColors().at(color) << "m"
             << message
             << "\e[0m";

        return temp.str();
    }

    return message;
}

ErrorHandler::Exception::Exception(const std::string& error) noexcept:
error(error)
{}

const char* ErrorHandler::Exception::what() const noexcept
{
    return this->error.c_str();
}
