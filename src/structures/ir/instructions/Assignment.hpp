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
        std::shared_ptr<ir::Variable> variable = std::make_shared<ir::Variable>();
        std::shared_ptr<ir::Assignable> value;

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        )
        {
            if (!this->variable->indexArg1)
            {
                scope->setVariable(variable->name, value->execute(scope, functions));
                return nullptr;
            }

            std::shared_ptr<Literal> ref = scope->getVariable(variable->name);
            auto indexArgVal = this->variable->indexArg1->execute(scope, functions);
            if (indexArgVal->getSize() != std::make_pair<unsigned int, unsigned int>(1, 1))
            {
                ErrorHandler::error(
                    std::string("Cannot call index access using matrix")
                );
                return nullptr;
            }
            if (indexArgVal->data.at(0).at(0) < 0)
            {
                ErrorHandler::error(
                    std::string("Negative index (y)")
                );
                return nullptr;
            }
            if (ref->data.size() <= indexArgVal->data.at(0).at(0))
            {
                ErrorHandler::error(
                    std::string("Out of bound access (y)")
                );
                return nullptr;
            }

            auto& rowRef = ref->data.at(indexArgVal->data.at(0).at(0));
            if (!this->variable->indexArg2)
            {
                auto newVal = value->execute(scope, functions);

                if (newVal->getSize() != std::make_pair<unsigned int, unsigned int>(1, rowRef.size()))
                {
                    ErrorHandler::error(
                        std::string("Invalid assignable size (y)")
                    );
                    return nullptr;
                }

                rowRef = newVal->data.at(0);
                return nullptr;
            }

            indexArgVal = this->variable->indexArg2->execute(scope, functions);
            if (indexArgVal->getSize() != std::make_pair<unsigned int, unsigned int>(1, 1))
            {
                ErrorHandler::error(
                    std::string("Cannot call index access using matrix")
                );
                return nullptr;
            }
            if (indexArgVal->data.at(0).at(0) < 0)
            {
                ErrorHandler::error(
                    std::string("Negative index (x)")
                );
                return nullptr;
            }
            if (rowRef.size() <= indexArgVal->data.at(0).at(0))
            {
                ErrorHandler::error(
                    std::string("Out of bound access (x)")
                );
                return nullptr;
            }

            auto newVal = value->execute(scope, functions);

            if (newVal->getSize() != std::make_pair<unsigned int, unsigned int>(1, 1))
            {
                ErrorHandler::error(
                    std::string("Invalid assignable size (x)")
                );
                return nullptr;
            }

            rowRef.at(indexArgVal->data.at(0).at(0)) = newVal->data.at(0).at(0);

            return nullptr;
        }
    };
}}}}

#endif
