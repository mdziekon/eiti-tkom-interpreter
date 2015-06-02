#ifndef TKOM_STRUCTURES_AST_NODES_CALL_HPP
#define TKOM_STRUCTURES_AST_NODES_CALL_HPP

#include "../AST.hpp"
#include <vector>

using Assignable = tkom::structures::ast::Assignable;

namespace tkom { namespace structures { namespace ast
{
    class Call: public Assignable
    {
    public:
        void setName(const std::string& name)
        {
            this->name = name;
        }
        void addArgument(const std::shared_ptr<Assignable>& assignableNode)
        {
            this->arguments.push_back(assignableNode);
        }
        virtual Type getType()
        {
            return Node::Type::Call;
        }

        std::string name;
        std::vector<std::shared_ptr<Assignable>> arguments;
    };
}}}

#endif
