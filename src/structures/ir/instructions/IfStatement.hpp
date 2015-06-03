#ifndef TKOM_STRUCTURES_IR_INSTRUCTIONS_IFSTATEMENT_HPP
#define TKOM_STRUCTURES_IR_INSTRUCTIONS_IFSTATEMENT_HPP

#include <memory>
#include <iostream>

#include "../Instruction.hpp"
#include "../Condition.hpp"
#include "../Block.hpp"
#include "../Executable.hpp"

namespace ir = tkom::structures::ir;

namespace tkom { namespace structures { namespace ir { namespace instructions
{
    struct IfStatement: public ir::Instruction
    {
        std::shared_ptr<ir::Condition> condition;
        std::shared_ptr<ir::Block> trueBlock;
        std::shared_ptr<ir::Block> falseBlock;

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        )
        {
            if (this->condition->execute(scope, functions)->isTruthy())
            {
                return this->trueBlock->execute(scope, functions);
            }
            else if (this->falseBlock)
            {
                return this->falseBlock->execute(scope, functions);
            }

            return nullptr;
        }

        virtual bool canDoReturn()
        {
            return true;
        }
    };
}}}}

#endif
