#ifndef TKOM_STRUCTURES_IR_INSTRUCTIONS_WHILESTATEMENT_HPP
#define TKOM_STRUCTURES_IR_INSTRUCTIONS_WHILESTATEMENT_HPP

#include <memory>
#include <iostream>

#include "../Instruction.hpp"
#include "../Condition.hpp"
#include "../Block.hpp"
#include "../Executable.hpp"

namespace ir = tkom::structures::ir;

namespace tkom { namespace structures { namespace ir { namespace instructions
{
    struct WhileStatement: public ir::Instruction
    {
        std::shared_ptr<ir::Condition> condition;
        std::shared_ptr<ir::Block> block;

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        )
        {
            while (this->condition->execute(scope, functions)->isTruthy())
            {
                auto result = this->block->execute(scope, functions);
                if (result && result->loopJump)
                {
                    if (result->isBreak)
                    {
                        break;
                    }
                    continue;
                }
                if (result && this->block->canDoReturn())
                {
                    return result;
                }
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
