#ifndef TKOM_STRUCTURES_IR_LITERAL_HPP
#define TKOM_STRUCTURES_IR_LITERAL_HPP

#include <vector>
#include <memory>

#include "ConditionOperand.hpp"
#include "ExpressionOperand.hpp"

namespace tkom { namespace structures { namespace ir
{
    struct Literal: public ConditionOperand, public ExpressionOperand
    {
        std::vector<std::vector<double>> data = {{}};

        virtual std::shared_ptr<Literal> execute(ScopeInst& scope)
        {
            // FIXME: return copy of itself
            return nullptr;
        }
    };
}}}

#endif
