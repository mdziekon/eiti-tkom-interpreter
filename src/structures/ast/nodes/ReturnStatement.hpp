#ifndef TKOM_STRUCTURES_AST_NODES_RETURNSTATEMENT_HPP
#define TKOM_STRUCTURES_AST_NODES_RETURNSTATEMENT_HPP

#include "../AST.hpp"

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class ReturnStatement: public Node
    {
    public:
        void setValue(const std::shared_ptr<Assignable>& assignableNode)
        {
            this->assignableNode = assignableNode;
        }
        virtual Type getType()
        {
            return Node::Type::ReturnStatement;
        }

        std::shared_ptr<Assignable> assignableNode;
    };
}}}

#endif
