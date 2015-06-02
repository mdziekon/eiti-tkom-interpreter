#ifndef TKOM_STRUCTURES_IR_EXPRESSION_HPP
#define TKOM_STRUCTURES_IR_EXPRESSION_HPP

#include <vector>
#include <memory>

#include "Assignable.hpp"
#include "ExpressionOperand.hpp"
#include "../../modules/utils/TokenType.hpp"

namespace tkom { namespace structures { namespace ir
{
    struct Expression: public Assignable, public ExpressionOperand
    {
        tkom::modules::utils::TokenType operation;
        std::vector<std::shared_ptr<ExpressionOperand>> operands;

        virtual std::shared_ptr<Literal> execute(ScopeInst& scope)
        {
            // FIXME: return computed literal
            return nullptr;
        }
    };
}}}

#endif
