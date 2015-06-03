#ifndef TKOM_STRUCTURES_IR_EXPRESSION_HPP
#define TKOM_STRUCTURES_IR_EXPRESSION_HPP

#include <vector>
#include <memory>
#include <iostream>

#include "Assignable.hpp"
#include "ExpressionOperand.hpp"
#include "../../modules/utils/TokenType.hpp"

namespace tkom { namespace structures { namespace ir
{
    struct Expression: public Assignable, public ExpressionOperand
    {
        std::vector<tkom::modules::utils::TokenType> operations;
        std::vector<std::shared_ptr<ExpressionOperand>> operands;

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        )
        {
            if (this->operations.size() == 0)
            {
                return this->operands.at(0)->execute(scope, functions);
            }

            auto result = this->operands.at(0)->execute(scope, functions);
            unsigned int i = 0;
            for(auto& op: this->operations)
            {
                auto& it = this->operands.at(i + 1);
                i++;

                if (op == tkom::modules::utils::TokenType::Plus)
                {
                    *result += *(it->execute(scope, functions));
                }
                else if (op == tkom::modules::utils::TokenType::Minus)
                {
                    *result -= *(it->execute(scope, functions));
                }
                else if (op == tkom::modules::utils::TokenType::Multiply)
                {
                    *result *= *(it->execute(scope, functions));
                }
                else if (op == tkom::modules::utils::TokenType::Divide)
                {
                    *result /= *(it->execute(scope, functions));
                }
                else if (op == tkom::modules::utils::TokenType::Modulo)
                {
                    *result %= *(it->execute(scope, functions));
                }
                else
                {
                    ErrorHandler::error(
                        std::string("Invalid expression operator")
                    );
                    return nullptr;
                }
            }

            return result;
        }
    };
}}}

#endif
