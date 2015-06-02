#ifndef TKOM_STRUCTURES_IR_VARIABLE_HPP
#define TKOM_STRUCTURES_IR_VARIABLE_HPP

#include <vector>
#include <memory>

#include "ConditionOperand.hpp"
#include "ExpressionOperand.hpp"

namespace tkom { namespace structures { namespace ir
{
    struct Variable: public ConditionOperand, public ExpressionOperand
    {
        std::string name;
        std::shared_ptr<Assignable> indexArg1;
        std::shared_ptr<Assignable> indexArg2;

        virtual std::shared_ptr<Literal> execute(ScopeInst& scope)
        {
            // FIXME: return value of variable
            return nullptr;
        }
    };
}}}

#endif
