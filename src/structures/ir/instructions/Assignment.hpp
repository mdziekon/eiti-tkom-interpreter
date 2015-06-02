#ifndef TKOM_STRUCTURES_IR_INSTRUCTIONS_ASSIGNMENT_HPP
#define TKOM_STRUCTURES_IR_INSTRUCTIONS_ASSIGNMENT_HPP

#include <memory>

#include "../Instruction.hpp"
#include "../Variable.hpp"
#include "../Assignable.hpp"
#include "../Executable.hpp"

namespace ir = tkom::structures::ir;

namespace tkom { namespace structures { namespace ir { namespace instructions
{
    struct Assignment: public ir::Instruction
    {
        std::string variable;
        std::shared_ptr<ir::Assignable> value;

        virtual std::shared_ptr<Literal> execute(ScopeInst& scope)
        {
            // FIXME: Assign value to variable
            return nullptr;
        }
    };
}}}}

#endif
