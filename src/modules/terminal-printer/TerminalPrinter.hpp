#ifndef TKOM_MODULES_TERMINALPRINTER_HPP
#define TKOM_MODULES_TERMINALPRINTER_HPP

#ifndef TKOM_CONFIG_TERMINALCOLORS
#define TKOM_CONFIG_TERMINALCOLORS true
#endif

#include <string>
#include <map>

namespace tkom { namespace modules
{
    class TerminalPrinter
    {
    protected:
        static const std::map<std::string, const unsigned int>& getColors();

        static const std::string colorize(const std::string& message, const std::string& color);
        static void printLabel(const std::string& message, const std::string& color = "");
        static const unsigned int getLabelLength(const std::string& message);
    };
}}

#endif
