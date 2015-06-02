#ifndef TKOM_STRUCTURES_IR_INSTRUCTIONS_CALL_HPP
#define TKOM_STRUCTURES_IR_INSTRUCTIONS_CALL_HPP

#include <vector>
#include <memory>

#include "../Instruction.hpp"
#include "../Assignable.hpp"
#include "../Executable.hpp"

namespace ir = tkom::structures::ir;

namespace tkom { namespace structures { namespace ir { namespace instructions
{
    struct Call: public ir::Instruction, public ir::Assignable
    {
        ir::Function::ptr function;
        std::vector<std::shared_ptr<ir::Assignable>> arguments;

        virtual std::shared_ptr<Literal> execute(ScopeInst& scope)
        {
            // FIXME: Call function and return it's value
            return nullptr;
        }
    };
}}}}

#endif
