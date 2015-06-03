#ifndef TKOM_STRUCTURES_IR_INSTRUCTIONS_LOOPJUMP_HPP
#define TKOM_STRUCTURES_IR_INSTRUCTIONS_LOOPJUMP_HPP

#include "../Instruction.hpp"
#include "../Executable.hpp"
#include <iostream>

namespace ir = tkom::structures::ir;

namespace tkom { namespace structures { namespace ir { namespace instructions
{
    struct LoopJump: public ir::Instruction
    {
        bool isBreak;

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        )
        {
            auto result = std::make_shared<ir::Literal>();
            result->loopJump = true;
            result->isBreak = this->isBreak;

            return result;
        }
    };
}}}}

#endif
