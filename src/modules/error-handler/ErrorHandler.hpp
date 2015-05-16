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
        class Exception: public std::exception
        {
            friend class ErrorHandler;

        public:
            virtual const char* what() const noexcept;

        private:
            Exception(const std::string& error) noexcept;

            const std::string error;
        };

        static void debugFatal(const std::string& message);
        static void error(const std::string& message, const bool& noThrow = false);
        static void warning(const std::string& message);
        static void notice(const std::string& message);

    private:
        static const std::map<std::string, const unsigned int>& getColors();

        static const std::string colorize(const std::string& message, const std::string& color);
    };
}}

#endif
