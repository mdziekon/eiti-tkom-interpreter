#ifndef TKOM_STRUCTURES_IR_LITERAL_HPP
#define TKOM_STRUCTURES_IR_LITERAL_HPP

#include <vector>
#include <memory>
#include <iostream>
#include <utility>

#include "ConditionOperand.hpp"
#include "ExpressionOperand.hpp"

#include "../../modules/error-handler/ErrorHandler.hpp"
using ErrorHandler = tkom::modules::ErrorHandler;

namespace tkom { namespace structures { namespace ir
{
    struct Literal: public ConditionOperand, public ExpressionOperand
    {
        std::vector<std::vector<double>> data = {{}};
        bool castedToBool = false;
        bool loopJump = false;
        bool isBreak = false;

        virtual std::shared_ptr<Literal> execute(
            ScopeInst* scope,
            std::unordered_map<std::string, std::shared_ptr<Function>>& functions
        )
        {
            std::shared_ptr<Literal> copy = std::make_shared<Literal>();
            copy->data = this->data;

            return copy;
        }

        const std::pair<unsigned int, unsigned int> getSize() const
        {
            return std::make_pair<unsigned int, unsigned int>(this->data.size(), this->data.at(0).size());
        }

        virtual bool isTruthy()
        {
            for(auto& it: this->data)
            {
                for(auto& rowIt: it)
                {
                    if (rowIt != 0)
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        bool operator==(const Literal& rhs)
        {
            this->protectSizes(rhs);

            for(auto y = 0; y < this->data.size(); ++y)
            {
                for(auto x = 0; x < this->data.at(0).size(); ++x)
                {
                    if (this->data.at(y).at(x) != rhs.data.at(y).at(x))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool operator!=(const Literal& rhs)
        {
            return !((*this) == rhs);
        }

        bool operator<(const Literal& rhs)
        {
            this->protectRelationOp(rhs);

            return this->data.at(0).at(0) < rhs.data.at(0).at(0);
        }
        bool operator<=(const Literal& rhs)
        {
            this->protectRelationOp(rhs);

            return this->data.at(0).at(0) <= rhs.data.at(0).at(0);
        }
        bool operator>(const Literal& rhs)
        {
            this->protectRelationOp(rhs);

            return this->data.at(0).at(0) > rhs.data.at(0).at(0);
        }
        bool operator>=(const Literal& rhs)
        {
            this->protectRelationOp(rhs);

            return this->data.at(0).at(0) >= rhs.data.at(0).at(0);
        }

        Literal& operator+=(const Literal& rhs)
        {
            this->protectSizes(rhs);

            for(auto y = 0; y < this->data.size(); ++y)
            {
                for(auto x = 0; x < this->data.at(0).size(); ++x)
                {
                    this->data.at(y).at(x) += rhs.data.at(y).at(x);
                }
            }

            return *this;
        }
        Literal& operator-=(const Literal& rhs)
        {
            this->protectSizes(rhs);

            for(auto y = 0; y < this->data.size(); ++y)
            {
                for(auto x = 0; x < this->data.at(0).size(); ++x)
                {
                    this->data.at(y).at(x) -= rhs.data.at(y).at(x);
                }
            }

            return *this;
        }
        Literal& operator*=(const Literal& rhs)
        {
            this->protectMultiplicativeOp(rhs);

            this->data.at(0).at(0) *= rhs.data.at(0).at(0);

            return *this;
        }
        Literal& operator/=(const Literal& rhs)
        {
            this->protectMultiplicativeOp(rhs);

            this->data.at(0).at(0) /= rhs.data.at(0).at(0);

            return *this;
        }
        Literal& operator%=(const Literal& rhs)
        {
            this->protectMultiplicativeOp(rhs);

            if (rhs.data.at(0).at(0) == 0)
            {
                ErrorHandler::error(
                    std::string("Modulus of division by zero is invalid")
                );
                return *this;
            }

            this->data.at(0).at(0) = ((int) this->data.at(0).at(0)) % ((int) rhs.data.at(0).at(0));

            return *this;
        }

    private:
        void protectSizes(const Literal& rhs)
        {
            if (this->getSize() != rhs.getSize())
            {
                ErrorHandler::error(
                    std::string("Used matrices have different sizes")
                );
                return;
            }
        }
        void protectRelationOp(const Literal& rhs)
        {
            if (this->getSize() != std::make_pair<unsigned int, unsigned int>(1, 1))
            {
                ErrorHandler::error(
                    std::string("Comparison operator makes no sense for matrices")
                );
                return;
            }
            if (this->getSize() != rhs.getSize())
            {
                ErrorHandler::error(
                    std::string("Comparison operator makes no sense for matrices")
                );
                return;
            }
        }
        void protectMultiplicativeOp(const Literal& rhs)
        {
            if (this->getSize() != std::make_pair<unsigned int, unsigned int>(1, 1))
            {
                ErrorHandler::error(
                    std::string("Multiplicative operator makes no sense for matrices")
                );
                return;
            }
            if (this->getSize() != rhs.getSize())
            {
                ErrorHandler::error(
                    std::string("Multiplicative operator makes no sense for matrices")
                );
                return;
            }
        }
    };
}}}

#endif
