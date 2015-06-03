#ifndef TKOM_STRUCTURES_IR_INSTRUCTIONS_CALL_HPP
#define TKOM_STRUCTURES_IR_INSTRUCTIONS_CALL_HPP

#include <vector>
#include <memory>
#include <string>

#include "../Instruction.hpp"
#include "../Assignable.hpp"
#include "../Executable.hpp"
#include "../../../modules/stdlib/StdLib.hpp"

namespace ir = tkom::structures::ir;
using StdLib = tkom::modules::StdLib;

namespace tkom { namespace structures { namespace ir { namespace instructions
{
    struct Call: public ir::Instruction, public ir::Assignable
    {
        std::string name;
        std::vector<std::shared_ptr<ir::Assignable>> arguments;

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        )
        {
            std::vector<std::shared_ptr<ir::Literal>> concreteArguments;
            for(auto& it: this->arguments)
            {
                concreteArguments.push_back(it->execute(scope, functions));
            }

            if (functions.count(this->name) == 1)
            {
                return functions.at(this->name)->execute(nullptr, functions, concreteArguments);
            }
            else
            {
                return StdLib::callFunction(this->name, concreteArguments);
            }
        }
    };
}}}}

#endif
