#ifndef TKOM_MODULES_TRACER_HPP
#define TKOM_MODULES_TRACER_HPP

#include <string>

#include "../terminal-printer/TerminalPrinter.hpp"

namespace tkom { namespace modules
{
    class Tracer: public TerminalPrinter
    {
    public:
        Tracer(const bool& enabled = false);

        void reset();

        void enter(const std::string& message = "");
        void leave(const std::string& message = "");
        void info(const std::string& message);

    private:
        const bool enabled;
        unsigned int nestingLevel = 0;

        void printNesting();
    };
}}

#endif
