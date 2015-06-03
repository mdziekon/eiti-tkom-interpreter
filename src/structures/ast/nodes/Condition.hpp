#ifndef TKOM_STRUCTURES_AST_NODES_CONDITION_HPP
#define TKOM_STRUCTURES_AST_NODES_CONDITION_HPP

#include "../AST.hpp"
#include "../../../modules/utils/TokenType.hpp"

using Node = tkom::structures::ast::Node;
using TokenType = tkom::modules::utils::TokenType;

namespace tkom { namespace structures { namespace ast
{
    class Condition: public Node
    {
    public:
        void addOperand(const ast::NodePtr& node)
        {
            this->operands.push_back(node);
        }
        void setOperator(const TokenType& operation)
        {
            this->operation = operation;
        }
        void setNegated()
        {
            this->negated = true;
        }
        bool isNegated()
        {
            return this->negated;
        }
        ast::NodePtr& getLeftSide()
        {
            return this->operands.at(0);
        }

        virtual Type getType()
        {
            return Node::Type::Condition;
        }

        bool negated = false;
        TokenType operation = TokenType::Undefined;
        std::vector<ast::NodePtr> operands;
    };
}}}

#endif
