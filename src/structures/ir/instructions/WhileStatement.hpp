#ifndef TKOM_STRUCTURES_IR_INSTRUCTIONS_WHILESTATEMENT_HPP
#define TKOM_STRUCTURES_IR_INSTRUCTIONS_WHILESTATEMENT_HPP

#include <memory>

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

        virtual std::shared_ptr<Literal> execute(ScopeInst& scope)
        {
            // FIXME: Executre block until condition is met
            return nullptr;
        }
    };
}}}}

#endif
