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
        void setLeftSide(const ast::NodePtr& node)
        {
            this->leftNode = node;
        }
        void setRightSide(const ast::NodePtr& node)
        {
            this->rightNode = node;
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
            return this->leftNode;
        }

    private:
        bool negated = false;
        ast::NodePtr leftNode;
        ast::NodePtr rightNode;
        TokenType operation;
    };
}}}

#endif
