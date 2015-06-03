#ifndef TKOM_STRUCTURES_IR_BLOCK_HPP
#define TKOM_STRUCTURES_IR_BLOCK_HPP

#include <vector>
#include <memory>
#include <iostream>

#include "Executable.hpp"
#include "ScopeProto.hpp"
#include "Instruction.hpp"
#include "Literal.hpp"

namespace tkom { namespace structures { namespace ir
{
    struct Block: public Instruction
    {
        ScopeProto scopeProto;
        std::vector<std::shared_ptr<Instruction>> instructions;

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        )
        {
            auto thisScope = this->scopeProto.instantiate(scope);

            for(auto& it: this->instructions)
            {
                auto result = it->execute(&thisScope, functions);
                if (result && ( result->loopJump || it->canDoReturn()))
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
}}}

#endif
