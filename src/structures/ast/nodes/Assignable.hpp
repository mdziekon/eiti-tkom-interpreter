#ifndef TKOM_STRUCTURES_AST_NODES_ASSIGNABLE_HPP
#define TKOM_STRUCTURES_AST_NODES_ASSIGNABLE_HPP

#include "../AST.hpp"

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class Assignable: public Node
    {
    public:
        typedef std::shared_ptr<Assignable> ptr;
    };
}}}

#endif
