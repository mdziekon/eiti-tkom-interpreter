#ifndef TKOM_STRUCTURES_IR_CONDITION_HPP
#define TKOM_STRUCTURES_IR_CONDITION_HPP

#include <vector>
#include <memory>
#include <iostream>

#include "Executable.hpp"
#include "ConditionOperand.hpp"
#include "Literal.hpp"
#include "../../modules/utils/TokenType.hpp"

#include "../../modules/error-handler/ErrorHandler.hpp"
using ErrorHandler = tkom::modules::ErrorHandler;

namespace tkom { namespace structures { namespace ir
{
    struct Condition: public ConditionOperand
    {
        bool negated = false;
        tkom::modules::utils::TokenType operation = tkom::modules::utils::TokenType::Undefined;
        std::vector<std::shared_ptr<ConditionOperand>> operands;

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        )
        {
            if (this->operation == tkom::modules::utils::TokenType::Undefined)
            {
                if (!this->negated)
                {
                    return this->operands.at(0)->execute(scope, functions);
                }
                else
                {
                    auto result = std::make_shared<Literal>();
                    result->castedToBool = true;
                    result->data = { { this->operands.at(0)->execute(scope, functions)->isTruthy() ? 0.0 : 1.0 } };
                    return result;
                }
            }

            else if (this->operation == tkom::modules::utils::TokenType::Or)
            {
                auto result = std::make_shared<ir::Literal>();
                result->castedToBool = true;
                for(auto& it: this->operands)
                {
                    if (it->execute(scope, functions)->isTruthy())
                    {
                        result->data = { { 1.0 } };
                        return result;
                    }
                }
                result->data = { { 0.0 } };
                return result;
            }
            else if (this->operation == tkom::modules::utils::TokenType::And)
            {
                auto result = std::make_shared<ir::Literal>();
                result->castedToBool = true;
                for(auto& it: this->operands)
                {
                    if (!it->execute(scope, functions)->isTruthy())
                    {
                        result->data = { { 0.0 } };
                        return result;
                    }
                }
                result->data = { { 1.0 } };
                return result;
            }
            else if (this->operation == tkom::modules::utils::TokenType::Equality)
            {
                auto result = std::make_shared<ir::Literal>();
                result->castedToBool = true;

                auto left = this->operands.at(0)->execute(scope, functions);
                auto right = this->operands.at(1)->execute(scope, functions);

                if (left->castedToBool && right->castedToBool)
                {
                    result->data = { { left->isTruthy() == right->isTruthy() ? 1.0 : 0.0 } };
                }
                else if (!left->castedToBool && !right->castedToBool)
                {
                    result->data = { { *left == *right ? 1.0 : 0.0 } };
                }
                else
                {
                    ErrorHandler::error(
                        std::string("Tried to compare matrix with bool matrix")
                    );
                    return nullptr;
                }

                return result;
            }
            else if (this->operation == tkom::modules::utils::TokenType::Inequality)
            {
                auto result = std::make_shared<ir::Literal>();
                result->castedToBool = true;

                auto left = this->operands.at(0)->execute(scope, functions);
                auto right = this->operands.at(1)->execute(scope, functions);

                if (left->castedToBool && right->castedToBool)
                {
                    result->data = { { left->isTruthy() != right->isTruthy() ? 1.0 : 0.0 } };
                }
                else if (!left->castedToBool && !right->castedToBool)
                {
                    result->data = { { *left != *right ? 1.0 : 0.0 } };
                }
                else
                {
                    ErrorHandler::error(
                        std::string("Tried to compare matrix with bool matrix")
                    );
                    return nullptr;
                }

                return result;
            }
            else if (this->operation == tkom::modules::utils::TokenType::Less)
            {
                auto result = std::make_shared<ir::Literal>();
                result->castedToBool = true;

                auto left = this->operands.at(0)->execute(scope, functions);
                auto right = this->operands.at(1)->execute(scope, functions);

                if (!left->castedToBool && !right->castedToBool)
                {
                    result->data = { { *left < *right ? 1.0 : 0.0 } };
                }
                else
                {
                    ErrorHandler::error(
                        std::string("Cannot compare bool matrices")
                    );
                    return nullptr;
                }

                return result;
            }
            else if (this->operation == tkom::modules::utils::TokenType::LessOrEqual)
            {
                auto result = std::make_shared<ir::Literal>();
                result->castedToBool = true;

                auto left = this->operands.at(0)->execute(scope, functions);
                auto right = this->operands.at(1)->execute(scope, functions);

                if (!left->castedToBool && !right->castedToBool)
                {
                    result->data = { { *left <= *right ? 1.0 : 0.0 } };
                }
                else
                {
                    ErrorHandler::error(
                        std::string("Cannot compare bool matrices")
                    );
                    return nullptr;
                }

                return result;
            }
            else if (this->operation == tkom::modules::utils::TokenType::Greater)
            {
                auto result = std::make_shared<ir::Literal>();
                result->castedToBool = true;

                auto left = this->operands.at(0)->execute(scope, functions);
                auto right = this->operands.at(1)->execute(scope, functions);

                if (!left->castedToBool && !right->castedToBool)
                {
                    result->data = { { *left > *right ? 1.0 : 0.0 } };
                }
                else
                {
                    ErrorHandler::error(
                        std::string("Cannot compare bool matrices")
                    );
                    return nullptr;
                }

                return result;
            }
            else if (this->operation == tkom::modules::utils::TokenType::GreaterOrEqual)
            {
                auto result = std::make_shared<ir::Literal>();
                result->castedToBool = true;

                auto left = this->operands.at(0)->execute(scope, functions);
                auto right = this->operands.at(1)->execute(scope, functions);

                if (!left->castedToBool && !right->castedToBool)
                {
                    result->data = { { *left >= *right ? 1.0 : 0.0 } };
                }
                else
                {
                    ErrorHandler::error(
                        std::string("Cannot compare bool matrices")
                    );
                    return nullptr;
                }

                return result;
            }
            else
            {
                ErrorHandler::error(
                    std::string("Invalid condition operator")
                );
                return nullptr;
            }
        }
    };
}}}

#endif
