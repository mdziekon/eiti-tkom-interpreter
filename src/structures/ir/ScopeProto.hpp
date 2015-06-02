#ifndef TKOM_STRUCTURES_IR_SCOPEPROTO_HPP
#define TKOM_STRUCTURES_IR_SCOPEPROTO_HPP

#include <unordered_map>
#include <string>
#include <memory>

#include "ScopeInst.hpp"

namespace tkom { namespace structures { namespace ir
{
    struct ScopeProto
    {
        ScopeProto* upperScope = nullptr;
        std::unordered_map<std::string, bool> variables;

        bool addVariable(const std::string& name)
        {
            if (this->hasVariable(name))
            {
                return false;
            }
            this->variables.insert({ { name, false } });
            return true;
        }

        bool* getVariable(const std::string& name)
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

        void setVariableDefined(const std::string& name)
        {
            auto variable = this->getVariable(name);

            if (variable == nullptr)
            {
                return;
            }

            (*variable) = true;
        }

        bool hasVariable(const std::string& name)
        {
            return this->getVariable(name) != nullptr;
        }

        bool isVariableDefined(const std::string& name)
        {
            auto variable = this->getVariable(name);

            if (variable == nullptr)
            {
                return false;
            }

            return (*variable);
        }

        ScopeInst instantiate(ScopeInst* upperScope)
        {
            auto instance = ScopeInst();
            instance.upperScope = upperScope;

            for(auto& it: this->variables)
            {
                instance.variables.insert({ { it.first, Literal() } });
            }

            return instance;
        }
    };
}}}

#endif
