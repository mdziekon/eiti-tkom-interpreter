#ifndef TKOM_MODULES_STDLIB_HPP
#define TKOM_MODULES_STDLIB_HPP

#include <unordered_map>
#include <string>

namespace tkom { namespace modules
{
    struct StdLib
    {
        static const std::unordered_map<std::string, bool>& getStandardFunctions();
        static bool hasFunction(const std::string& name);
    };
}}

#endif
