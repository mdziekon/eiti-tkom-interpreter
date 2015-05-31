#ifndef TKOM_STRUCTURES_AST_NODES_ASSIGNMENT_HPP
#define TKOM_STRUCTURES_AST_NODES_ASSIGNMENT_HPP

#include "../AST.hpp"

using Node = tkom::structures::ast::Node;

namespace tkom { namespace structures { namespace ast
{
    class Variable;
    class Assignable;

    class Assignment: public Node
    {
    public:
        void setVariable(const std::shared_ptr<Variable>& variable)
        {
            this->variable = variable;
        }
        void setValue(const std::shared_ptr<Assignable>& value)
        {
            this->value = value;
        }

    private:
        std::shared_ptr<Variable> variable;
        std::shared_ptr<Assignable> value;
    };
}}}

#endif
