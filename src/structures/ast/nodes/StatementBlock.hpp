#ifndef TKOM_STRUCTURES_AST_NODES_STATEMENTBLOCK_HPP
#define TKOM_STRUCTURES_AST_NODES_STATEMENTBLOCK_HPP

#include "../AST.hpp"

#include <vector>

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class StatementBlock: public Node
    {
    public:
        void addInstruction(const ast::NodePtr& node)
        {
            this->instructions.push_back(node);
        }
        virtual Type getType()
        {
            return Node::Type::StatementBlock;
        }

        std::vector<ast::NodePtr> instructions;
    };
}}}

#endif
