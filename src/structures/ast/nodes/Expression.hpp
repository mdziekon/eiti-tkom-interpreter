#ifndef TKOM_STRUCTURES_AST_NODES_EXPRESSION_HPP
#define TKOM_STRUCTURES_AST_NODES_EXPRESSION_HPP

#include "../AST.hpp"

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class Expression: public Assignable
    {
    public:
        void addOperand(const ast::NodePtr& node)
        {
            this->operands.push_back(node);
        }
        void addOperator(const TokenType& operation)
        {
            this->operations.push_back(operation);
        }
        virtual Type getType()
        {
            return Node::Type::Expression;
        }

        std::vector<TokenType> operations;
        std::vector<ast::NodePtr> operands;
    };
}}}

#endif
