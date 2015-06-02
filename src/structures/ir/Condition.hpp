#ifndef TKOM_STRUCTURES_IR_CONDITION_HPP
#define TKOM_STRUCTURES_IR_CONDITION_HPP

#include <vector>
#include <memory>

#include "Executable.hpp"
#include "ConditionOperand.hpp"
#include "../../modules/utils/TokenType.hpp"

namespace tkom { namespace structures { namespace ir
{
    struct Condition: public ConditionOperand
    {
        bool negated = false;
        tkom::modules::utils::TokenType operation;
        std::vector<std::shared_ptr<ConditionOperand>> operands;

        virtual std::shared_ptr<Literal> execute(ScopeInst& scope)
        {
            // FIXME: Return truthy or falsy matrix literal
            return nullptr;
        }
    };
}}}

#endif
