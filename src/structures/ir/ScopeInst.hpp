#ifndef TKOM_STRUCTURES_IR_SCOPEINST_HPP
#define TKOM_STRUCTURES_IR_SCOPEINST_HPP

#include <unordered_map>
#include <string>
#include <memory>

#include "Variable.hpp"
#include "Literal.hpp"

namespace tkom { namespace structures { namespace ir
{
    struct ScopeInst
    {
        ScopeInst* upperScope = nullptr;
        std::unordered_map<std::string, Literal> variables;

        Literal* getVariable(const std::string& name)
        {
            auto it = this->variables.find(name);
            if (it != this->variables.end())
            {
                return &(it->second);
            }

            if (this->upperScope != nullptr)
            {
                return this->upperScope->getVariable(name);
            }

            return nullptr;
        }
    };
}}}

#endif
