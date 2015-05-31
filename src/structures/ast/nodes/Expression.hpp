#ifndef TKOM_STRUCTURES_AST_NODES_EXPRESSION_HPP
#define TKOM_STRUCTURES_AST_NODES_EXPRESSION_HPP

#include "../AST.hpp"

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class Expression: public Assignable
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

    private:
        ast::NodePtr leftNode;
        ast::NodePtr rightNode;
        TokenType operation;
    };
}}}

#endif
