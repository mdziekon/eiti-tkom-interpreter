#ifndef TKOM_STRUCTURES_AST_NODES_VARDECLARATION_HPP
#define TKOM_STRUCTURES_AST_NODES_VARDECLARATION_HPP

#include "../AST.hpp"

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class VarDeclaration: public Node
    {
    public:
        void setName(const std::string& name)
        {
            this->name = name;
        }
        void setValue(const std::shared_ptr<Assignable>& assignableNode)
        {
            this->assignableNode = assignableNode;
        }

    private:
        std::string name;
        std::shared_ptr<Assignable> assignableNode;
    };
}}}

#endif
