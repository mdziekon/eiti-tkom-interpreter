#ifndef TKOM_STRUCTURES_IR_EXECUTABLE_HPP
#define TKOM_STRUCTURES_IR_EXECUTABLE_HPP

namespace tkom { namespace structures { namespace ir
{
    struct Literal;
    struct ScopeInst;

    struct Executable
    {
        virtual std::shared_ptr<Literal> execute(ScopeInst& scope) = 0;
    };
}}}

#endif
