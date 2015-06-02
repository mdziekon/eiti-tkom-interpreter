#include "StdLib.hpp"

using StdLib = tkom::modules::StdLib;

const std::unordered_map<std::string, bool>&
StdLib::getStandardFunctions()
{
    static const std::unordered_map<std::string, bool> list = {
        { "generate", true },
        { "resize", true },
        { "size", true },
        { "clone", true },
        { "print", true },
        { "transpose", true }
    };

    return list;
}

bool
StdLib::hasFunction(const std::string& name)
{
    return (StdLib::getStandardFunctions()).count(name) == 1;
}
