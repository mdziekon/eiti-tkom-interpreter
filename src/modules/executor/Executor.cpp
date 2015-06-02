#include "Executor.hpp"

using Executor = tkom::modules::Executor;

bool Executor::addFunction(const std::string& name)
{
    if (this->definedFunctions.count(name) == 1)
    {
        return false;
    }

    this->definedFunctions.insert({ { name, true } });

    return true;
}
