#ifndef TKOM_STRUCTURES_IR_SCOPEINST_HPP
#define TKOM_STRUCTURES_IR_SCOPEINST_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

#include "../../modules/error-handler/ErrorHandler.hpp"
using ErrorHandler = tkom::modules::ErrorHandler;

namespace tkom { namespace structures { namespace ir
{
    struct Literal;

    struct ScopeInst
    {
        ScopeInst* upperScope = nullptr;
        std::unordered_map<std::string, std::shared_ptr<Literal>> variables;
        std::vector<std::string> varOrder;

        std::shared_ptr<Literal> getVariable(const std::string& name)
        {
            auto it = this->variables.find(name);
            if (it != this->variables.end())
            {
                return it->second;
            }

            if (this->upperScope != nullptr)
            {
                return this->upperScope->getVariable(name);
            }

            return nullptr;
        }

        void setVariable(const std::string& name, std::shared_ptr<Literal> literal)
        {
            auto it = this->variables.find(name);
            if (it != this->variables.end())
            {
                it->second = literal;
                return;
            }

            if (this->upperScope != nullptr)
            {
                this->upperScope->setVariable(name, literal);
                return;
            }

            ErrorHandler::error(
                std::string("Setting undefined variable")
            );
            return ;
        }
    };
}}}

#endif
