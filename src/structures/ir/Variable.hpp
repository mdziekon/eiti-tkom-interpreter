#ifndef TKOM_STRUCTURES_IR_VARIABLE_HPP
#define TKOM_STRUCTURES_IR_VARIABLE_HPP

#include <vector>
#include <memory>

#include "Assignable.hpp"
#include "ConditionOperand.hpp"
#include "ExpressionOperand.hpp"

#include "ScopeInst.hpp"

namespace tkom { namespace structures { namespace ir
{
    struct Variable: public ConditionOperand, public ExpressionOperand
    {
        std::string name;
        std::shared_ptr<Assignable> indexArg1;
        std::shared_ptr<Assignable> indexArg2;

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        )
        {
            if (!this->indexArg1)
            {
                std::shared_ptr<Literal> ref = scope->getVariable(name);
                std::shared_ptr<Literal> copy = std::make_shared<Literal>();
                copy->data = ref->data;
                return copy;
            }

            std::shared_ptr<Literal> ref = scope->getVariable(name);
            std::shared_ptr<Literal> copy = std::make_shared<Literal>();
            copy->data = ref->data;
            auto indexArgVal = this->indexArg1->execute(scope, functions);
            if (indexArgVal->getSize() != std::make_pair<unsigned int, unsigned int>(1, 1))
            {
                ErrorHandler::error(
                    std::string("Cannot call index access using matrix")
                );
                return nullptr;
            }
            if (indexArgVal->data.at(0).at(0) < 0)
            {
                ErrorHandler::error(
                    std::string("Negative index (y)")
                );
                return nullptr;
            }
            if (copy->data.size() <= indexArgVal->data.at(0).at(0))
            {
                ErrorHandler::error(
                    std::string("Out of bound access (y)")
                );
                return nullptr;
            }
            copy->data = { copy->data.at(indexArgVal->data.at(0).at(0)) };

            if (!this->indexArg2)
            {
                return copy;
            }

            indexArgVal = this->indexArg2->execute(scope, functions);
            if (indexArgVal->getSize() != std::make_pair<unsigned int, unsigned int>(1, 1))
            {
                ErrorHandler::error(
                    std::string("Cannot call index access using matrix")
                );
                return nullptr;
            }
            if (indexArgVal->data.at(0).at(0) < 0)
            {
                ErrorHandler::error(
                    std::string("Negative index (x)")
                );
                return nullptr;
            }
            if (copy->data.at(0).size() <= indexArgVal->data.at(0).at(0))
            {
                ErrorHandler::error(
                    std::string("Out of bound access (x)")
                );
                return nullptr;
            }
            copy->data = { { copy->data.at(0).at(indexArgVal->data.at(0).at(0)) } };

            return copy;
        }
    };
}}}

#endif
