#ifndef TKOM_STRUCTURES_IR_FUNCTION_HPP
#define TKOM_STRUCTURES_IR_FUNCTION_HPP

#include <vector>
#include <memory>
#include <string>

#include "Block.hpp"
#include "Literal.hpp"

#include "../../modules/error-handler/ErrorHandler.hpp"
using ErrorHandler = tkom::modules::ErrorHandler;

namespace tkom { namespace structures { namespace ir
{
    struct Function: public Block
    {
        typedef std::shared_ptr<Function> ptr;

        std::string name;

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        )
        {
            ErrorHandler::error(
                std::string("Cannot execute function without parameters, fatal error")
            );
            return nullptr;
        }

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions,
            std::vector<std::shared_ptr<ir::Literal>> arguments
        )
        {
            auto thisScope = this->scopeProto.instantiate(scope);
            unsigned int argIdx = 0;
            for(auto& argument: arguments)
            {
                std::shared_ptr<ir::Literal> copy = std::make_shared<ir::Literal>();
                copy->data = argument->data;

                thisScope.variables.at(thisScope.varOrder.at(argIdx)) = copy;
                argIdx++;
            }

            for(auto& it: this->instructions)
            {
                auto result = it->execute(&thisScope, functions);
                if (result && result->loopJump)
                {
                    ErrorHandler::error(
                        std::string("Break/continue outside of loop")
                    );
                }
                if (result && it->canDoReturn())
                {
                    return result;
                }
            }

            ErrorHandler::error(
                std::string("No return, fatal error")
            );
            return nullptr;
        };
    };
}}}

#endif
