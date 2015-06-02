#ifndef TKOM_STRUCTURES_IR_BLOCK_HPP
#define TKOM_STRUCTURES_IR_BLOCK_HPP

#include <vector>
#include <memory>

#include "Executable.hpp"
#include "ScopeProto.hpp"
#include "Instruction.hpp"

namespace tkom { namespace structures { namespace ir
{
    struct Block: public Instruction
    {
        ScopeProto scopeProto;
        std::vector<std::shared_ptr<Instruction>> instructions;

        virtual std::shared_ptr<Literal> execute(ScopeInst& scope)
        {
            // FIXME: Executre instructions
            return nullptr;
        }
    };
}}}

#endif
