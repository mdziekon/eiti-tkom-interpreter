#ifndef TKOM_MODULES_EXECUTOR_HPP
#define TKOM_MODULES_EXECUTOR_HPP

#include <unordered_map>
#include <string>

namespace tkom { namespace modules
{
    class Executor
    {
    public:
        bool addFunction(const std::string& name);

    private:
        std::unordered_map<std::string, bool> definedFunctions;
    };
}}

#endif
