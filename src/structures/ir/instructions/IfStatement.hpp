#ifndef TKOM_STRUCTURES_IR_INSTRUCTIONS_IFSTATEMENT_HPP
#define TKOM_STRUCTURES_IR_INSTRUCTIONS_IFSTATEMENT_HPP

#include <memory>

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

        virtual std::shared_ptr<Literal> execute(ScopeInst& scope)
        {
            // FIXME: Execute one of the blocks
            return nullptr;
        }
    };
}}}}

#endif
