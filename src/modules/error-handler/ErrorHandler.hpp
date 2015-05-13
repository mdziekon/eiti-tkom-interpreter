#ifndef TKOM_MODULES_ERRORHANDLER_HPP
#define TKOM_MODULES_ERRORHANDLER_HPP

#ifndef TKOM_CONFIG_TERMINALCOLORS
#define TKOM_CONFIG_TERMINALCOLORS true
#endif

#ifndef TKOM_CONFIG_SILENTERRORS
#define TKOM_CONFIG_SILENTERRORS false
#endif

#include <string>
#include <map>
#include <exception>

namespace tkom { namespace modules
{
    class ErrorHandler
    {
    public:
        static void error(const std::string& message);
        static void warning(const std::string& message);
        static void notice(const std::string& message);

    private:
        static const std::map<std::string, const unsigned int>& getColors();

        static const std::string colorize(const std::string& message, const std::string& color);

        class Exception: public std::exception
        {
        public:
            Exception(const std::string& error) noexcept;
            virtual const char* what() const noexcept;

        private:
            const std::string error;
        };
    };
}}

#endif
