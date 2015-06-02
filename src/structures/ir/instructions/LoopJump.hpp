#ifndef TKOM_STRUCTURES_IR_INSTRUCTIONS_LOOPJUMP_HPP
#define TKOM_STRUCTURES_IR_INSTRUCTIONS_LOOPJUMP_HPP

#include "../Instruction.hpp"
#include "../Executable.hpp"

namespace ir = tkom::structures::ir;

namespace tkom { namespace structures { namespace ir { namespace instructions
{
    struct LoopJump: public ir::Instruction
    {
        bool isBreak;

        virtual std::shared_ptr<Literal> execute(ScopeInst& scope)
        {
            // FIXME: Jump out of the loop
            return nullptr;
        }
    };
}}}}

#endif
