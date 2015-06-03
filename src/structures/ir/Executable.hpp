#ifndef TKOM_STRUCTURES_IR_EXECUTABLE_HPP
#define TKOM_STRUCTURES_IR_EXECUTABLE_HPP

namespace tkom { namespace structures { namespace ir
{
    struct Literal;
    struct ScopeInst;
    struct Function;

    struct Executable
    {
        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        ) = 0;
    };
}}}

#endif
